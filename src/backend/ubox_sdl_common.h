#pragma once
#include "common.h"

#if defined(SDL1)
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#elif defined(SDL2)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

#if defined(SDL1) || defined(SDL2)
#define DISPLAY_COLOR_DEPTH 24
extern cvector_vector_type(image_info) g_sprite_list;

void set_pixel(SDL_Surface* surface, int x, int y, int color);
SDL_Surface* load_png(const char* filename);
#endif