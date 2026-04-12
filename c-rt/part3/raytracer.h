#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <math.h>
#include <stdlib.h>

/*
 * Part 3: the complete assignment version.
 *
 * This file adds two new ideas on top of part 2:
 * - shadows: check whether a light ray is blocked by another sphere
 * - reflections: recursively trace the reflected ray
 */

typedef struct {
  double x, y, z;
} Point;

typedef struct {
  short int r, g, b;
} RGB;

typedef struct {
  double r;
  Point c;
  RGB color;
  int s;      /* shininess */
  double rfl; /* reflectiveness */
} Sphere;

typedef struct {
  char k;     /* 'a' ambient, 'd' directional, 'p' point */
  double i;   /* light intensity */
  Point v;    /* light direction or position */
} Light;

/* Vector operations */
Point sub3(Point p1, Point p2);
Point add3(Point p1, Point p2);
Point scale(double k, Point p2);
double dot(Point p1, Point p2);
double norm(Point p);
Point reflectedRay(Point ncap, Point l);

/* Quadratic solver */
double* quad(double a, double b, double c);

/* Color helpers */
short int clamp(double x);
RGB adjustColor(RGB rgb, double intensity);
RGB sphereColor(Sphere sphere, double intensity);

/* Viewport mapping */
Point g_to_viewport(int gx, int gy, int gw, int gh);

/* Sphere intersection */
double* intersectSphere(Point o, Point d, Sphere s);
void closestSphere(Point o, Point d, double tmin, double tmax,
                   int n_spheres, Sphere s_arr[],
                   Sphere* closest_s, double* c_t);

/* Lighting and recursion */
double diffuseI(Point normal, Point l, double i);
double specularI(Point o, Point p, Point normal, Point l, double i, int s);
double tli(Point normal, Point p, Point o, int s,
           int no_lights, Light l_arr[],
           int no_spheres, Sphere s_arr[]);
double rtx_inner(Point o, Point d, double tmin, double tmax,
                 int no_lights, int n_sphere, Sphere s_arr[], Light l_arr[],
                 int limit, Sphere *sphere);

/* Final ray tracer */
RGB rtx(Point o, Point d, double tmin, double tmax,
        int no_lights, int n_sphere, Sphere s_arr[], Light l_arr[]);

#endif