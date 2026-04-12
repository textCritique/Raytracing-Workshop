#include "raytracer.h"

#include <math.h>
#include <stdlib.h>

/*
 * Part 2 implementation.
 *
 * Compared with part 1, the only big change is the lighting model.
 * The code now calculates ambient, diffuse, and specular contributions.
 */

/* ---------- Vector operations ---------- */

Point sub3(Point p1, Point p2) {
  Point p;
  p.x = p1.x - p2.x;
  p.y = p1.y - p2.y;
  p.z = p1.z - p2.z;
  return p;
}

Point add3(Point p1, Point p2) {
  Point p;
  p.x = p1.x + p2.x;
  p.y = p1.y + p2.y;
  p.z = p1.z + p2.z;
  return p;
}

Point scale(double k, Point p2) {
  Point p;
  p.x = k * p2.x;
  p.y = k * p2.y;
  p.z = k * p2.z;
  return p;
}

double dot(Point p1, Point p2) {
  return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

double norm(Point p) {
  return sqrt(dot(p, p));
}

Point reflectedRay(Point ncap, Point l) {
  return sub3(scale(2 * dot(l, ncap), ncap), l);
}

/* ---------- Quadratic equation ---------- */

double* quad(double a, double b, double c) {
  double discriminant = b * b - 4 * a * c;
  double* roots = NULL;

  if (discriminant >= 0) {
    roots = (double*)malloc(sizeof(double) * 2);
    roots[0] = (-b - sqrt(discriminant)) / (2 * a);
    roots[1] = (-b + sqrt(discriminant)) / (2 * a);
  }

  return roots;
}

/* ---------- Color helpers ---------- */

short int clamp(double x) {
  if (x > 255) return 255;
  if (x < 0) return 0;
  return (short int)round(x);
}

RGB adjustColor(RGB rgb, double intensity) {
  RGB newrgb;
  newrgb.r = clamp(rgb.r * intensity);
  newrgb.g = clamp(rgb.g * intensity);
  newrgb.b = clamp(rgb.b * intensity);
  return newrgb;
}

RGB sphereColor(Sphere sphere, double intensity) {
  if (isinf(intensity)) {
    return (RGB){0, 0, 0};
  }

  return adjustColor(sphere.color, intensity);
}

/* ---------- Viewport mapping ---------- */

Point g_to_viewport(int gx, int gy, int gw, int gh) {
  double vw = 1.0;
  double vh = 1.0;
  Point v;
  v.x = (double)gx * vw / (double)gw;
  v.y = (double)gy * vh / (double)gh;
  v.z = 1.0;
  return v;
}

/* ---------- Sphere intersection ---------- */

double* intersectSphere(Point o, Point d, Sphere s) {
  /*
   * TODO:
   * Build the quadratic equation for the ray-sphere test and return the
   * two possible intersection distances when the ray hits the sphere.
   */
  return NULL;
}

void closestSphere(Point o, Point d, double tmin, double tmax,
                   int n_spheres, Sphere s_arr[],
                   Sphere* closest_s, double* c_t) {
  /*
   * TODO:
   * Keep the nearest valid sphere intersection.
   * Ignore roots outside the [tmin, tmax] interval.
   */
}

/* ---------- Lighting ---------- */

double diffuseI(Point normal, Point l, double i) {
  /*
   * TODO:
   * Compute the diffuse term using the angle between the normal and the
   * light direction.
   */
  return 0;
}

double specularI(Point o, Point p, Point normal, Point l, double i, int s) {
  /*
   * TODO:
   * Reflect the light vector around the normal, compare it with the view
   * vector, and raise the result to the shininess exponent.
   */
  return 0;
}

double tli(Point normal, Point p, Point o, int s,
           int no_lights, Light l_arr[]) {
  /*
   * TODO:
   * Loop over every light source and add ambient, diffuse, and specular
   * contributions.
   */
  return 0;
}

/* ---------- Part 2 ray tracer ---------- */

RGB rtx(Point o, Point d, double tmin, double tmax,
        int no_lights, int n_sphere, Sphere s_arr[], Light l_arr[]) {
  /*
   * TODO:
   * 1. Find the closest sphere hit.
   * 2. Compute the hit point and surface normal.
   * 3. Call tli() to evaluate the shading.
   * 4. Return the shaded sphere color.
   */
  return (RGB){0, 0, 0};
}