#include "raytracer.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

static int approx(double a, double b) {
  return fabs(a - b) < 1e-6;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    return 2;
  }

  Sphere spheres[2] = {
      {.r = 1.0,
       .c = {0.0, 0.0, 3.0},
       .color = {255, 0, 0},
       .s = 500,
       .rfl = 0.2},
      {.r = 1.0,
       .c = {0.0, 0.0, 6.0},
       .color = {0, 255, 0},
       .s = 500,
       .rfl = 0.3},
  };

  Light lights[1] = {
      {.k = 'a', .i = 1.0, .v = {0.0, 0.0, 0.0}},
  };

  Point o = {0.0, 0.0, 0.0};
  Point d_hit = {0.0, 0.0, 1.0};
  Point d_miss = {1.0, 0.0, 0.0};

  if (strcmp(argv[1], "closestSphere-hit") == 0) {
    Sphere closest = {.r = -1.0, .c = {99.0, 99.0, 99.0}, .color = {1, 2, 3}, .s = 1, .rfl = 0.0};
    double t = INFINITY;
    closestSphere(o, d_hit, 0.001, INFINITY, 2, spheres, &closest, &t);

    if (approx(t, 2.0) && approx(closest.c.x, 0.0) && approx(closest.c.y, 0.0) && approx(closest.c.z, 3.0) &&
        closest.color.r == 255 && closest.color.g == 0 && closest.color.b == 0) {
      printf("OK\n");
      return 0;
    }

    printf("BAD t=%.6f c=(%.6f,%.6f,%.6f) color=(%d,%d,%d)\n", t, closest.c.x, closest.c.y, closest.c.z,
           closest.color.r, closest.color.g, closest.color.b);
    return 1;
  }

  if (strcmp(argv[1], "closestSphere-miss") == 0) {
    Sphere closest = {.r = -1.0, .c = {99.0, 99.0, 99.0}, .color = {1, 2, 3}, .s = 1, .rfl = 0.0};
    double t = 123.0;
    closestSphere(o, d_miss, 0.001, INFINITY, 2, spheres, &closest, &t);

    if (isinf(t)) {
      printf("OK\n");
      return 0;
    }

    printf("BAD t=%.6f\n", t);
    return 1;
  }

  if (strcmp(argv[1], "rtx_inner-hit") == 0) {
    Sphere hit = {.r = -1.0, .c = {99.0, 99.0, 99.0}, .color = {1, 2, 3}, .s = 1, .rfl = 0.0};
    double intensity = rtx_inner(o, d_hit, 0.001, INFINITY, 1, 2, spheres, lights, 3, &hit);

    if (approx(intensity, 1.0) && approx(hit.c.z, 3.0) && hit.color.r == 255 && hit.color.g == 0 && hit.color.b == 0) {
      printf("OK\n");
      return 0;
    }

    printf("BAD i=%.6f z=%.6f color=(%d,%d,%d)\n", intensity, hit.c.z, hit.color.r, hit.color.g, hit.color.b);
    return 1;
  }

  if (strcmp(argv[1], "rtx_inner-miss") == 0) {
    Sphere hit = {.r = -1.0, .c = {99.0, 99.0, 99.0}, .color = {1, 2, 3}, .s = 1, .rfl = 0.0};
    double intensity = rtx_inner(o, d_miss, 0.001, INFINITY, 1, 2, spheres, lights, 3, &hit);

    if (isinf(intensity)) {
      printf("OK\n");
      return 0;
    }

    printf("BAD i=%.6f\n", intensity);
    return 1;
  }

  if (strcmp(argv[1], "rtx-hit") == 0) {
    RGB color = rtx(o, d_hit, 0.001, INFINITY, 1, 2, spheres, lights);

    if (color.r == 255 && color.g == 0 && color.b == 0) {
      printf("OK\n");
      return 0;
    }

    printf("BAD color=(%d,%d,%d)\n", color.r, color.g, color.b);
    return 1;
  }

  if (strcmp(argv[1], "rtx-miss") == 0) {
    RGB color = rtx(o, d_miss, 0.001, INFINITY, 1, 2, spheres, lights);

    if (color.r == 0 && color.g == 0 && color.b == 0) {
      printf("OK\n");
      return 0;
    }

    printf("BAD color=(%d,%d,%d)\n", color.r, color.g, color.b);
    return 1;
  }

  return 2;
}
