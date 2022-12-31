#include <stdint.h>
#include <ubox.h>
#include "ubox_common.h"
#include "common.h"
#include <expand.h>

/*#ifdef WIN32
#if defined(_DEBUG) && defined(SDL2)
#pragma comment(lib, "sdl2maind.lib")
#endif
#endif*/

#define VM_WIDTH 32
#define VM_HEIGHT 24

uint8_t SONG[] = { 0,0,0,0,0 };
uint8_t EFFECTS[] = { 0,0,0,0,0 };

extern void read_control_key();
extern uint8_t read_key(int row);

uint8_t* g_tiles = 0;
uint8_t* g_tiles_colors = 0;

char g_tiles_rgb[2048 * 8 * 4];

cvector_vector_type(pattern_info) g_pattern_info = NULL;
uint8_t g_next_pattern_index = 0;

cvector_vector_type(music_info) g_music_list = NULL;
cvector_vector_type(image_info) g_sprite_list = NULL;


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
	{204, 204, 85, 0},
	{238, 238, 136, 0},
	{85, 170, 85, 0},
	{187, 85, 187, 0},
	{204, 204, 204, 0},
	{238, 238, 238, 0},
};



uint8_t ubox_read_ctl(uint8_t control)
{
	read_control_key();
	return control_key;
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

extern uint8_t game_main();
#if defined(DJGPP)
int main(void)
#elif defined(WIN32)
#include <windows.h>
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)

//#elif defined(WIN32)
//int SDL_main(int argc, char** argv)
#elif defined(SKYOS32) || defined(__linux)
int main(int argc, char** argv)
#elif defined(__ANDROID__)
int SDL_main(int argc, char** argv)
#else
void main()
#endif
{
    uint8_t result = game_main();
#if defined(__ANDROID__) || defined(WIN32) || defined(DJGPP)
    return result;
#endif
}

size_t GetMapDataSize(const uint8_t* map)
{
	unsigned short count = map[1];
	count = count << 8;
	count = count | map[0];

	return count;
}

void ap_uncompress(const uint8_t* dst, const uint8_t* src)
{

	size_t n = GetMapDataSize(src - 3);

	apultra_decompress(src, (uint8_t*)dst, n, g_map_width * g_map_height, 0, 0);
}


void ubox_fill_screen(uint8_t tile)
{
	uint8_t x = 0, y = 0;

	for (y = 0; y < g_map_height; y++)
		for (x = 0; x < g_map_width; x++)
		{
			ubox_put_tile(x, y, tile);
		}

}

void ubox_write_vm_(uint8_t* dst, uint16_t len, uint8_t* src)
{
	if (len >= 256)
		return;

	uint8_t pivot_x = (uint8_t)((uint32_t)dst % g_map_width);
	uint8_t y = (uint8_t)((uint32_t)dst / g_map_width);


	//for (y = 0; y < map_height; y++)
		for (uint8_t x = pivot_x; x < len; x++)
		{
			uint8_t tile = src[x];
			ubox_put_tile(x, y, tile);
		}

}



void ubox_write_vm(uint8_t* dst, uint16_t len, uint8_t* src)
{
	if ((dst + len) > (uint8_t * )(VM_WIDTH * VM_HEIGHT))
		return;

	if (dst == 0 && 0 == (len % VM_WIDTH)) {

		for (uint8_t y = 0; y < (len / VM_WIDTH); y++)
			for (uint8_t x = 0; x < VM_WIDTH; x++)
			{
				uint8_t tile = src[x + y * VM_WIDTH];
				ubox_put_tile(x, y, tile);
			}

		return;
	}

	uint8_t pivot_x = (uint8_t)((uint32_t)dst % g_map_width);
	uint8_t pivot_y = (uint8_t)((uint32_t)dst / g_map_width);
	uint8_t x = pivot_x;

	for (uint8_t i = 0; x < g_map_width; x++, i++) // ÇÑÁÙ ·»´õ¸µ
	{
		uint8_t tile = src[i];
		ubox_put_tile(x, pivot_y, tile);
	}

	if ((pivot_x + len) <= g_map_width)
		return;

	len -= pivot_x;
	x = 0;

	uint8_t height = len / g_map_width;

	for (uint8_t y = 0; y < height; y++)
		for (; x < g_map_width; x++)
		{
			uint8_t tile = src[g_map_width - pivot_x + x + y * g_map_width];
			ubox_put_tile(x, pivot_y + y + 1, tile);
		}
}

void ubox_set_mode(uint8_t mode)
{

}

//load_midi
void mplayer_init(uint8_t* song, uint8_t sub_song)
{
	ubox_play_music(sub_song);

}

void ubox_load_music(uint8_t music_index, char* filename, uint8_t loop) {
	music_info* vec_info = (music_info*)g_music_list;

	if (g_music_list) {
		for (music_info* info = cvector_begin(vec_info); info != cvector_end(vec_info); ++info)
		{
			if (info->music_index == music_index)
				return;
		}
	}

	void* music = 0;
	if (strlen(filename) != 0) {
		music = load_music(filename);
		//assert(music);
	}

	music_info element = { music_index, loop, music };
	cvector_push_back(g_music_list, element);
}



void ubox_add_sprite(uint8_t sprite_index, char* filename, uint8_t flip) {
	image_info* vec_info = (image_info*)g_sprite_list;

	if (g_sprite_list) {
		for (image_info* info = cvector_begin(vec_info); info != cvector_end(vec_info); ++info)
		{
			if (info->sprite_index == sprite_index)
				return;
		}
	}

	void* texture = 0;
	if (strlen(filename) != 0) {
		texture = load_texture(filename);
		assert(texture);
	}

	image_info element = { sprite_index, flip, texture};
	cvector_push_back(g_sprite_list, element);

	if (flip == 1) {
		void* flip_texture = create_flip_texture(texture, 16);
		image_info element_flip= { sprite_index + 1, flip, flip_texture };
		cvector_push_back(g_sprite_list, element_flip);
	}
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

void spman_init()
{
	if (g_pattern_info) {
		cvector_free(g_pattern_info);
		g_pattern_info = NULL;
	}

	g_next_pattern_index = 0;


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

	void* texture = create_texture_from_array(data, len, 16, flip);

#if defined(SDL2)
	extern void* create_sdl_texture(void* texture);

	texture = create_sdl_texture(texture);
#endif

	uint16_t patten_len = len * 4;
	pattern_info element = { type, g_next_pattern_index, data, patten_len, flip, texture };
	cvector_push_back(g_pattern_info, element);

	g_next_pattern_index += patten_len;

	return element.pattern;
}


void spman_alloc_sprite(struct sprite_attr* sp) {

	pattern_info* vec_info = (pattern_info*)g_pattern_info;
	uint8_t found = 0;
	uint8_t flip = 0;
	pattern_info* info = cvector_begin(vec_info);
	for (; info != cvector_end(vec_info); ++info) {

		if ((info->pattern <= sp->pattern) && (sp->pattern < (info->pattern + (info->len))))
		{
			found = 1;
			break;
		}
	}

	assert(found);

	uint8_t pattern = sp->pattern - info->pattern;
	if (info->flip) {
		flip = 1;
	}

#if defined(IMAGE_LOAD_MODE)
	render_sprite_type(info->type, sp->x, sp->y, pattern / 4, flip);

#else
#if defined(SPRITE_PIXEL_MODE)
	uint8_t color = 0;
	for (int i = 0; i < 4 * 8; i++)
	{
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
#else
	render_sprite_texture(info->texture, sp->x, sp->y, pattern / 4, flip);
#endif


#endif
}

void spman_alloc_fixed_sprite(struct sprite_attr* sp)
{
	spman_alloc_sprite(sp);
}

void* create_texture_from_array(void* array_data, int sprite_len, int sprite_size, uint8_t flip)
{
	uint8_t* data = array_data;
	void* texture = ubox_create_texture(sprite_len * sprite_size, sprite_size);

	assert(texture > 0);

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
						ubox_putpixel(texture, k * 16 + 15 - ((i / 16) * 8 + j), (i % 16), 5);
					else
						ubox_putpixel(texture, k * 16 + ((i / 16) * 8 + j), (i % 16), 5);

				}
				else {
#if defined(DJGPP)
					if (flip)
						ubox_putpixel(texture, k * 16 + 15 - ((i / 16) * 8 + j), (i % 16), 0);
					else
						ubox_putpixel(texture, k * 16 + ((i / 16) * 8 + j), (i % 16), 0);

#else
					if (flip)

						ubox_putpixel(texture, k * 16 + 15 - ((i / 16) * 8 + j), (i % 16), 0);
					else
						ubox_putpixel(texture, k * 16 + ((i / 16) * 8 + j), (i % 16), 0);
#endif
				}
			}
		}
	}

	return texture;

}

void mplayer_play()
{

}

void mplayer_stop()
{

}

void spman_sprite_flush()
{

}

void mplayer_init_effects(uint8_t* effects)
{

}
