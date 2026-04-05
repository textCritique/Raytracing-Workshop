# Part 2 — Ray Tracing with Shader

This stage adds lighting calculations on top of the ray tracer.
The spheres are still intersected in the same way, but now the visible point is
shaded using:
- ambient light
- diffuse light
- specular light

## What students should understand
- how light direction affects brightness
- how the surface normal changes the shading result
- how to combine several light sources

## Files
- `raytracer.h` and `raytracer.c`: vector math, intersection, and lighting
- `render.c`: scene setup and window drawing

## Assignment idea
Try changing the light positions or the shininess values and observe how the
image changes.