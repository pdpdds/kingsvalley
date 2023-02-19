#pragma once
#include <stdint.h>
#include "cvector.h"

#define IMAGE_LOAD_MODE
//#define SPRITE_PIXEL_MODE

#define TICK_INTERVAL    60

uint8_t control_key;
uint8_t read_key_7;
uint8_t read_key_4;
uint8_t read_key_5;

uint8_t g_map_width;
uint8_t g_map_height;

uint8_t g_room_width;
uint8_t g_room_height;

uint32_t g_screen_width;
uint32_t g_screen_height;

extern uint8_t* g_tiles;
extern uint8_t* g_tiles_colors;

typedef struct color_info
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} color_info;

typedef struct tag_pattern_info
{
	uint8_t type;
	uint8_t pattern;
	uint8_t* data;
	uint16_t len;
	uint8_t flip;
	void* texture;
}pattern_info;

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


extern color_info sprite_pallete[16];
extern cvector_vector_type(pattern_info) g_pattern_info;
extern uint8_t g_next_pattern_index;

extern char g_tiles_rgb[2048 * 8 * 4];

void* create_flip_texture(void* texture, int sprite_size);
uint8_t render_sprite_texture(void* texture, int x, int y, int patternIndex, uint8_t flip);
uint8_t render_sprite_type(int type, int x, int y, int patternIndex, uint8_t flip);

void play_music(void* data, uint8_t loop);
void stop_music(void* data);
void* load_music(char* filename);
void* load_texture(const char* filename);


extern void ubox_putpixel(void* texture, int x, int y, int attr);
extern void* ubox_create_texture(int width, int height);
extern void* create_texture_from_array(void* array_data, int sprite_len, int sprite_size, uint8_t flip);