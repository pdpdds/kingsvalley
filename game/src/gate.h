#ifndef _GATE_H
#define _GATE_H

#include <stdint.h>

void update_exit();

uint8_t process_start_gate_animation(uint8_t tile_x, uint8_t tile_y);
uint8_t process_end_gate_animation(uint8_t tile_x, uint8_t tile_y);

#endif