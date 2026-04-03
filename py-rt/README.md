# Raytracing-Workshop
Hands-On Workshop on Raytracing with Python

## Prerequisites:

### create virtual environment and install pygame

create a venv in project folder (where all raytracing code will be there)
- `uv venv --python 3.11`
activate venv (needs to be activated everytime you work on this project)
- `source .venv/bin/activate.fish`
install pygame
- `uv pip install -r requirements.txt`

without using uv

- `python3.11 -m venv .venv`
- `source .venv/bin/activate`
- `pip install pygame, numpy, numba`

## installation check

Create **test.py**, copy and paste following and run `python test.py`:

```python

import pygame

pygame.init()
window = pygame.display.set_mode((640, 480))

window.fill((0,0,0))
pygame.display.flip()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit()
            
```

You will get a screen such as

[!test image](./../img/test.png)

## numpy & numba

We will use numpy instead of pure python which is slower.

Here is bare minimum that we need to know:

```python

import numpy as np

# define datatype of each element
Point = np.dtype([
    ('x', np.float64),
    ('y', np.float64),
    ('z', np.float64)
])

point = np.dtype("(3,)f8")

# further reading: https://numpy.org/doc/stable/reference/arrays.dtypes.html

# create numpy array with specific datatype
arr = np.zeros(100,dtype=Point)
arr2 = np.array([(1,2,3),(4,5,6),(7,8,9)],dtype=Point)
a = np.array([1,2,3], dtype= Point)
b = np.array([4,5,6], dtype= Point)

# access array
print(arr2[1]['y'])
# add, subtract and multiplication two arrays element by element
print(a+b)
print(a-b)
print(a*b)
# dot product
print(np.dot(np.array([1,2,3]),np.array([3,2,1])))
# scalar multiplication
print(2*a)
# norm of vector which is represented as array
print(np.linalg.norm(a))

```

Numba is a just-in-time(jit) compiler for python. It helps to optimize code especially numpy and math-heavy computation by compiling function to machine code.
It works by prefixing function definition with decorators like `@jit` and `@vectorize`.
