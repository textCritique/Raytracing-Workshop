# Part 3 — Full Ray Tracing

This final stage adds the features that make the image feel like a real ray
tracer:
- shader-based lighting
- shadows
- mirror reflections

## What students should understand
- how to cast a second ray toward each light to test for shadows
- how to recursively trace reflection rays
- how recursive depth limits prevent infinite loops

## Files
- `raytracer.h` and `raytracer.c`: geometry, lighting, shadows, and recursion
- `render.c`: the final scene configuration

## Assignment idea
Increase or decrease the recursion depth and observe how reflection quality
changes.