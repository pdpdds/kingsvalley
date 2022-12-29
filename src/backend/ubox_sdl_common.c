#include "ubox_sdl_common.h"
#include <ubox.h>
#include "common.h"

#if defined(SDL1) || defined(SDL2)
/*void set_pixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
{
	Uint32* const target_pixel = (Uint32*)((Uint8*)surface->pixels
		+ y * surface->pitch
		+ x * surface->format->BytesPerPixel);
	*target_pixel = pixel;
}*/



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

uint8_t ubox_select_ctl()
{
	if (control_key == 0)
		return UBOX_MSX_CTL_NONE;

	return control_key;
}

void read_control_key()
{

	return;
}


uint8_t read_key(int row)
{
	return read_key_7;
}

uint8_t ubox_update() {

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{

			case SDLK_SPACE:
				control_key |= UBOX_MSX_CTL_FIRE1;
				break;
			case SDLK_m:
				control_key |= UBOX_MSX_CTL_FIRE2;
				break;
			case SDLK_UP:
				control_key |= UBOX_MSX_CTL_UP;
				break;
			case SDLK_LEFT:
				control_key |= UBOX_MSX_CTL_LEFT;
				break;
			case SDLK_RIGHT:
				control_key |= UBOX_MSX_CTL_RIGHT;
				break;
			case SDLK_DOWN:
				control_key |= UBOX_MSX_CTL_DOWN;
				break;
			case SDLK_ESCAPE:
				read_key_7 |= UBOX_MSX_KEY_ESC;
				control_key |= UBOX_MSX_CTL_EXIT;
				break;
			}
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				control_key &= ~(UBOX_MSX_CTL_FIRE1);
				break;
			case SDLK_m:
				control_key &= ~(UBOX_MSX_CTL_FIRE2);
				break;
			case SDLK_UP:
				control_key &= ~(UBOX_MSX_CTL_UP);
				break;
			case SDLK_LEFT:
				control_key &= ~(UBOX_MSX_CTL_LEFT);
				break;
			case SDLK_RIGHT:
				control_key &= ~(UBOX_MSX_CTL_RIGHT);
				break;
			case SDLK_DOWN:
				control_key &= ~(UBOX_MSX_CTL_DOWN);
				break;
			case SDLK_ESCAPE:
				control_key &= ~(UBOX_MSX_CTL_EXIT);
				read_key_7 &= ~(UBOX_MSX_KEY_ESC);
				break;
			}
			break;
		}
	}

	return 1;
}



void spman_hide_all_sprites()
{
	control_key = 0;
	read_key_7 = 0;
	read_key_4 = 0;
}


void mplayer_play_effect(uint8_t effect_no, uint8_t chan, uint8_t inv_vol)
{

}


void mplayer_play_effect_p(uint8_t effect_no, uint8_t chan, uint8_t inv_vol)
{

	/*if (effect_no == EFX_DEAD)
	{
		if (!effect_dead) {
			effect_dead = Mix_LoadWAV("audio/Caught.wav");
			if (effect_dead == NULL)
			{
				return;
			}
		}

		Mix_PlayChannel(-1, effect_dead, 0);

	}

	else if (effect_no == EFX_DIG)
	{
		if (!effect_dig) {
			effect_dig = Mix_LoadWAV("audio/Dig.wav");
			if (effect_dig == NULL)
			{
				return;
			}
		}

		Mix_PlayChannel(-1, effect_dig, 0);

	}
	else if (effect_no == EFX_DOOR)
	{
		if (!effect_door) {
			effect_door = Mix_LoadWAV("audio/door.wav");
			if (effect_door == NULL)
			{
				return;
			}
		}

		Mix_PlayChannel(-1, effect_door, 0);

	}*/


}

void mplayer_stop_effect_channel(uint8_t chan)
{

}

uint8_t mplayer_is_sound_effect_on(uint8_t chan)
{
	return 0;
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




Uint32 TimeLeft(void)
{
	static Uint32 next_time = 0;

	if (next_time == 0) {
		next_time = TICK_INTERVAL;
	}

	Uint32 now;

	now = SDL_GetTicks();
	if (next_time <= now) {
		next_time = now + TICK_INTERVAL;
		return 0;
	}
	return (next_time - now);
}

void ubox_wait()
{
	SDL_Delay(TimeLeft());
}

void ubox_wait_for(uint8_t frames)
{
	uint32_t delay = (uint32_t)((frames / 60.0f) * 1000);
	SDL_Delay(delay);
}


#endif