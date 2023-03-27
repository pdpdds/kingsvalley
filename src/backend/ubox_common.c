#include <stdint.h>
#include "ubox_common.h"
#include "common.h"
#include <expand.h>

typedef struct tag_pattern_info
{
	uint8_t type;
	uint8_t pattern;
	uint8_t* data;
	uint16_t len;
	uint8_t flip;
	void* texture;
}pattern_info;



extern void read_control_key();
extern uint8_t read_key(int row);

uint8_t* g_tiles = 0;
uint8_t* g_tiles_colors = 0;

uint8_t g_tiles_rgb[2048 * 8 * 4];

cvector_vector_type(pattern_info) g_pattern_info = NULL;
cvector_vector_type(struct sprite_attr) g_allocated_patterns = NULL;

cvector_vector_type(music_info) g_music_list = NULL;
cvector_vector_type(music_info) g_effect_list = NULL;
cvector_vector_type(image_info) g_sprite_list = NULL;

extern void ubox_play_music(uint8_t music_index);
extern void ubox_play_effect(uint8_t effect_index);

GameSystemInfo* g_system_info;
uint8_t g_cur_pattern_index = 0;
cvector_vector_type(pattern_info) g_pattern_info;
key_info g_key_info;

color_info sprite_pallete[16] =
{
	{255, 0, 255, 0},
	{0, 0, 0, 0},
	{102, 204, 102, 0 },
	{136, 238, 136, 0},
	{68, 68, 221, 0},
	{119, 119, 255, 0},
	{187, 85, 85, 0},
	{119, 221, 221, 0},
	{221, 102, 102, 0},
	{255, 119, 119, 0},
	//{204, 204, 0, 0}, //for DJGPP
	{204, 204, 85, 0},
	{238, 238, 136, 0},
	{85, 170, 85, 0},
	{187, 85, 187, 0},
	{204, 204, 204, 0},
	{238, 238, 238, 0},
};

/*color_info sprite_pallete[16] =
{
	{255, 0, 255, 0},     // Magenta
	{0, 0, 0, 0},         // Black
	{0, 255, 0, 0},       // Lime
	{102, 204, 102, 0},   // Pale Green
	{0, 0, 255, 0},       // Blue
	{153, 204, 255, 0},   // Light Blue
	{255, 85, 85, 0},     // Light Red
	{85, 255, 255, 0},    // Cyan
	{255, 102, 102, 0},   // Light Red 2
	{255, 119, 119, 0},   // Light Red 3
	{204, 204, 0, 0},     // Dark Yellow
	{238, 238, 136, 0},   // Light Yellow
	{85, 170, 85, 0},     // Dark Green
	{187, 85, 187, 0},    // Plum
	{192, 192, 192, 0},   // Light Gray
	{238, 238, 238, 0},   // White
};*/

//default ubox transparent color (28, 28, 28, 0));
color_info transparent_color = { 255, 0, 255, 0 };

uint8_t ubox_read_ctl(uint8_t control)
{
	read_control_key();
	return g_key_info._control_key;
}

uint8_t ubox_read_keys(uint8_t row)
{
	return read_key(row);
}

void ubox_disable_screen()
{

}

void ubox_set_tiles_colors(uint8_t* colors){
	g_tiles_colors = colors;
}

void ubox_init_isr(uint8_t wait_ticks)
{

}

uint8_t ubox_get_tile(uint8_t x, uint8_t y)
{
	return 0;
}

void ubox_set_user_isr(void (*fn)())
{

}

void ubox_set_colors(uint8_t fg, uint8_t bg, uint8_t border)
{

}

void ubox_read_vm(uint8_t* dst, uint16_t len, uint8_t* src)
{

}

void ubox_wvdp(uint8_t reg, uint8_t data)
{

}

uint8_t ubox_get_vsync_freq()
{
	return 0;
}

void ubox_reset_tick()
{

}

void ubox_set_sprite_pat8(uint8_t* data, uint8_t pattern)
{

}

void ubox_set_sprite_pat8_flip(uint8_t* data, uint8_t pattern)
{

}

void ubox_set_sprite_attr(struct sprite_attr* attr, uint8_t sprite)
{

}


void ubox_set_sprite_pat16(uint8_t* data, uint8_t pattern)
{

}

void ubox_set_sprite_pat16_flip(uint8_t* data, uint8_t pattern)
{

}

void ubox_fill_screen(uint8_t tile) {
	uint8_t x = 0, y = 0;

	for (y = 0; y < g_system_info->_room_height; y++)
		for (x = 0; x < g_system_info->_room_width; x++) {
			ubox_put_tile(x, y, tile);
		}
}

void ubox_write_vm(uint8_t* dst, uint16_t len, uint8_t* src)
{
	if ((dst + len) > (uint8_t * )(VM_WIDTH * VM_HEIGHT))
		return;

	if (dst == 0 && 0 == (len % VM_WIDTH)) {

		for (uint8_t y = 0; y < (len / VM_WIDTH); y++)
			for (uint8_t x = 0; x < VM_WIDTH; x++) {
				uint8_t tile = src[x + y * VM_WIDTH];
				ubox_put_tile(x, y, tile);
			}

		return;
	}

	uint8_t pivot_x = (uint8_t)((uint32_t)dst % g_system_info->_room_width);
	uint8_t pivot_y = (uint8_t)((uint32_t)dst / g_system_info->_room_width);
	uint8_t x = pivot_x;

	// 1 line rendering
	for (uint8_t i = 0; x < g_system_info->_room_width; x++, i++)  {
		uint8_t tile = src[i];
		ubox_put_tile(x, pivot_y, tile);
	}

	if ((pivot_x + len) <= g_system_info->_room_width)
		return;

	len -= pivot_x;

	uint8_t height = len / g_system_info->_room_width;

	for (uint8_t y = 1; y <= height; y++)
		for (x = 0; x < g_system_info->_room_width; x++) {
			uint8_t tile = src[g_system_info->_room_width - pivot_x + x + y * g_system_info->_room_width];
			ubox_put_tile(x, pivot_y + y, tile);
		}
}



//load_midi
void mplayer_init(uint8_t* song, uint8_t sub_song) {
	ubox_play_music(sub_song);	
}

void ubox_load_music(uint8_t music_index, char* filename, uint8_t loop) {
	music_info* vec_info = (music_info*)g_music_list;

	if (g_music_list) {
		for (music_info* info = cvector_begin(vec_info); info != cvector_end(vec_info); ++info) {
			if (info->music_index == music_index)
				return;
		}
	}

	void* music = 0;
	if (strlen(filename) != 0) {
		music = load_music(filename);

		assert(music);
	}

	music_info element = { music_index, loop, music };
	cvector_push_back(g_music_list, element);
}

void ubox_load_effect(uint8_t music_index, char* filename, uint8_t loop) {
	music_info* vec_info = (music_info*)g_effect_list;

	if (g_effect_list) {
		for (music_info* info = cvector_begin(vec_info); info != cvector_end(vec_info); ++info) {
			if (info->music_index == music_index)
				return;
		}
	}

	void* music = 0;
	if (strlen(filename) != 0) {
		music = load_music(filename);
	}

	music_info element = { music_index, loop, music };
	cvector_push_back(g_effect_list, element);
}


void* current = 0;
void ubox_play_music(uint8_t sub_song) {
	if (!g_music_list)
		return;

	if (current) {
		stop_music(current);
		current = 0;
	}

	music_info* vec_info = (music_info*)g_music_list;
	music_info* info = cvector_begin(vec_info);
	for (; info != cvector_end(vec_info); ++info) {

		if (info->music_index == sub_song)
			break;
	}

	if (cvector_end(vec_info) == info)
		return;

	if (info->data)
	{
		current = info->data;
		play_music(info->data, info->loop);
	}
	else
		current = 0;
}

void* effect_current = 0;
void ubox_play_effect(uint8_t sub_song) {
	if (!g_effect_list)
		return;

	if (effect_current) {
		stop_music(effect_current);
		effect_current = 0;
	}

	music_info* vec_info = (music_info*)g_effect_list;
	music_info* info = cvector_begin(vec_info);
	for (; info != cvector_end(vec_info); ++info) {

		if (info->music_index == sub_song)
			break;
	}

	if (cvector_end(vec_info) == info)
		return;

	if (info->data)
	{
		effect_current = info->data;
		play_music(info->data, info->loop);
	}
	else
		effect_current = 0;
}

void mplayer_play_effect_p(uint8_t effect_no, uint8_t chan, uint8_t inv_vol)
{
	ubox_play_effect(effect_no);
}

void spman_init()
{
	if (g_pattern_info) {
		cvector_free(g_pattern_info);
		g_pattern_info = NULL;
	}

	g_cur_pattern_index = 0;
}

uint8_t spman_alloc_pat(uint8_t type, uint8_t* data, uint8_t len, uint8_t flip)
{
	pattern_info* vec_info = (pattern_info*)g_pattern_info;

	if (g_pattern_info) {
		for (pattern_info* info = cvector_begin(vec_info); info != cvector_end(vec_info); ++info)
		{
			if (info->type == type && info->flip == flip)
				return info->pattern;
		}
	}

	void* texture = create_texture_from_data(data, len, SPRITE_WIDTH, flip);

	assert(texture);

	uint16_t patten_len = len * PATTENS_PER_SPRITE;
	pattern_info element = { type, g_cur_pattern_index, data, patten_len, flip, texture};
	cvector_push_back(g_pattern_info, element);

	g_cur_pattern_index += patten_len;

	return element.pattern;
}

void spman_alloc_sprite(struct sprite_attr* sp) {

	cvector_push_back(g_allocated_patterns, *sp);
}


void render_sprites_by_image(pattern_info* info, struct sprite_attr* sp, uint8_t pattern, uint8_t flip) {

	image_info* vec_info = (image_info*)g_sprite_list;
	uint8_t found = 0;
	
	image_info* image = cvector_begin(vec_info);
	for (; image != cvector_end(vec_info); ++image) {

		if (image->sprite_index == info->type) {
			found = 1;
			break;
		}
	}

	assert(found);

	pattern = pattern / 4;

	uint8_t src_x = (pattern % SPRITE_WIDTH) * SPRITE_WIDTH;
	uint8_t src_y = (pattern / SPRITE_HEIGHT) * SPRITE_HEIGHT;

	render_sprite_image(image->texture, src_x, src_y, sp->x, sp->y, flip);
}

void render_sprites_by_data(pattern_info* info, struct sprite_attr* sp, uint8_t pattern, uint8_t flip ) {
	uint8_t color = 0;
	for (int i = 0; i < 4 * 8; i++) {
		color = info->data[pattern * 8 + i];

		for (int j = 0; j < 8; j++) {
			uint8_t mask = 0;

			mask = 1 << (7 - j);

			if (color & mask) {
				if (flip)
					ubox_putpixel(0, sp->x + 16 - ((i / 16) * 8 + j), sp->y + (i % 16), sp->attr);
				else
					ubox_putpixel(0, sp->x + ((i / 16) * 8 + j), sp->y + (i % 16), sp->attr);
			}
		}
	}
}

void render_sprites() {
	if (!g_allocated_patterns)
		return;

	struct sprite_attr* vec_info = (struct sprite_attr*)g_allocated_patterns;

	if (g_pattern_info) {
		for (struct sprite_attr* sp = cvector_begin(vec_info); sp != cvector_end(vec_info); ++sp) {
			pattern_info* vec_info = (pattern_info*)g_pattern_info;
			uint8_t found = 0;
			uint8_t flip = 0;
			pattern_info* info = cvector_begin(vec_info);
			for (; info != cvector_end(vec_info); ++info) {

				if ((info->pattern <= sp->pattern) && (sp->pattern < (info->pattern + (info->len)))) {
					found = 1;
					break;
				}
			}

			assert(found);

			uint8_t pattern = sp->pattern - info->pattern;
			if (info->flip) {
				flip = 1;
			}

			if (g_system_info->_sprite_mode == 0)
				render_sprites_by_image(info, sp, pattern, flip);
			else
				render_sprites_by_data(info, sp, pattern, flip);
		}
	}

	cvector_free(g_allocated_patterns);
	g_allocated_patterns = NULL;
}

void* create_texture_from_data(void* array_data, int sprite_len, int sprite_size, uint8_t flip)
{
	uint8_t* data = array_data;
	void* surface = ubox_create_surface(sprite_len * sprite_size, sprite_size, g_system_info->_color_depth);

	assert(surface > 0);

	uint8_t color = 0;
	for (int k = 0; k < sprite_len; k++) {
		for (int i = 0; i < 4 * 8; i++)
		{
			color = data[k * 4 * 8 + i];

			for (int j = 0; j < 8; j++) {
				uint8_t mask = 0;

				mask = 1 << (7 - j);

				if (color & mask) {
					if (flip)
						ubox_putpixel(surface, k * 16 + 15 - ((i / 16) * 8 + j), (i % 16), 5);
					else
						ubox_putpixel(surface, k * 16 + ((i / 16) * 8 + j), (i % 16), 5);

				}
				else {
#if defined(DJGPP)
					if (flip)
						ubox_putpixel(surface, k * 16 + 15 - ((i / 16) * 8 + j), (i % 16), 0);
					else
						ubox_putpixel(surface, k * 16 + ((i / 16) * 8 + j), (i % 16), 0);

#else
					if (flip)

						ubox_putpixel(surface, k * 16 + 15 - ((i / 16) * 8 + j), (i % 16), 0);
					else
						ubox_putpixel(surface, k * 16 + ((i / 16) * 8 + j), (i % 16), 0);
#endif
				}
			}
		}
	}

	return (void*)create_texture(surface);
}

void spman_alloc_fixed_sprite(struct sprite_attr* sp)
{
	spman_alloc_sprite(sp);
}

void ubox_finalize() {

	if (g_allocated_patterns)
		cvector_free(g_allocated_patterns);

	if (g_music_list)
		cvector_free(g_music_list);

	if (g_effect_list)
		cvector_free(g_effect_list);

	if (g_sprite_list)
		cvector_free(g_sprite_list);
}

void init_key_values() {
	g_key_info._control_key = 0;
	g_key_info._read_key_7 = 0;
	g_key_info._read_key_5 = 0;
	g_key_info._read_key_4 = 0;
}


void spman_hide_all_sprites()
{
	init_key_values();
}

uint8_t ubox_select_ctl() {
	if (g_key_info._control_key == 0)
		return UBOX_MSX_CTL_NONE;

	return g_key_info._control_key;
}

void read_control_key() {
	return;
}

uint8_t read_key(int row) {
	if (row == 5)
		return g_key_info._read_key_5;
	if (row == 4)
		return g_key_info._read_key_4;

	return g_key_info._read_key_7;
}


//dummy ubox functions
void ubox_set_mode(uint8_t mode) {
}

//dummy spman functions
void spman_sprite_flush() {
}

//dummy mplayer functions
void mplayer_init_effects(uint8_t* effects) {

}

void mplayer_stop_effect_channel(uint8_t chan) {
}

uint8_t mplayer_is_sound_effect_on(uint8_t chan) {
	return 0;
}

void mplayer_play_effect(uint8_t effect_no, uint8_t chan, uint8_t inv_vol) {
}

void mplayer_play() {
}

void mplayer_stop() {
}


//direct image file processing
void ubox_load_sprite(uint8_t sprite_index, char* filename, uint8_t flip) {

	void* texture = 0;

	assert(filename);

	if (strlen(filename) == 0)
		return;

	image_info* vec_info = (image_info*)g_sprite_list;

	if (g_sprite_list) {
		for (image_info* info = cvector_begin(vec_info); info != cvector_end(vec_info); ++info) {
			if (info->sprite_index == sprite_index)
				return;
		}
	}

	texture = load_texture(filename);
	assert(texture);

	image_info element = { sprite_index, flip, texture };
	cvector_push_back(g_sprite_list, element);

	if (flip == 1) {
		void* flip_texture = create_flip_texture(texture, SPRITE_WIDTH);
		image_info element_flip = { sprite_index + 1, flip, flip_texture };
		cvector_push_back(g_sprite_list, element_flip);
	}
}