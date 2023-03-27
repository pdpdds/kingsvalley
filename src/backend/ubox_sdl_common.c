#include <ubox_common.h>
#include "ubox_sdl_common.h"
#include "common.h"

const uint32_t rmask = 0x000000ff;
const uint32_t gmask = 0x0000ff00;
const uint32_t bmask = 0x00ff0000;
const uint32_t amask = 0;

FPSmanager fpsManager;
int frameCount = 0;
Uint32 lastTime = 0;
float fps = 0.f;

void set_pixel(SDL_Surface* surface, int x, int y, int color)
{
	Uint8* row8;
	Uint16* row16;
	Uint8* row24;
	Uint32* row32;

	//if (x < 0 || x >= SCREEN_PIXEL_WIDTH || y < 0 || y >=
	//	SCREEN_PIXEL_HEIGHT)
		//return; // Don¡¯t allow overwriting boundaries of the screen

	switch (surface->format->BytesPerPixel)
	{
	case 1:
		row8 = (Uint8*)((Uint8*)surface->pixels + y * surface->pitch + x *
			surface->format->BytesPerPixel);
		*row8 = (Uint8)color;
		break;

	case 2:
		row16 = (Uint16*)((Uint8*)surface->pixels + y * surface->pitch + x *
			surface->format->BytesPerPixel);
		*row16 = (Uint16)color;
		break;

	case 3:
		row24 = (Uint8*)((Uint8*)surface->pixels + y * surface->pitch + x *
			surface->format->BytesPerPixel);
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			row24[0] = (color >> 16) & 0xff;
			row24[1] = (color >> 8) & 0xff;
			row24[2] = color & 0xff;
		}
		else
		{
			row24[0] = color & 0xff;
			row24[1] = (color >> 8) & 0xff;
			row24[2] = (color >> 16) & 0xff;
		}
		break;
	case 4:
		row32 = (Uint32*)((Uint8*)surface->pixels + y * surface->pitch + x *
			surface->format->BytesPerPixel);
		*row32 = (Uint32)color;
		break;
	}
}



void* load_music(char* filename) {
	return Mix_LoadMUS(filename);
}

void play_music(void* data, uint8_t loop) {
	Mix_PlayMusic(data, (loop ? -1 : 0));
}

void stop_music(void* data) {
	Mix_HaltMusic();
}

SDL_Surface* load_png(const char* filename)
{
	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		//printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return 0;
	}

	return IMG_Load(filename);
}

void ubox_wait_for(uint8_t frames)
{
	uint32_t delay = (uint32_t)((frames / 60.0f) * 1000);
	SDL_Delay(delay);
}

void ubox_wait()
{
	Uint32 frameStart = SDL_GetTicks();

	// Calculate FPS
	frameCount++;
	Uint32 currentTime = SDL_GetTicks();
	Uint32 elapsedTime = currentTime - lastTime;
	if (elapsedTime >= 1000) {
		fps = frameCount / (elapsedTime / 1000.0f);

		// Reset the frame count and time
		frameCount = 0;
		lastTime = currentTime;
	}

	SDL_framerateDelay(&fpsManager);
}



