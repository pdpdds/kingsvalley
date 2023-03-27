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
SDL_Surface* g_tile_set;

SDL_Surface* g_tile_surface = 0; 
SDL_Surface* g_final_surface = 0;

void* ubox_create_surface(int width, int height,int color_depth) {

	SDL_Surface* temp = SDL_CreateRGBSurface(0, width, height, 24, rmask, gmask, bmask, amask);
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, transparent_color.r, transparent_color.g, transparent_color.b));
	return temp;
}


void* create_flip_texture(void* texture, int sprite_size) {

	SDL_Surface* flip_texture = rotozoomSurfaceXY(texture, 0, -1.0f, 1.0f, 0);	
	SDL_SetColorKey(flip_texture, SDL_SRCCOLORKEY, SDL_MapRGB(flip_texture->format, transparent_color.r, transparent_color.g, transparent_color.b));

	return flip_texture;
}

void* load_texture(const char* filename)
{
	SDL_Surface* temp = load_png(filename);	
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, transparent_color.r, transparent_color.g, transparent_color.b));
	
	return temp;
}

void* ubox_create_texture(int width, int height) {

	SDL_Surface* temp = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, DISPLAY_COLOR_DEPTH, rmask, gmask, bmask, amask);
	SDL_SetColorKey(temp, SDL_SRCCOLORKEY, SDL_MapRGB(temp->format, transparent_color.r, transparent_color.g, transparent_color.b));
	return temp;
}

void ubox_set_tiles_from_file(const char* filename) {
	if (g_tile_set)
		SDL_FreeSurface(g_tile_set);

	g_tile_set = load_png(filename);
}


void ubox_putpixel(void* texture, uint8_t x, uint8_t y, int attr) {

	if (texture) {
		set_pixel(texture, x, y, (255 << 24) | (sprite_pallete[attr].b << 16) | (sprite_pallete[attr].g << 8) | sprite_pallete[attr].r);
	}
	else
		set_pixel(g_final_surface, x, y, (255 << 24) | (sprite_pallete[attr].b << 16) | (sprite_pallete[attr].g << 8) | sprite_pallete[attr].r);
}


uint8_t render_sprite_image(void* texture, uint8_t src_x, uint8_t src_y, uint8_t x, uint8_t y, uint8_t flip) {	
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	
	srcRect.x = src_x;
	srcRect.y = src_y;
	srcRect.w = SPRITE_WIDTH;
	srcRect.h = SPRITE_HEIGHT;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = SPRITE_WIDTH;
	dstRect.h = SPRITE_HEIGHT;
	
	SDL_BlitSurface(texture, &srcRect, screen, &dstRect);
	
	return 1;
}


void ubox_set_tiles(uint8_t* tiles) {

	g_tiles = tiles;

	int i = 0, j = 0, k = 0, t = 0;
	for (i = 0; i < TILESET_COUNT_Y; i++) {
		for (j = 0; j < TILESET_COUNT_X; j++) {
			for (k = 0; k < PIXELS_PER_TILE; k++) {
				uint8_t pixel = g_tiles[(i * TILESET_COUNT_Y * TILESET_COUNT_X) + (j * PIXELS_PER_TILE) + k];
				uint8_t color = g_tiles_colors[(i * TILESET_COUNT_Y * TILESET_COUNT_X) + (j * PIXELS_PER_TILE) + k];

				uint8_t color1 = (color >> 4);
				uint8_t color2 = ((uint8_t)(color << 4)) >> 4;

				for (t = 0; t < 8; t++) {
					uint8_t mask = 1 << (7 - t);
					int index = ((i * TILE_HEIGHT * TILE_WIDTH * TILESET_COUNT_X) + (k)*TILE_WIDTH * TILESET_COUNT_X + (j * TILE_WIDTH + t)) * 3;

					uint8_t pixel_color = (pixel & mask) ? color1 : color2;

					g_tiles_rgb[index] = sprite_pallete[pixel_color].r;
					g_tiles_rgb[index + 1] = sprite_pallete[pixel_color].g;
					g_tiles_rgb[index + 2] = sprite_pallete[pixel_color].b;
				}
			}
		}
	}

	//24bit Surface
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)g_tiles_rgb, TILESET_COUNT_X * TILE_WIDTH, TILESET_COUNT_Y * TILE_HEIGHT, 24, 3 * TILESET_COUNT_X * TILE_WIDTH,
		rmask, gmask, bmask, amask);

	if (surface == NULL) {		
		exit(1);
	}

	g_tile_set = surface;
}



void ubox_put_tile(uint8_t x, uint8_t y, uint8_t tile)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	uint8_t src_x = tile % g_system_info->_room_width;
	uint8_t src_y = tile / g_system_info->_room_width;


	srcRect.x = src_x * TILE_SIZE;
	srcRect.y = src_y * TILE_SIZE;
	srcRect.w = TILE_SIZE;
	srcRect.h = TILE_SIZE;


	dstRect.x = x * TILE_SIZE;
	dstRect.y = y * TILE_SIZE;
	dstRect.w = TILE_SIZE;
	dstRect.h = TILE_SIZE;

	SDL_BlitSurface(g_tile_set, &srcRect, g_tile_surface, &dstRect);

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


void ubox_init_game_system(GameSystemInfo* info) {
	g_system_info = info;

	init_key_values();

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		//printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return;
	}


#ifdef _DEBUG
	screen = SDL_SetVideoMode(g_system_info->_screen_width, g_system_info->_screen_height, DISPLAY_COLOR_DEPTH, SDL_SWSURFACE);
#else	
#if defined(DJGPP)
	screen = SDL_SetVideoMode(g_system_info->_screen_width, g_system_info->_screen_height, DISPLAY_COLOR_DEPTH, SDL_SWSURFACE | SDL_FULLSCREEN);
#else
	screen = SDL_SetVideoMode(g_system_info->_screen_width, g_system_info->_screen_height, DISPLAY_COLOR_DEPTH, SDL_SWSURFACE);
#endif
#endif
	
#if defined(WIN32)
	SDL_WM_SetCaption(info->_title_name, NULL);
	SDL_WM_SetIcon(SDL_LoadBMP("kings.bmp"), NULL);
#endif

	SDL_initFramerate(&fpsManager);
	SDL_setFramerate(&fpsManager, g_system_info->_fps);	
	lastTime = SDL_GetTicks();
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0) {
			SDL_QuitSubSystem(SDL_INIT_AUDIO);
			exit(0);	
	}

	g_tile_surface = ubox_create_texture(g_system_info->_msx_screen_width, g_system_info->_msx_screen_height);
	g_final_surface = ubox_create_texture(g_system_info->_msx_screen_width, g_system_info->_msx_screen_height);
	
}

void render_present() {
	SDL_BlitSurface(g_tile_surface, NULL, g_final_surface, NULL);
	render_sprites();

#if defined(DJGPP)
	SDL_BlitSurface(g_final_surface, NULL, screen, NULL);
#else
	SDL_Surface* scaled_surface = rotozoomSurfaceXY(g_final_surface, 0, 640.0f / (float)g_system_info->_msx_screen_width, 480.0f / (float)g_system_info->_msx_screen_height, 0);
	SDL_BlitSurface(scaled_surface, NULL, screen, NULL);
	SDL_FreeSurface(scaled_surface);
#endif
	SDL_Flip(screen);
}

void spman_update() {
	render_present();
}

void ubox_enable_screen() {
	render_present();
}

void* create_texture(void* surface) {

	return surface;
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
				g_key_info._control_key |= UBOX_MSX_CTL_FIRE1;
				break;
			case SDLK_m:
				g_key_info._control_key |= UBOX_MSX_CTL_FIRE2;
				break;
			case SDLK_UP:
				g_key_info._control_key |= UBOX_MSX_CTL_UP;
				break;
			case SDLK_LEFT:
				g_key_info._control_key |= UBOX_MSX_CTL_LEFT;
				break;
			case SDLK_RIGHT:
				g_key_info._control_key |= UBOX_MSX_CTL_RIGHT;
				break;
			case SDLK_DOWN:
				g_key_info._control_key |= UBOX_MSX_CTL_DOWN;
				break;
			case SDLK_ESCAPE:
				g_key_info._read_key_7 |= UBOX_MSX_KEY_ESC;
				g_key_info._control_key |= UBOX_MSX_CTL_EXIT;
				break;
			case SDLK_z:
				g_key_info._read_key_5 |= UBOX_MSX_KEY_Z;
				break;
			}
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_FIRE1);
				break;
			case SDLK_m:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_FIRE2);
				break;
			case SDLK_UP:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_UP);
				break;
			case SDLK_LEFT:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_LEFT);
				break;
			case SDLK_RIGHT:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_RIGHT);
				break;
			case SDLK_DOWN:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_DOWN);
				break;
			case SDLK_ESCAPE:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_EXIT);
				g_key_info._read_key_7 &= ~(UBOX_MSX_KEY_ESC);
				break;
			case SDLK_z:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_EXIT);
				g_key_info._read_key_5 &= ~(UBOX_MSX_KEY_Z);
				break;
			}
			break;
		}
	}

	return 1;
}
