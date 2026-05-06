#include <stdbool.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "raytracer.h"

/*
 * Part 2 renderer.
 *
 * This file sets up a window and asks the ray tracer for one color per pixel.
 * There are no lights in this stage, so the spheres are rendered with their
 * base colors only.
 */

static const int WINDOW_WIDTH = 1000;
static const int WINDOW_HEIGHT = 720;

/* Scene: a few spheres placed in front of the camera. */
Sphere spheres[] = {
    { .c = {0.0, -1.0, 3.0},   .r = 1.0,   .color = {255, 0, 0} },
    { .c = {-2.0, 1.0, 3.0},   .r = 1.0,   .color = {0, 0, 255} },
    { .c = {2.0, 1.0, 3.0},    .r = 1.0,   .color = {0, 255, 0} },
    { .c = {0.0, -5001.0, 0.0}, .r = 5000.0, .color = {255, 255, 0} },
};

static const int num_spheres = sizeof(spheres) / sizeof(Sphere);

static bool quit(void) {
  SDL_Event e;

  if (SDL_PollEvent(&e)) {
    if (e.type == SDL_EVENT_QUIT) {
      return false;
    }
    if (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE) {
      return false;
    }
  }

  SDL_Delay(1);
  return true;
}

/* Return a pointer to the pixel at (x, y). */
static inline Uint8* get_pixel_ptr(SDL_Surface *surface, int x, int y) {
  int bpp = SDL_BYTESPERPIXEL(surface->format);
  return (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
}

/* Write an RGB value into the SDL surface. */
static void set_pixel(SDL_Surface *surface, int x, int y,
                      Uint8 r, Uint8 g, Uint8 b) {
  const SDL_PixelFormatDetails *fmt = SDL_GetPixelFormatDetails(surface->format);
  Uint32 color = SDL_MapRGB(fmt, NULL, r, g, b);
  Uint8 *pixel = get_pixel_ptr(surface, x, y);
  int bpp = SDL_BYTESPERPIXEL(surface->format);
  memcpy(pixel, &color, (size_t)bpp);
}

int main(void) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Ray Tracer — Part 1",
                                        WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (!window) {
    SDL_Quit();
    return 1;
  }

  SDL_Surface *surface = SDL_GetWindowSurface(window);
  if (!surface) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  if (SDL_MUSTLOCK(surface)) {
    SDL_LockSurface(surface);
  }

  int x_offset = WINDOW_WIDTH / 2;
  int y_offset = WINDOW_HEIGHT / 2;
  Point o = {0.0, 0.0, 0.0};

  /* One ray per pixel. */
  for (int y = 0; y < surface->h; y++) {
    for (int x = 0; x < surface->w; x++) {
      Point v = g_to_viewport(x - x_offset, -y + y_offset,
                               WINDOW_WIDTH, WINDOW_HEIGHT);
      Point d = sub3(v, o);
      RGB rgb = rtx(o, d, 1.0, INFINITY, num_spheres, spheres);
      set_pixel(surface, x, y, (Uint8)rgb.r, (Uint8)rgb.g, (Uint8)rgb.b);
    }
  }

  if (SDL_MUSTLOCK(surface)) {
    SDL_UnlockSurface(surface);
  }

  SDL_UpdateWindowSurface(window);
  while (quit()) {
    /* Keep the window open until the user closes it. */
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}