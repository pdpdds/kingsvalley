#include <ubox.h>
#include <spman.h>
#include "game_util.h"
#include "game.h"

extern void render_player_sprite();

#define GATE_TILE1 108
#define GATE_TILE2 109
#define GATE_TILE3 110
#define GATE_TILE4 99
#define GATE_TILE5 102

#define GATE_TILE6 100
#define GATE_TILE7 103

#define GATE_TILE8 123
#define GATE_TILE9 124
#define GATE_TILE10 125

#define GATE_TILE11 111
#define GATE_TILE12 112
#define GATE_TILE13 114

#define GATE_TILE14 95
#define GATE_TILE15 96
#define GATE_TILE16 97
#define GATE_TILE18 98

#define GATE_TILE19 113

#define GATE_TILE20 126
#define GATE_TILE21 127
#define GATE_TILE22 128
#define GATE_TILE23 129


const unsigned char gate_tiles[4][12] = {
{
GATE_TILE1, GATE_TILE2, GATE_TILE3,
GATE_TILE4, BLANK_TILE, GATE_TILE5,
GATE_TILE6, BLANK_TILE, GATE_TILE7,
GATE_TILE8, GATE_TILE9, GATE_TILE10,
},
{
GATE_TILE11, GATE_TILE12, GATE_TILE13,
GATE_TILE14, GATE_TILE19, GATE_TILE16,
GATE_TILE15, GATE_TILE22, GATE_TILE18,
GATE_TILE20, GATE_TILE21, GATE_TILE23,
},
{
BLANK_TILE, BLANK_TILE, BLANK_TILE,
GATE_TILE1, GATE_TILE2, GATE_TILE3,
GATE_TILE8, GATE_TILE9, GATE_TILE10,
BLANK_TILE, BLANK_TILE, BLANK_TILE,
},
{
BLANK_TILE, BLANK_TILE, BLANK_TILE,
BLANK_TILE, BLANK_TILE, BLANK_TILE,
BLANK_TILE, BLANK_TILE, BLANK_TILE,
BLANK_TILE, BLANK_TILE, BLANK_TILE,
}
};

void put_gate_tiles(uint8_t tile_x, uint8_t  tile_y, uint8_t step) {
	for (uint8_t i = 0; i < 12; i++) {
		update_map_data_by_position((tile_x + i / 3) * 8, (tile_y + i % 3) * 8, gate_tiles[step][i]);
		ubox_put_tile(tile_x + i / 3, tile_y + i % 3, gate_tiles[step][i]);
	}
}

void update_exit() {
	if (self->roomId != g_cur_room_id || self->state != PS_ATTACK)
		return;

	uint8_t tile_x = self->x >> 3;
	uint8_t tile_y = self->y >> 3;

	if (self->delay++ == FRAME_WAIT)
	{
		self->delay = 0;

		ubox_put_tile(tile_x - 2, tile_y, (self->frame % 4) ? GATE_LOCK_DOWN_TILE : 0);
	}

	if (++self->frame == 4)
		self->frame = 0;


}

extern uint8_t pattern_door;

void put_gate_sprite(uint8_t x, uint8_t y) {
	sp.x = x;
	sp.y = y;

	for (int8_t i = 0; i <  4; i++) {
		sp.pattern = pattern_door + i * 4;
		sp.attr = 2 - i % 2;
		spman_alloc_fixed_sprite(&sp);

		if (i == 1)
			sp.y += 16;
	}
}

extern uint8_t is_blocked(uint8_t x, uint8_t y);

void run_door_opening()
{
	self = player;

	uint8_t tile_x = self->x >> 3;
	uint8_t tile_y = self->y >> 3;

	self->x += 8;
	self->y -= 8;
	self->dir = 1;

	uint8_t step = 0;
	uint8_t count = 0;

	while (1) {

		ubox_update();

		switch (step) {
		case 0:
			ubox_put_tile(tile_x - 2, tile_y - 1, GATE_LOCK_UP_TILE);
			put_gate_tiles(tile_x - 1, tile_y - 1, 0); 
			if (count > 30) {
				count = 0;
				step++;
			}
			break;
		case 1:
			if (++self->delay == FRAME_WAIT) {

				if (!is_blocked(self->x - 2, self->y + 1 + 15)) {
					self->x -= 2;
					self->y++;

					if (++self->frame == WALK_CYCLE)
						self->frame = 0;
				}
				else 
					self->frame = 0;

				self->delay = 0;
			}

			if (count > 30) {
				count = 0;
				step++;
			}
			break;
		case 2:
			if (count > 30) {
				count = 0;
				step++;
			}
			break;
		case 3:
			put_gate_tiles(tile_x - 1, tile_y - 1, 1);
			if (count > 30) {
				count = 0;
				step++;
			}
			break;
		case 4:
			put_gate_tiles(tile_x - 1, tile_y - 1, 2);
			if (count > 30) {
				count = 0;
				step++;
			}
			break;
		case 5:
	
			ubox_put_tile(tile_x - 2, tile_y - 1, (count % 4) ? GATE_LOCK_UP_TILE : BLANK_TILE);
			if (count > 30) {
				count = 0;
				step++;
			}
			break;
		case 6: 
			put_gate_tiles(tile_x - 1, tile_y - 1, 3);
			ubox_put_tile(tile_x - 2, tile_y - 1, BLANK_TILE);
			return;
		}

		count++;

		if(step < 3)
			put_gate_sprite((tile_x + 2) * 8, (tile_y - 2) * 8);

		render_player_sprite();


		ubox_wait();
		spman_update();
	}
}

#define PLAYER_HIDE_COUNT 15
void run_door_exit() {
	self = player;

	uint8_t tile_x = self->x >> 3;
	uint8_t tile_y = self->y >> 3;

	self->delay = 0;

	uint8_t count = 0;

	while (1) {

		ubox_update();


		if (++self->delay == FRAME_WAIT) {

			if (count < PLAYER_HIDE_COUNT) {
				self->x += 2;
				self->y--;

				if (++self->frame == WALK_CYCLE)
					self->frame = 0;
			}

			self->delay = 0;
		}

		if (count > 30) {
			return;
		}


		count++;

		put_gate_sprite((tile_x + 2) * 8, (tile_y - 2) * 8);
		if (count < PLAYER_HIDE_COUNT)
			render_player_sprite();

		ubox_wait();
		spman_update();
	}
}


