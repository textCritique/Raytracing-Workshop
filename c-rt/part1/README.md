# Part 1 — Simple Ray Tracing

This stage renders spheres by tracing a ray from the camera through each pixel.
There is no shader yet: if a ray hits a sphere, the sphere is painted with its
base color.

## What students should understand
- how rays are formed from screen pixels
- how a ray intersects a sphere
- how the nearest visible object is chosen
- how the final image is written to the window

## Files
- `raytracer.h` and `raytracer.c`: math helpers, sphere intersection, and the
  basic ray-tracing routine
- `render.c`: SDL window setup and the pixel loop

## Assignment idea
Extend this stage by adding your own object types or changing the camera and
viewport mapping.