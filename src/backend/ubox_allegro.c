#ifdef ALLEGRO4
#include <ubox.h>
#include <allegro.h>
#include <alpng.h>
#include <mplayer.h>
#include "ubox_common.h"
#include "common.h"


#ifdef WIN32

#pragma comment(lib, "allegro.lib")
#pragma comment(lib, "alpng.lib")

#endif

extern cvector_vector_type(image_info) g_sprite_list;

int32_t g__tick_interval = 40;

volatile int ticks = 0;

BITMAP* g_backbuffer = 0; //Double buffer
int g_color_depth = 32;

BITMAP* tile_surface;
BITMAP* player_surface;
BITMAP* enemy_surface;

BITMAP* enemy_flip_surface;
BITMAP* player_flip_surface;

BITMAP* g_bitmap_tiles = NULL;

void keyupdate();

/* MAIN TIMER FUNCTION */
void ticker() {
	ticks++;
}
END_OF_FUNCTION(ticker);


void redner_stretch() {
	stretch_blit((BITMAP*)g_backbuffer, screen, 0, 0, 256, 192, 0, 0, screen->w, screen->h);
	//blit(g_backbuffer, screen, 0, 0, 0, 0, screen->w, screen->h);
}

void ubox_enable_screen()
{
	redner_stretch();

}







void ubox_put_tile(uint8_t x, uint8_t y, uint8_t tile)
{
	blit(g_bitmap_tiles, g_backbuffer, (int)(tile % g_map_width) * 8, (int)(tile / g_map_width) * 8, x * 8, y * 8, 8, 8); //전면버퍼에 후면버퍼를 블리팅한다.

}

uint32_t TimeLeft(void)
{
	static uint32_t next_time = 0;
	uint32_t now;

	now = ticks;
	if (next_time <= now) {
		next_time = now + g__tick_interval;
		return(0);
	}
	return (next_time - now);
}



void ubox_wait()
{
	
}

void ubox_set_tiles(uint8_t* tiles)
{
	g_tiles = tiles;

	int i = 0, j = 0, k = 0, t = 0;

#ifdef IMAGE_LOAD_MODE
	g_bitmap_tiles = load_png("tiles.png", NULL);

#else
	if (g_bitmap_tiles) {
		destroy_bitmap(g_bitmap_tiles);
		g_bitmap_tiles = 0;
	}

	g_bitmap_tiles = create_bitmap_ex(g_color_depth, 256, 64);

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

					putpixel(g_bitmap_tiles, j * 8 + t, i * 8 + k, makecol(g_tiles_rgb[index], g_tiles_rgb[index + 1], g_tiles_rgb[index + 2]));
			
				}
			}
		}
	}
#endif
}

void ubox_wait_for(uint8_t frames)
{
	uint32_t delay = (uint32_t)((frames / 60.0f) * 1000);
	//SDL_Delay(delay);
}

uint8_t ubox_update() {

	if (ticks) {
		keyupdate();
		ticks--;
		return 1;
	}

	return 0;
}

char keyPressed[KEY_MAX] = { 0 };
char keyReleased[KEY_MAX] = { 0 };
char lastTicksKey[KEY_MAX] = { 0 };
int lastKeyPressed = -1;
int lastKeyReleased = -1;
char anyKeyPressed = 0;

void init_key_values() {
	control_key = 0;
	read_key_7 = 0;
	read_key_4 = 0;

	int i = 0;
	for (; i < KEY_MAX; i++) {
		lastTicksKey[i] = 0;
	}


}





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
}

uint8_t ubox_select_ctl()
{
	if (ticks) {
		keyupdate();
		ticks--;
		
	}

	if (keyPressed[KEY_SPACE]) {
		return UBOX_MSX_CTL_CURSOR;
	}
	if (keyPressed[KEY_M]) {
		return UBOX_MSX_CTL_CURSOR;
	}
	if (keyPressed[KEY_ESC]) {
		return UBOX_MSX_CTL_EXIT;
	}

	return UBOX_MSX_CTL_NONE;
}


void read_control_key()
{

	if (keyPressed[KEY_SPACE]) {
		control_key |= UBOX_MSX_CTL_FIRE1;
	}
	if (keyPressed[KEY_M]) {
		control_key |= UBOX_MSX_CTL_FIRE2;
	}
	if (keyPressed[KEY_UP]) {
		control_key |= UBOX_MSX_CTL_UP;
	}
	if (keyPressed[KEY_LEFT]) {
		control_key |= UBOX_MSX_CTL_LEFT;
	}
	if (keyPressed[KEY_RIGHT]) {
		control_key |= UBOX_MSX_CTL_RIGHT;
	}
	if (keyPressed[KEY_DOWN]) {
		control_key |= UBOX_MSX_CTL_DOWN;
	}

	if (keyReleased[KEY_SPACE]) {
		control_key &= ~(UBOX_MSX_CTL_FIRE1);
	}
	if (keyReleased[KEY_M]) {
		control_key &= ~(UBOX_MSX_CTL_FIRE2);
	}
	if (keyReleased[KEY_UP]) {
		control_key &= ~(UBOX_MSX_CTL_UP);
	}
	if (keyReleased[KEY_LEFT]) {
		control_key &= ~(UBOX_MSX_CTL_LEFT);
	}
	if (keyReleased[KEY_RIGHT]) {
		control_key &= ~(UBOX_MSX_CTL_RIGHT);
	}
	if (keyReleased[KEY_DOWN]) {
		control_key &= ~(UBOX_MSX_CTL_DOWN);
	}
}

uint8_t read_key(int row)
{

	switch (row)
	{
	case 4:
		if (keyPressed[KEY_P]) {
			read_key_4 |= UBOX_MSX_KEY_P;
		}


		if (keyReleased[KEY_P]) {
			read_key_4 &= ~(UBOX_MSX_KEY_P);
		}

		return read_key_4;

		break;
	case 7:
		if (keyPressed[KEY_ESC]) {
			read_key_7 |= UBOX_MSX_KEY_ESC;
		}


		if (keyReleased[KEY_ESC]) {
			read_key_7 &= ~(UBOX_MSX_KEY_ESC);
		}

		return read_key_7;

	}

	return 0;


}

void ubox_putpixel(void* texture, int x, int y, int attr) {

	if(texture)
		putpixel(texture, x, y, makecol(sprite_pallete[attr].r, sprite_pallete[attr].g, sprite_pallete[attr].b));
	else
		putpixel(g_backbuffer, x, y, makecol(sprite_pallete[attr].r, sprite_pallete[attr].g, sprite_pallete[attr].b));
}




void ubox_init_game_system(int screen_width, int screen_height, uint8_t map_width, uint8_t map_height)
{
	g_screen_width = screen_width;
	g_screen_height = screen_height;

	g_map_width = map_width;
	g_map_height = map_height;

	allegro_init();
	install_keyboard();

	install_timer(); //Setup the timer
	LOCK_VARIABLE(ticks); //Set timer variable

	LOCK_FUNCTION(ticker); //Set timer function
	install_int_ex(ticker, BPS_TO_TIMER(30));

	//intialze sound
	if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL)) {
		allegro_message("Sound Error: %s\n", allegro_error);
		return;
	}

	set_volume(255, 255);


#ifdef _WIN32
	g_color_depth = 32;
	set_color_depth(g_color_depth);
	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, screen_width, screen_height, 0, 0)) {
#else
	g_color_depth = 8;
	set_color_depth(g_color_depth); //256 color mode, 8 bits
	if (set_gfx_mode(GFX_AUTODETECT, screen_width, screen_height, 0, 0)) {
#endif
		return;
	}

	BITMAP* buffer = NULL; //create backbuffer surface
	g_backbuffer = create_bitmap_ex(g_color_depth, 256, 192);

	init_key_values();
}

void* load_music(char* filename) {
	return load_sample(filename);
}

void play_music(void* data, uint8_t loop) {
	play_sample(data, 255, 128, 1000, loop);
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

	masked_blit(texture, g_backbuffer, patternIndex * 16, 0,x, y, 16, 16);
	return 0;
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


	uint8_t src_x = (patternIndex % 16) * 16;
	uint8_t src_y = (patternIndex / 16) * 16;


	masked_blit(info->texture, g_backbuffer, src_x, src_y, x, y, 16, 16);
	//blit(info->texture, g_backbuffer, src_x, src_y, x, y, 16, 16);
	return 0;
}


void spman_update()
{
	redner_stretch();
}

extern void init_key_values();

void spman_hide_all_sprites()
{
	init_key_values();
}








void mplayer_play_effect(uint8_t effect_no, uint8_t chan, uint8_t inv_vol)
{

}


void mplayer_play_effect_p(uint8_t effect_no, uint8_t chan, uint8_t inv_vol)
{



}

void mplayer_stop_effect_channel(uint8_t chan)
{

}

uint8_t mplayer_is_sound_effect_on(uint8_t chan)
{
	return 0;
}

#endif

