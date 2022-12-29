#pragma once
#include <stdint.h>

void ubox_load_music(uint8_t music_index, char* filename, uint8_t loop);
void ubox_play_music(uint8_t music_index);
void ubox_init_game_system(int screen_width, int screen_height, uint8_t map_width, uint8_t map_height);
void ubox_add_sprite(uint8_t sprite_index, char* filename, uint8_t flip);