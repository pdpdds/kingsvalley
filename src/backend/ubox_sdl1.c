#ifdef SDL1
#include <ubox.h>
#include <expand.h>
#include "ubox_common.h"


#include "ubox_sdl_common.h"
#include "SDL_gfxPrimitives.h"
#include "sdl_rotozoom.h"

#if defined(WIN32)
#pragma comment(lib, "sdlimage.lib")
#pragma comment(lib, "sdl.lib")
#pragma comment(lib, "sdlmixer.lib")
#endif

SDL_Surface* screen;
SDL_Surface* tile_surface;


void* create_flip_texture(void* texture, int sprite_size) {

	SDL_Surface* flip_texture = rotozoomSurfaceXY(texture, 0, -1.0f, 1.0f, 0);	

	SDL_SetColorKey(flip_texture, SDL_SRCCOLORKEY, SDL_MapRGB(flip_texture->format, 255, 0, 255));

	return flip_texture;
}

void* load_texture(const char* filename)
{
	SDL_Surface* temp = load_png(filename);
	//SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 28, 28, 28));
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 255, 0, 255));
	
	
	return temp;
}



void ubox_putpixel(void* texture, int x, int y, int attr) {

	if (texture) {

		set_pixel(texture, x, y, (255 << 24) | (sprite_pallete[attr].r << 16) | (sprite_pallete[attr].g << 8) | sprite_pallete[attr].b);
	}
	else
		set_pixel(screen, x, y, (255 << 24) | (sprite_pallete[attr].r << 16) | (sprite_pallete[attr].g << 8) | sprite_pallete[attr].b);
		//set_pixel(screen, x, y, (255 << 24) | (sprite_pallete[attr].r << 16) | (sprite_pallete[attr].g << 8) | sprite_pallete[attr].b);
}

void* ubox_create_texture(int width, int height) {

	uint32_t rmask = 0x000000ff;
	uint32_t gmask = 0x0000ff00;
	uint32_t bmask = 0x00ff0000;
	uint32_t amask = 0;

	SDL_Surface* temp = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, DISPLAY_COLOR_DEPTH, rmask, gmask, bmask, amask);
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, 255, 0, 255));
	return temp;
}


void ubox_enable_screen()
{
	SDL_Flip(screen);

}


uint8_t render_sprite_type(int type, int x, int y, int patternIndex, uint8_t flip)
{
	image_info* vec_info = (image_info*)g_sprite_list;
	uint8_t found = 0;
	;
	image_info* info = cvector_begin(vec_info);
	for (; info != cvector_end(vec_info); ++info) {

		if (info->sprite_index == type) {
			found = 1;
			break;
		}
	}

	assert(found);

	SDL_Rect srcRect;
	SDL_Rect dstRect;


	uint8_t src_x = (patternIndex % 16) * 16;
	uint8_t src_y = (patternIndex / 16) * 16;


	srcRect.x = src_x;
	srcRect.y = src_y;
	srcRect.w = 16;
	srcRect.h = 16;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = 16;
	dstRect.h = 16;
	
	
	SDL_BlitSurface(info->texture, &srcRect, screen, &dstRect);
	return 1;
}


void ubox_set_tiles(uint8_t* tiles)
{
	int i = 0, j = 0, k = 0, t = 0;
	uint32_t rmask = 0x000000ff;
	uint32_t gmask = 0x0000ff00;
	uint32_t bmask = 0x00ff0000;
	uint32_t amask = 0;

	g_tiles = tiles;


#ifdef IMAGE_LOAD_MODE
	SDL_Surface* temp;
	temp = load_png("tiles.png");

	tile_surface = temp;	
	

#else
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 32; j++)
		{
			for (k = 0; k < 8; k++)
			{
				uint8_t tile_pixels = g_tiles[(i * 8 * 32) + (j * 8) + k];
				uint8_t tile_color = g_tiles_colors[(i * 8 * 32) + (j * 8) + k];

				uint8_t color = (tile_color >> 4);
				uint8_t color2 = (tile_color << 4);
				color2 = color2 >> 4;

				for (t = 0; t < 8; t++)
				{
					uint8_t mask = 1 << (7 - t);
					int index = ((i * 8 * 8 * 32) + (k) * 8 * 32 + (j * 8 + t)) * 3;

					uint8_t pixel_color = (tile_pixels & mask) ? color : color2;

					g_tiles_rgb[index] = sprite_pallete[pixel_color].r;
					g_tiles_rgb[index + 1] = sprite_pallete[pixel_color].g;
					g_tiles_rgb[index + 2] = sprite_pallete[pixel_color].b;
				}
			}
		}
	}

	tile_surface = SDL_CreateRGBSurfaceFrom((void*)g_tiles_rgb, 256, 64, DISPLAY_COLOR_DEPTH, 3 * 256,
		rmask, gmask, bmask, amask);

	if (tile_surface == NULL) {
		exit(1);
	}

#endif

}



void ubox_put_tile(uint8_t x, uint8_t y, uint8_t tile)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	uint8_t src_x = tile % g_map_width;
	uint8_t src_y = tile / g_map_width;


	srcRect.x = src_x * 8;
	srcRect.y = src_y * 8;
	srcRect.w = 8;
	srcRect.h = 8;


	dstRect.x = x * 8;
	dstRect.y = y * 8;
	dstRect.w = 8;
	dstRect.h = 8;

	SDL_BlitSurface(tile_surface, &srcRect, screen, &dstRect);

}





// variable declarations
static Uint8* audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play


void my_audio_callback(void* userdata, Uint8* stream, int len) {

	if (audio_len == 0)
		return;

	len = (len > audio_len ? audio_len : len);
	//SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}


void ubox_init_game_system(int screen_width, int screen_height, uint8_t map_width, uint8_t map_height)
{
	g_map_width = map_width;
	g_map_height = map_height;

	control_key = 0;
	read_key_7 = 0;
	read_key_4 = 0;
	

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		//printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return;
	}


#ifdef _DEBUG
	screen = SDL_SetVideoMode(screen_width, screen_height, DISPLAY_COLOR_DEPTH, SDL_SWSURFACE);
#else	
	screen = SDL_SetVideoMode(screen_width, screen_height, DISPLAY_COLOR_DEPTH, SDL_SWSURFACE | SDL_FULLSCREEN);
#endif
	/*if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0) {
			SDL_QuitSubSystem(SDL_INIT_AUDIO);
			exit(0);	
	}*/

	//Mix_Init(0);

	//Mix_Music* music = Mix_LoadMUS("audio/map.wav");

	

	/*Mix_Music* music = Mix_LoadMUS("audio/map.wav");
	if (!music)
		exit(0);
	Mix_PlayMusic(music, 1);
	while (1) {
		SDL_Delay(100);
	}*/
	
//#if !defined(SDL1) && !defined(linux)
	//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
	//	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	//	exit(0);
	//}
	/*SDL_AudioSpec wav_spec;
	Uint32 wavLength;
	Uint8* wavBuffer;

	SDL_LoadWAV("bgm.wav", &wav_spec, &wavBuffer, &wavLength);

	// set the callback function
	wav_spec.callback = my_audio_callback;
	wav_spec.userdata = NULL;
	// set our global static variables
	audio_pos = wavBuffer; // copy sound buffer
	audio_len = wavLength; // copy file length

	// Open the audio device 
	if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
		//fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		exit(-1);
	}

	printf("format, %d\n", wav_spec.format);
	printf("frequency, %d\n", wav_spec.freq);

	// Start playing 
	SDL_PauseAudio(0);

	// wait until we're don't playing
	while (audio_len > 0) {
		SDL_Delay(100);
	}*/


	

//#endif
	
}

void spman_update()
{

	SDL_Flip(screen);

}



#endif