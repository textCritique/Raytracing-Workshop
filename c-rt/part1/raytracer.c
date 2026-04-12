#include "raytracer.h"

#include <math.h>
#include <stdlib.h>

/*
 * Part 1 implementation.
 *
 * This version intentionally stays simple:
 * - find the nearest sphere hit by the ray
 * - return the sphere's base color
 * - return black if no object is hit
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
    /* Background color for rays that do not hit anything. */
    return (RGB){0, 0, 0};
  }

  return adjustColor(sphere.color, intensity);
}

/* ---------- Viewport mapping ---------- */

Point g_to_viewport(int gx, int gy, int gw, int gh) {
  /*
   * Convert a window coordinate to a point on a simple viewport.
   * The viewport is placed in front of the camera.
   */
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
   * 1. Compute the vector from the ray origin to the sphere center.
   * 2. Build the quadratic equation for ray-sphere intersection.
   * 3. Return the two roots when the discriminant is non-negative.
   */
  return NULL;
}

void closestSphere(Point o, Point d, double tmin, double tmax,
                   int n_spheres, Sphere s_arr[],
                   Sphere* closest_s, double* c_t) {
  /*
   * TODO:
   * - Initialize the closest hit distance to infinity.
   * - Loop through every sphere.
   * - Call intersectSphere() and keep the smallest valid root.
   * - Store the winning sphere in closest_s and the distance in c_t.
   */
}

/* ---------- Part 1 ray tracer ---------- */

RGB rtx(Point o, Point d, double tmin, double tmax,
        int n_spheres, Sphere s_arr[]) {
  /*
   * TODO:
   * - Find the nearest visible sphere.
   * - If nothing is hit, return the background color.
   * - Otherwise return the sphere color directly.
   */
  return (RGB){0, 0, 0};
}