#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <math.h>
#include <stdlib.h>

/*
 * Part 1: the geometry-only version of the ray tracer.
 *
 * The goal here is to keep the code small and readable:
 * - vector math helpers
 * - sphere intersection
 * - a simple ray-tracing entry point
 */

typedef struct {
  double x, y, z;
} Point;

typedef struct {
  short int r, g, b;
} RGB;

typedef struct {
  double r;     /* radius */
  Point c;      /* center */
  RGB color;    /* base color */
} Sphere;

/* Vector operations */
Point sub3(Point p1, Point p2);
Point add3(Point p1, Point p2);
Point scale(double k, Point p2);
double dot(Point p1, Point p2);
double norm(Point p);
Point reflectedRay(Point ncap, Point l);

/* Quadratic solver used by sphere intersection */
double* quad(double a, double b, double c);

/* Color helpers */
short int clamp(double x);
RGB adjustColor(RGB rgb, double intensity);
RGB sphereColor(Sphere sphere, double intensity);

/* Screen-to-viewport mapping */
Point g_to_viewport(int gx, int gy, int gw, int gh);

/* Sphere intersection helpers */
double* intersectSphere(Point o, Point d, Sphere s);
void closestSphere(Point o, Point d, double tmin, double tmax,
                   int n_spheres, Sphere s_arr[],
                   Sphere* closest_s, double* c_t);

/* Main ray-tracing entry point for part 1 */
RGB rtx(Point o, Point d, double tmin, double tmax,
        int n_spheres, Sphere s_arr[]);

#endif