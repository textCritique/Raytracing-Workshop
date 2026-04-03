import time
start = time.time()
from numba import jit, vectorize
import numpy as np
import pygame

# dimension of window
WIDTH, HEIGHT = (600,600)

# for representing 3D points - each field is accessed by [0], [1], [2]
Point = np.dtype("(3,)f8")

"""
    Type for sphere

    Parameters:
        r : radius
        c : center
        color : color of the sphere
        s : shiniess of the sphere ranges 0 on up, -ve means not shiny
        rfl : reflectiveness of the sphere ranges from 0 to 1
"""
Sphere = np.dtype(
    [
        ("r", np.float64),
        ("c", Point),
        ("color", np.dtype("(3,)uint8")),
        ("s", np.int16),
        ("rfl", np.float64),
    ]
)

"""
    Type for light

    Parameters:
        k : kind of light ('p' - for point source, 'd' for directional light, 'a' - for ambient source)
        i : intensity of the light
        v : vector of the light (irrelevant in case of ambient source)
"""
Light = np.dtype([("k", np.dtype("U1")), ("i", np.float64), ("v", Point)])


# norm of a vector
@jit
def norm(v):
    return np.sqrt(v * v)


# quadratic equation solver
@jit
def quad(a, b, c):
    d = b * b - 4 * a * c
    if d >= 0:
        return ((-b + np.sqrt(d)) / (2 * a)), ((-b - np.sqrt(d)) / (2 * a))
    else:
        return np.nan, np.nan


# clamping function
@jit
def clamp(x):
    if x > 255:
        return 255
    elif x < 0:
        return 0
    else:
        return round(x)


# increasing brightness of a color
# takes np.array and returns a tuple
@jit
def rgb(color_arr, intensity):
    r = color_arr[0] * intensity
    g = color_arr[1] * intensity
    b = color_arr[2] * intensity
    return (clamp(r), clamp(g), clamp(b))


# finds out color of sphere if its actually a sphere
# can be later extended to give color of other objects
def sphere_color(sphere, intensity, is_valid):
    if is_valid:
        r, g, b = rgb(sphere["color"], intensity)
        return np.array([r, g, b], dtype=np.int16)
    else:
        return np.array([0, 0, 0], dtype=np.int16)

# transforming world coordinate to window coordinate
# In window coordinate of pygame, origin is at top left corner of the window and x increases towards right and y increases downwards
@jit
def transform_coord(x,y):
    n_x = x + WIDTH//2
    n_y = y + HEIGHT//2
    return (n_x, n_y)

# transforming window coordinate to world coordinate
# setting width vw and height vh of viewport
# z coordinate of viewport is d 
@jit
def g_to_viewport(gx, gy):
    vwdith = 1.
    vheight = 1.
    vx = float(gx) * vwdith / float(WIDTH)
    vy = float(gy) * vheight / float(HEIGHT)
    d = 0.58
    return np.array([vx, vy, d])

# finding the point of intersection with sphere and return the parameter t
@jit
def intersect_sphere(o, d, sphere):
    co = o - sphere['c']
    a = np.dot(d,d)
    b = 2. * np.dot(d, co)
    c = np.dot(co, co) - (sphere['r'])**2
    return quad(a, b, c)

# find closest sphere to the camera and parameter t of intersection with sphere with ray from camera
# closest sphere should initially be None
# closest t should intially be infinity
def closest_sphere(o, d, tmin, tmax, sphere_arr):
    c_sphere = None
    c_t = np.inf
    for sphere in sphere_arr:
        t1, t2 = intersect_sphere(o,d, sphere)
        if (not np.isnan(t1) and t1 >= tmin and t1 <= tmax) and t1 <= c_t:
            c_t = t1
            c_sphere = sphere
        
        if (not np.isnan(t2) and t2 >= tmin and t2 <= tmax) and t2 <= c_t:
            c_t = t2
            c_sphere = sphere
    return c_sphere, c_t

# total intensity of light after reflection
@jit
def til(intensity):
    return intensity

# finally ray trace
def rtx(o, d, tmin, tmax, sphere_arr):
    objintesity = 0.
    otherintensity = 0.
    sphere, t = closest_sphere(o, d, tmin, tmax, sphere_arr)
    is_valid = t != np.inf
    if is_valid:
        objintesity = til(1)

    return sphere_color(sphere, objintesity, is_valid)

# create coordinate of pixels of graphics window
pixel_arr = np.empty((WIDTH, HEIGHT, 3), dtype= np.int16)

def initialize_pixel_arr(arr, sphere_arr):
    # Jitted inner loop for pixel computation
    x_offset = WIDTH//2
    y_offset = HEIGHT//2
    o = np.array([0.,0.,0.],dtype=np.float64)
    for j in range(WIDTH):
        for i in range(HEIGHT):
            v = g_to_viewport(-j+x_offset,-i+y_offset)
            d = v - o
            result = rtx(o, d, 1., np.inf, sphere_arr)
            arr[j, i] = result
            
            
# scene definition
# consist of only sphere
spheres = [
    {
        "c" : [0., -1., 3.],
        "r" : 1.,
        "color" : [255, 0, 0],
        "s" : 9900,
        "rfl" : 0.2
    }, 
    {
        "c" : [-2., 1., 3.],
        "r" : 1.,
        "color" : [0, 0, 255],
        "s" : 5,
        "rfl" : 0.
    }, 
    {
        "c" : [2., 1., 3.],
        "r" : 1.,
        "color" : [0, 255, 0],
        "s" : 50,
        "rfl" : 0.5
    },
    {
        "c" : [0.,- 5001.,0.],
        "r" : 5000.,
        "color" : [255, 255, 0],
        "s" : 1000,
        "rfl" :  0.01
    }
]
sphere_arr = np.zeros(len(spheres),dtype=Sphere)
for i, sphere in enumerate(spheres):
    for k, val in sphere.items():
        sphere_arr[i][k] = val


# print(sphere_arr)
# pygame code starts
pygame.init()
window = pygame.display.set_mode((WIDTH, HEIGHT))
initialize_pixel_arr(pixel_arr, sphere_arr)
pygame.surfarray.blit_array(window, pixel_arr)
pygame.display.flip()
print("Time: ",time.time()-start)
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit()
