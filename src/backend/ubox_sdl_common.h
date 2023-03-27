#pragma once
#include "common.h"

#if defined(SDL2)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>
#else
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_framerate.h>
#endif

extern const uint32_t rmask;
extern const uint32_t gmask;
extern const uint32_t bmask;
extern const uint32_t amask;

extern FPSmanager fpsManager;
extern int frameCount;
extern Uint32 lastTime;
extern float fps;

#define DISPLAY_COLOR_DEPTH 24


void set_pixel(SDL_Surface* surface, int x, int y, int color);
SDL_Surface* load_png(const char* filename);
SDL_Surface* create_icon();
