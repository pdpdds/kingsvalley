#include "ubox_common.h"
#include "common.h"
#include <allegro.h>
#include <alpng.h>

#ifdef WIN32
#pragma comment(lib, "alleg.lib")
#pragma comment(lib, "alpng.lib")
#endif

int32_t g__tick_interval = 40;

volatile int ticks = 0;
volatile int update_flag = 0;

BITMAP* g_tile_surface = 0;
BITMAP* g_final_surface = 0;

BITMAP* g_tile_set = NULL;

void keyupdate();

/* MAIN TIMER FUNCTION */
void ticker() {
	ticks++;
	update_flag = 1;
}
END_OF_FUNCTION(ticker);


void redner_stretch() {
#if defined(DJGPP)
	stretch_blit((BITMAP*)g_final_surface, screen, 0, 0, g_system_info->_msx_screen_width, g_system_info->_msx_screen_height, 0, 0, screen->w, g_system_info->_msx_screen_height);
#else
	stretch_blit((BITMAP*)g_final_surface, screen, 0, 0, g_system_info->_msx_screen_width, g_system_info->_msx_screen_height, 0, 0, screen->w, screen->h);
#endif
}

void ubox_put_tile(uint8_t x, uint8_t y, uint8_t tile) {
	blit(g_tile_set, g_tile_surface, (int)(tile % g_system_info->_room_width) * 8, (int)(tile / g_system_info->_room_width) * 8, x * 8, y * 8, 8, 8); //전면버퍼에 후면버퍼를 블리팅한다.
}

uint32_t TimeLeft(void) {
	return 0;
	
	/*static uint32_t next_time = 0;
	uint32_t now;

	now = ticks;
	if (next_time < now) {
		next_time = now + g__tick_interval;
		return(0);
	}
	return (next_time - now);*/
}

void ubox_wait()
{
	//while(!TimeLeft());
}

void* ubox_create_surface(int width, int height, int color_depth) {

	return create_bitmap_ex(color_depth, width, height);
}

void ubox_set_tiles_from_file(const char* filename) {

	if (g_tile_set) {
		destroy_bitmap(g_tile_set);
		g_tile_set = 0;
	}

	g_tile_set = load_png(filename, NULL);

}

void ubox_set_tiles(uint8_t* tiles) {

	if (tiles == NULL)
		return;
	
	if (g_tile_set) {
		destroy_bitmap(g_tile_set);
		g_tile_set = 0;
	}

	g_tiles = tiles;
	g_tile_set = create_bitmap_ex(g_system_info->_color_depth, 256, 64);

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

					//putpixel(g_tile_set, j * 8 + t, i * 8 + k, makeacol_depth(g_color_depth, g_tiles_rgb[index], g_tiles_rgb[index + 1], g_tiles_rgb[index + 2], 0));
					putpixel(g_tile_set, j * 8 + t, i * 8 + k, makecol8(g_tiles_rgb[index], g_tiles_rgb[index + 1], g_tiles_rgb[index + 2]));
				}
			}
		}
	}	
}

void ubox_wait_for(uint8_t frames)
{
	uint32_t delay = (uint32_t)((frames / 60.0f) * 1000);
	rest(delay);		
}


#define FPS 30
#define FRAME_TIME (1000 / FPS)
long old_time = 0, current_time = 0, dt;
uint8_t ubox_update() {

	while (!update_flag);

	update_flag = 0;

	/*old_time = current_time;
	current_time = clock(); // 현재 시간 가져오기
	dt = current_time - old_time;

	if((FRAME_TIME - dt) > 0)
		rest(FRAME_TIME - dt);*/

	keyupdate();
	return 1;
}

char keyPressed[KEY_MAX] = { 0 };
char keyReleased[KEY_MAX] = { 0 };
char lastTicksKey[KEY_MAX] = { 0 };
int lastKeyPressed = -1;
int lastKeyReleased = -1;
char anyKeyPressed = 0;

void keyupdate() {
	// Reset last key
	lastKeyPressed = -1;
	lastKeyReleased = -1;
	anyKeyPressed = 0;


	// Check key just pressed
	for (int i = 0; i < KEY_MAX; i++) {
		// Clear old values
		keyPressed[i] = 0;
		keyReleased[i] = 0;

		// Wheres the any key?
		if (key[i])
			anyKeyPressed = 1;

		// Pressed since last tick?
		if (key[i] == -1 && lastTicksKey[i] == 0) {
			keyPressed[i] = -1;
			lastKeyPressed = i;
			//std::cout << "Key: " << i << " pressed. \n";
		}

		// Released since last tick?
		if (key[i] == 0 && lastTicksKey[i] == -1) {
			keyReleased[i] = -1;
			lastKeyReleased = i;
			//std::cout << "Key: " << i << " released. \n";
		}
	}

	// Get new values
	for (int i = 0; i < KEY_MAX; i++) {
		// Key changed
		if (lastTicksKey[i] != (char)key[i]) {
			//std::cout << "Key: " << i << " was " << lastTicksKey[i] << " and became " << (bool)key[i] << "\n";
			lastTicksKey[i] = key[i];
		}
	}

	for (int i = 0; i < KEY_MAX; i++) {
		if(keyPressed[i] == -1 && lastTicksKey[i] == key[i]) {
			switch (i) {
			case KEY_SPACE:
				g_key_info._control_key |= UBOX_MSX_CTL_FIRE1;
				break;
			case KEY_M:
				g_key_info._control_key |= UBOX_MSX_CTL_FIRE2;
				break;
			case KEY_UP:
				g_key_info._control_key |= UBOX_MSX_CTL_UP;
				break;
			case KEY_LEFT:
				g_key_info._control_key |= UBOX_MSX_CTL_LEFT;
				break;
			case KEY_RIGHT:
				g_key_info._control_key |= UBOX_MSX_CTL_RIGHT;
				break;
			case KEY_DOWN:
				g_key_info._control_key |= UBOX_MSX_CTL_DOWN;
				break;
			case KEY_ESC:
				g_key_info._read_key_7 |= UBOX_MSX_KEY_ESC;
				g_key_info._control_key |= UBOX_MSX_CTL_EXIT;
				break;
			case KEY_Z:
				g_key_info._read_key_5 |= UBOX_MSX_KEY_Z;
				break;
			case KEY_P:
				g_key_info._read_key_4 |= UBOX_MSX_KEY_P;
				break;
			}
			
		}

		if(keyReleased[i] == -1 && lastTicksKey[i] == key[i]) {
			switch (i) {
			case KEY_SPACE:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_FIRE1);
				break;
			case KEY_M:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_FIRE2);
				break;
			case KEY_UP:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_UP);
				break;
			case KEY_LEFT:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_LEFT);
				break;
			case KEY_RIGHT:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_RIGHT);
				break;
			case KEY_DOWN:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_DOWN);
				break;
			case KEY_ESC:
				g_key_info._control_key &= ~(UBOX_MSX_CTL_EXIT);
				g_key_info._read_key_7 &= ~(UBOX_MSX_KEY_ESC);
				break;
			case KEY_Z:
				g_key_info._read_key_5 &= ~(UBOX_MSX_KEY_Z);
				break;
			case KEY_P:
				g_key_info._read_key_4 &= ~(UBOX_MSX_KEY_P);
				break;
			}
		}
	}

}

void ubox_putpixel(void* texture, uint8_t x, uint8_t y, int attr) {

	if(texture)
		putpixel(texture, x, y, makecol8(sprite_pallete[attr].r, sprite_pallete[attr].g, sprite_pallete[attr].b));
	else
		putpixel(g_final_surface, x, y, makecol8(sprite_pallete[attr].r, sprite_pallete[attr].g, sprite_pallete[attr].b));
}

void ubox_init_game_system(GameSystemInfo* info)
{
	g_system_info = info;

	allegro_init();
	install_keyboard();

	install_timer(); //Setup the timer
	LOCK_VARIABLE(ticks); //Set timer variable
	
	LOCK_FUNCTION(ticker); //Set timer function
	install_int_ex(ticker, BPS_TO_TIMER(g_system_info->_fps));

	//intialze sound
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL)) {
		allegro_message("Sound Error: %s\n", allegro_error);
		return;
	}

	set_volume(255, 255);

#ifdef _WIN32
	set_color_depth(g_system_info->_color_depth);
	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, g_system_info->_screen_width, g_system_info->_screen_height, 0, 0)) {
#else
	set_color_depth(g_system_info->_color_depth); 
	if (set_gfx_mode(GFX_AUTODETECT, g_system_info->_screen_width, g_system_info->_screen_height, 0, 0)) {
#endif
		return;
	}

	set_window_title(g_system_info->_title_name);	
	
	g_tile_surface = create_bitmap_ex(g_system_info->_color_depth, g_system_info->_msx_screen_width, g_system_info->_msx_screen_height);
	g_final_surface = create_bitmap_ex(g_system_info->_color_depth, g_system_info->_msx_screen_width, g_system_info->_msx_screen_height);

	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);

	init_key_values();
}

void* load_music(char* filename) {
	return load_sample(filename);
}

void play_music(void* data, uint8_t loop) {
	//play_sample(data, 255, 128, 1000, loop);
	play_sample(data, 255, 0, 1000, loop);
}

void stop_music(void* data) {
	stop_sample(data);
}

void* ubox_create_texture(int width, int height) {
	return create_bitmap(width, height);
}


void* create_flip_texture(void* texture, int sprite_size)
{
	BITMAP* original_texture = texture;
	BITMAP* flip_texture = create_bitmap(original_texture->w, original_texture->h);

	int sprite_count = original_texture->w / sprite_size;

	assert(sprite_count > 0);

	uint32_t color = 0;
	for(int i = 0; i < sprite_count; i++)
	for (int y = 0; y < 16; y++)
		for (int x = 0; x < 16; x++)
		{
			color = getpixel(original_texture, x + i * 16, y);
			putpixel(flip_texture, i * 16 + 15 - x, y, color);	
		}

	return flip_texture;
}

void* load_texture(const char* filename) {
	
	return load_png(filename, NULL);
}


uint8_t render_sprite_texture(void* texture, int x, int y, int patternIndex, uint8_t flip) {

	masked_blit(texture, g_tile_surface, patternIndex * 16, 0,x, y, 16, 16);
	return 0;
}

void spman_update() {
	blit(g_tile_surface, g_final_surface, 0, 0, 0, 0, screen->w, screen->h);
	render_sprites();
	redner_stretch();
	
}

void ubox_enable_screen() {
	blit(g_tile_surface, g_final_surface, 0, 0, 0, 0, screen->w, screen->h);
	redner_stretch();

}

void* create_texture(void* surface) {

	return surface;
}

//direct image manipulation
uint8_t render_sprite_image(void* texture, uint8_t src_x, uint8_t src_y, uint8_t x, uint8_t y, uint8_t flip) {
	masked_blit(texture, g_final_surface, src_x, src_y, x, y, 16, 16);
	
	return 0;
}