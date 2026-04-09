
import check50
import check50.c

@check50.check()
def exists():
    """part1.c exists"""
    check50.exists("part1.c")

@check50.check(exists)
def compiles():
    """part1.c compiles with raytracer test harness"""
    check50.include("testing_part1.c", "raytracer.h")
    check50.c.compile("part1.c", "testing_part1.c", exe_name="test_part1")

@check50.check(compiles)
def closest_sphere_hit():
    """closestSphere finds nearest visible sphere"""
    check50.run("./test_part1 closestSphere-hit").stdout("OK\n", regex=False).exit(0)

@check50.check(compiles)
def closest_sphere_miss():
    """closestSphere returns no hit when ray misses all spheres"""
    check50.run("./test_part1 closestSphere-miss").stdout("OK\n", regex=False).exit(0)

@check50.check(compiles)
def rtx_inner_hit():
    """rtx_inner returns finite intensity and hit sphere"""
    check50.run("./test_part1 rtx_inner-hit").stdout("OK\n", regex=False).exit(0)

@check50.check(compiles)
def rtx_inner_miss():
    """rtx_inner returns infinity for miss"""
    check50.run("./test_part1 rtx_inner-miss").stdout("OK\n", regex=False).exit(0)

@check50.check(compiles)
def rtx_hit():
    """rtx returns hit sphere color"""
    check50.run("./test_part1 rtx-hit").stdout("OK\n", regex=False).exit(0)

@check50.check(compiles)
def rtx_miss():
    """rtx returns black background for miss"""
    check50.run("./test_part1 rtx-miss").stdout("OK\n", regex=False).exit(0)
