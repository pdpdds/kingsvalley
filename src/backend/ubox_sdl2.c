#ifdef SDL2

#include <ubox.h>
#include <expand.h>
#include "ubox_common.h"
#include "ubox_sdl_common.h"

SDL_Window* g_window;
SDL_Renderer* g_renderer;
SDL_Texture* g_tile_texture;

void set_icon()
{
	SDL_Surface* surface;

	//SDL Icon
	Uint16 pixels[16 * 16] =
	{
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
	  0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
	  0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
	  0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
	  0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
	  0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
	  0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
	  0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
	  0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
	  0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
	  0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
	  0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
	  0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
	  0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
	  0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
	  0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
	  0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
	  0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
	  0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
	  0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
	  0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
	  0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
	  0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
	};
	surface = SDL_CreateRGBSurfaceFrom(pixels, 16, 16, 16, 16 * 2, 0x0f00, 0x00f0, 0x000f, 0xf000);

	SDL_FreeSurface(surface);
}

void ubox_enable_screen()
{
	SDL_RenderPresent(g_renderer);
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


	g_tile_texture = SDL_CreateTextureFromSurface(g_renderer, temp);
	SDL_FreeSurface(temp);

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

	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)g_tiles_rgb, 256, 64, 24, 3 * 256,
		rmask, gmask, bmask, amask);

	if (surface == NULL) {
		SDL_Log("Creating surface failed: %s", SDL_GetError());		
		exit(1);
	}

	if(g_tile_texture)
		SDL_DestroyTexture(g_tile_texture);

	g_tile_texture = SDL_CreateTextureFromSurface(g_renderer, surface);

	SDL_FreeSurface(surface);

#endif

}


void* create_sdl_texture(void* texture) {

	return SDL_CreateTextureFromSurface(g_renderer, texture);
	
}


void ubox_put_tile(uint8_t x, uint8_t y, uint8_t tile)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	uint8_t src_x = tile % g_room_width;
	uint8_t src_y = tile / g_room_width;


	srcRect.x = src_x * 8;
	srcRect.y = src_y * 8;
	srcRect.w = 8;
	srcRect.h = 8;

	dstRect.x = x * 8;
	dstRect.y = y * 8;
	dstRect.w = 8;
	dstRect.h = 8;


	SDL_RenderCopy(g_renderer, g_tile_texture, &srcRect, &dstRect);

}


extern void ubox_init_game_system(const char* szTitle, int screen_width, int screen_height, uint8_t room_width, uint8_t room_height, uint8_t map_width, uint8_t map_height)
{
	g_room_width = room_width;
	g_room_height = room_height;
	g_map_width = map_width;
	g_map_height = map_height;

	control_key = 0;
	read_key_7 = 0;
	read_key_4 = 0;

#if defined(__ANDROID__)
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
#else	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
#endif
	{
		//ubox_log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return;
	}

#if defined(__ANDROID__)
	g_window = SDL_CreateWindow(szTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 448, SDL_WINDOW_FULLSCREEN);
#elif defined(__linux)
	g_window = SDL_CreateWindow(szTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
#else
	g_window = SDL_CreateWindow(szTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screen_width, screen_height, SDL_WINDOW_SHOWN);
#endif
	if (g_window == NULL)
	{
		//printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

#if defined(__ANDROID__)
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
#elif defined(WIN32)
	set_icon();
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#elif defined(__linux)
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#else
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_SOFTWARE);
#endif

	if (g_renderer == NULL)
	{
		//printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	SDL_RenderSetLogicalSize(g_renderer, g_room_width * 8, (g_room_height + 2) * 8);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		SDL_QuitSubSystem(SDL_INIT_AUDIO);		
		return;
	}
}

void* create_flip_texture(void* texture, int sprite_size) {
	return texture;
}

void* ubox_create_texture(int width, int height) {
	
	uint32_t rmask = 0x000000ff;
	uint32_t gmask = 0x0000ff00;
	uint32_t bmask = 0x00ff0000;
	uint32_t amask = 0;

	SDL_Surface* temp = SDL_CreateRGBSurface(0, width, height, 24, rmask, gmask, bmask, amask);
	SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 255, 0, 255));
	return temp;
}



void ubox_putpixel(void* texture, int x, int y, int attr) {
	
	SDL_SetRenderDrawColor(g_renderer, sprite_pallete[attr].r, sprite_pallete[attr].g, sprite_pallete[attr].b, 255);
	if (texture) {

		set_pixel(texture, x, y, (255 << 24) |(sprite_pallete[attr].r << 16) | (sprite_pallete[attr].g << 8) |  sprite_pallete[attr].b);
	}
	else
		SDL_RenderDrawPoint(g_renderer, x, y);
}


void* load_texture(const char* filename)
{
	SDL_Surface* temp = load_png(filename);
	//SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 28, 28, 28));
	SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 255, 0, 255));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, temp);
	SDL_FreeSurface(temp);

	return texture;
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

	SDL_RenderCopyEx(g_renderer, info->texture, &srcRect, &dstRect, 0, 0, flip);

	return 1;
}

uint8_t render_sprite_texture(void* texture, int x, int y, int patternIndex, uint8_t flip) {

	SDL_Rect srcRect;
	SDL_Rect dstRect;


	uint8_t src_x = patternIndex * 16;
	uint8_t src_y = 0;


	srcRect.x = src_x;
	srcRect.y = src_y;
	srcRect.w = 16;
	srcRect.h = 16;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = 16;
	dstRect.h = 16;

	SDL_RenderCopyEx(g_renderer, texture, &srcRect, &dstRect, 0, 0, 0);
	
	return 1;
}


void spman_update()
{

	SDL_RenderPresent(g_renderer);
}



#endif