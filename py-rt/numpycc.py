import numpy as np

# define datatype of each element
Point = np.dtype([("x", np.float64), ("y", np.float64), ("z", np.float64)])
point = np.dtype("(3,)f8")

# create numpy array with specific datatype
arr = np.zeros(100, dtype=Point)
arr2 = np.array([(1, 2, 3), (4, 5, 6), (7, 8, 9)], dtype=Point)
a = np.array([(1.0, 2.0, 3.0)], dtype=point)
b = np.array([(4.0, 5.0, 6.0)], dtype=point)

# access array
print(arr2[1]["y"])
# add, subtract and multiplication two arrays element by element
print(a + b)
print(a - b)
print(a * b)
# dot product
print(np.dot(np.array([1,2,3]),np.array([3,2,1])))
# scalar multiplication
print(2 * a)
# norm of vector which is represented as array
print(np.linalg.norm(a))
