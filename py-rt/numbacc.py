
from numba import config, njit, threading_layer, vectorize
import numpy as np
import time

config.THREADING_LAYER = 'threadsafe'

@njit(parallel=True)
def foo(a, b):
    return a + b

x = np.arange(10.)
y = x.copy()

# Compilation + first run (slow)
start = time.time()
foo(x, y)
print(f"First call: {(time.time() - start) * 1000:.2f} ms")

# Subsequent runs (fast - no compilation)
start = time.time()
for _ in range(1000):
    foo(x, y)
print(f"1000 calls: {(time.time() - start) * 1000:.2f} ms")

print("Threading layer chosen: %s" % threading_layer())


# monte carlo simulation
@njit
def approx_pi(nsamples):
    accu = 0
    for _ in range(nsamples):
        x = np.random.random_sample()
        y = np.random.random_sample()
        if x**2 + y**2 <= 1:
            accu += 1
    return 4*accu/nsamples

start = time.time()
print(approx_pi(1000))
print("Time taken: ",time.time()-start)


start = time.time()
print(approx_pi(1000000))
print("Time taken: ",time.time()-start)

@vectorize(['float64(float64)'], target='parallel')
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

@vectorize(['(float64,float64)->(float64,float64,float64)'])
def return_tuple(a, b):
    return a + b, a - b, a * b

data = np.linspace(-10,10,100000)
print(data)

start = time.time()
print(sigmoid(data))
print("Time: ", time.time()-start)


start = time.time()
print(sigmoid(data))
print("Time: ", time.time()-start)

start = time.time()
print(return_tuple(data,data))
print("Time: ", time.time()-start)


start = time.time()
print(return_tuple(data, data))
print("Time: ", time.time()-start)
