#pragma once
#include <stdint.h>
#include "cvector.h"

#define VM_WIDTH 32
#define VM_HEIGHT 24

#define TILE_SIZE 8
#define TILE_MAP_X_COUNT 32
#define TILE_MAP_T_COUNT 24

#define TILESET_COUNT_X		32
#define TILESET_COUNT_Y		8
#define TILE_WIDTH			8
#define TILE_HEIGHT			8
#define PIXELS_PER_TILE		8

#define SPRITE_WIDTH 16
#define SPRITE_HEIGHT 16
#define PATTENS_PER_SPRITE 4

#define TICK_INTERVAL    60

typedef struct key_info {
	uint8_t _control_key;
	uint8_t _read_key_7;
	uint8_t _read_key_4;
	uint8_t _read_key_5;
}key_info;

typedef struct color_info
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} color_info;



typedef struct tag_music_info
{
	uint8_t music_index;
	uint8_t loop;
	void* data;
}music_info;

typedef struct tag_image_info
{
	uint8_t sprite_index;
	uint8_t flip;
	void* texture;

}image_info;


void* create_flip_texture(void* texture, int sprite_size);
//deprecated
uint8_t render_sprite_texture(void* texture, int x, int y, int patternIndex, uint8_t flip);
//deprecated
uint8_t render_sprite_image(void* texture, uint8_t src_x, uint8_t src_y, uint8_t x, uint8_t y, uint8_t flip);

void play_music(void* data, uint8_t loop);
void stop_music(void* data);
void* load_music(char* filename);
void* load_texture(const char* filename);
void* create_texture_from_data(void* array_data, int sprite_len, int sprite_size, uint8_t flip);
void init_key_values();

extern void ubox_putpixel(void* texture, uint8_t x, uint8_t y, int attr);
extern void* ubox_create_surface(int width, int height, int color_depth);
extern void* create_texture(void* surface);
extern void render_sprites();

extern key_info g_key_info;
extern uint8_t* g_tiles;
extern uint8_t* g_tiles_colors;
extern color_info transparent_color;
extern color_info sprite_pallete[16];
extern uint8_t g_tiles_rgb[2048 * 8 * 4];
extern cvector_vector_type(image_info) g_sprite_list;