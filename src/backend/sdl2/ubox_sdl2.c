#include <ubox.h>
#include <expand.h>
#include "ubox_common.h"
#include "ubox_sdl_common.h"

void set_pixel(SDL_Surface* surface, int x, int y, int color);
SDL_Surface* load_png(const char* filename);

SDL_Window* g_window;
SDL_Renderer* g_renderer;
SDL_Texture* g_tile_texture;
SDL_Texture* g_background_texture;
TTF_Font* g_font = 0;


#define ICON_SIZE_X 16
#define ICON_SIZE_Y 16
#define ICON_DEPTH 16
#define ICON_PITCH 32

void set_icon() {	
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

	SDL_Surface* icon = SDL_CreateRGBSurfaceFrom(pixels, ICON_SIZE_X, 
		                                                 ICON_SIZE_Y, 
														 ICON_DEPTH, 
		                                                 ICON_PITCH, 
		                                                 0x0f00, 
		                                                 0x00f0, 
		                                                 0x000f, 
		                                                 0xf000);
	SDL_SetWindowIcon(g_window, icon);
	SDL_FreeSurface(icon);	
}

void ubox_set_tiles_from_file(const char* filename)
{

	SDL_Surface* surface = load_png(filename);
	g_tile_texture = SDL_CreateTextureFromSurface(g_renderer, surface);
	SDL_FreeSurface(surface);

}

void ubox_set_tiles(uint8_t* tiles) {

	g_tiles = tiles;

	if (g_tile_texture)
		SDL_DestroyTexture(g_tile_texture);

	g_tile_texture = NULL;	

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
					int index = ((i * TILE_HEIGHT * TILE_WIDTH * TILESET_COUNT_X) + (k) * TILE_WIDTH * TILESET_COUNT_X + (j * TILE_WIDTH + t)) * 3;

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
		SDL_Log("Creating surface failed: %s", SDL_GetError());
		exit(1);
	}

	g_tile_texture = SDL_CreateTextureFromSurface(g_renderer, surface);
	SDL_FreeSurface(surface);
}


void* create_texture(void* surface) {

	assert(surface != NULL);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);
	SDL_FreeSurface((SDL_Surface*)surface);

	assert(texture != NULL);

	return texture;
	
}

void ubox_put_tile(uint8_t x, uint8_t y, uint8_t tile)
{
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	uint8_t src_x = tile % TILE_MAP_X_COUNT;
	uint8_t src_y = tile / TILE_MAP_X_COUNT;

	srcRect.x = src_x * TILE_SIZE;
	srcRect.y = src_y * TILE_SIZE;
	srcRect.w = TILE_SIZE;
	srcRect.h = TILE_SIZE;

	dstRect.x = x * TILE_SIZE;
	dstRect.y = y * TILE_SIZE;
	dstRect.w = TILE_SIZE;
	dstRect.h = TILE_SIZE;
	
	SDL_SetRenderTarget(g_renderer, g_background_texture);
	SDL_RenderCopy(g_renderer, g_tile_texture, &srcRect, &dstRect);	
	SDL_SetRenderTarget(g_renderer, NULL);
}

extern void ubox_init_game_system(GameSystemInfo* info)
{
	g_system_info = info;

	init_key_values();

#if defined(__ANDROID__)
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
#else	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
#endif
	{
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return;
	}

#if defined(__ANDROID__)
	g_window = SDL_CreateWindow(info->_title_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 448, SDL_WINDOW_FULLSCREEN);
#elif defined(__linux)
	g_window = SDL_CreateWindow(info->_title_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, info->_screen_width, info->_screen_height, SDL_WINDOW_SHOWN);
#else
	g_window = SDL_CreateWindow(info->_title_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		info->_screen_width, info->_screen_height, SDL_WINDOW_SHOWN);
#endif
	if (!g_window)
	{
		SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

#if defined(__ANDROID__)
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
#elif defined(WIN32)
	set_icon();
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
#elif defined(__linux)
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#else
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_SOFTWARE);
#endif

	if (!g_renderer)
	{
		SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	g_background_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, g_system_info->_msx_screen_width, g_system_info->_msx_screen_height);

	SDL_RenderSetLogicalSize(g_renderer, g_system_info->_room_width * TILE_WIDTH, (g_system_info->_room_height) * TILE_HEIGHT);	
	
	SDL_initFramerate(&fpsManager);
	SDL_setFramerate(&fpsManager, g_system_info->_fps);
	int frameCount = 0;
	lastTime = SDL_GetTicks();

	if (TTF_Init() == -1) {
		SDL_Log("Could not initialize TTF: %s", TTF_GetError());
		return;
	}

	g_font = TTF_OpenFont("arial.ttf", 10);
	if (g_font == NULL) {
		SDL_Log("Could not load font: %s", TTF_GetError());
		return;
	}
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		SDL_QuitSubSystem(SDL_INIT_AUDIO);		
		return;
	}
}

void* create_flip_texture(void* texture, int sprite_size) {
	return texture;
}

void* ubox_create_surface(int width, int height, int color_depth) {
		
	SDL_Surface* temp = SDL_CreateRGBSurface(0, width, height, 24, rmask, gmask, bmask, amask);
	SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, 255, 0, 255));
	return temp;
}


void ubox_putpixel(void* texture, uint8_t x, uint8_t y, int attr) {
		
	SDL_SetRenderDrawColor(g_renderer, sprite_pallete[attr].r, sprite_pallete[attr].g, sprite_pallete[attr].b, 255);
	
	if (texture) {
		set_pixel(texture, x, y, (255 << 24) | (sprite_pallete[attr].b << 16) | (sprite_pallete[attr].g << 8) |  sprite_pallete[attr].r);
	}
	else
		SDL_RenderDrawPoint(g_renderer, x, y);
}

void* load_texture(const char* filename)
{
	SDL_Surface* temp = load_png(filename);
	SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, transparent_color.r, transparent_color.g, transparent_color.b));
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, temp);
	SDL_FreeSurface(temp);

	return texture;
}



uint8_t render_sprite_image(void* texture, uint8_t src_x, uint8_t src_y, uint8_t x, uint8_t y, uint8_t flip)
{

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

	SDL_RenderCopyEx(g_renderer, texture, &srcRect, &dstRect, 0, 0, flip);

	return 1;
}

uint8_t render_sprite_texture(void* texture, int x, int y, int patternIndex, uint8_t flip) {

	SDL_Rect srcRect;
	SDL_Rect dstRect;

	uint8_t src_x = patternIndex * SPRITE_WIDTH;
	uint8_t src_y = 0;

	srcRect.x = src_x;
	srcRect.y = src_y;
	srcRect.w = SPRITE_WIDTH;
	srcRect.h = SPRITE_HEIGHT;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = SPRITE_WIDTH;
	dstRect.h = SPRITE_HEIGHT;

	SDL_RenderCopyEx(g_renderer, texture, &srcRect, &dstRect, 0, 0, 0);
	
	return 1;
}

void show_fps() {
	SDL_Color textColor = { 255, 255, 255 };
	char fpsStr[20];
	sprintf(fpsStr, "FPS: %.2f", fps);
	SDL_Surface* surface = TTF_RenderText_Blended(g_font, fpsStr, textColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);

	int width = 0;
	int height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	SDL_Rect destRect = { 200 - width - 10, 0, width, height };
	SDL_RenderCopy(g_renderer, texture, NULL, &destRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
void spman_update() {	
	
	SDL_RenderCopy(g_renderer, g_background_texture, NULL, NULL);
	render_sprites();

	if(g_system_info->_show_fps)
		show_fps();

	SDL_RenderPresent(g_renderer);
	SDL_SetRenderTarget(g_renderer, NULL);	

	
}

void ubox_enable_screen() {
	SDL_RenderCopy(g_renderer, g_background_texture, NULL, NULL);
	SDL_RenderPresent(g_renderer);
	SDL_SetRenderTarget(g_renderer, NULL);
}

uint8_t ubox_update() {

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