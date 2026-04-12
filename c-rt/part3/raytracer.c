#include "raytracer.h"

#include <math.h>
#include <stdlib.h>

/*
 * Part 3 implementation.
 *
 * This is the full assignment solution path:
 * 1. trace the primary ray
 * 2. compute direct lighting
 * 3. test for shadows
 * 4. trace reflected rays recursively
 */

#define EPSILON 0.00001

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
   * Build the quadratic equation for the ray-sphere intersection and return
   * the roots when the discriminant is non-negative.
   */
  return NULL;
}

void closestSphere(Point o, Point d, double tmin, double tmax,
                   int n_spheres, Sphere s_arr[],
                   Sphere* closest_s, double* c_t) {
  /*
   * TODO:
   * Search all spheres and keep the closest hit in the valid t-range.
   */
}

/* ---------- Lighting ---------- */

double diffuseI(Point normal, Point l, double i) {
  /*
   * TODO:
   * Return the diffuse contribution only when the light is in front of the
   * surface.
   */
  return 0;
}

double specularI(Point o, Point p, Point normal, Point l, double i, int s) {
  /*
   * TODO:
   * Compute the mirror reflection and compare it to the camera direction to
   * create a specular highlight.
   */
  return 0;
}

/*
 * Returns the light intensity at a surface point.
 *
 * In part 3 we also check whether the light is blocked by another sphere.
 */
double tli(Point normal, Point p, Point o, int s,
           int no_lights, Light l_arr[],
           int no_spheres, Sphere s_arr[]) {
  /*
   * TODO:
   * For each light source:
   * - compute the light vector
   * - cast a shadow ray
   * - add diffuse/specular terms only when the point is visible
   */
  return 0;
}

/*
 * Recursive ray tracing for reflections.
 *
 * The intensity returned here is the final shading value for the closest hit.
 * If the ray misses everything, INFINITY is returned as a marker value.
 */
double rtx_inner(Point o, Point d, double tmin, double tmax,
                 int no_lights, int n_sphere, Sphere s_arr[], Light l_arr[],
                 int limit, Sphere *sphere) {
  /*
   * TODO:
   * 1. Find the closest sphere hit for the incoming ray.
   * 2. Compute the hit point and the normal.
   * 3. Evaluate direct lighting with tli().
   * 4. If the sphere is reflective, recursively trace the reflected ray.
   * 5. Blend the local and reflected intensities using the reflectiveness.
   */
  return INFINITY;
}

RGB rtx(Point o, Point d, double tmin, double tmax,
        int no_lights, int n_sphere, Sphere s_arr[], Light l_arr[]) {
  /*
   * TODO:
   * Call rtx_inner() with a recursion limit and convert the resulting
   * intensity into a final RGB color.
   */
  return (RGB){0, 0, 0};
}