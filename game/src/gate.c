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


const unsigned char gate_sprite[4][12] = {
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
		update_map_data_by_position((tile_x + i / 3) * 8, (tile_y + i % 3) * 8, gate_sprite[step][i]);
		ubox_put_tile(tile_x + i / 3, tile_y + i % 3, gate_sprite[step][i]);
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

void put_gate_sprite(uint8_t tile_x, uint8_t tile_y) {
	sp.x = (tile_x + 2) * 8;
	sp.y = (tile_y - 2) * 8;

	for (int8_t i = 0; i <  4; i++) {
		sp.pattern = pattern_door + i * 4;
		sp.attr = 1 + i % 2;
		spman_alloc_fixed_sprite(&sp);

		if (i == 1)
			sp.y += 16;
	}
}


void play_animation(uint8_t tile_x, uint8_t tile_y, uint8_t count, uint8_t step, uint8_t tile) {

	put_gate_tiles(tile_x - 1, tile_y - 1, step);
	ubox_put_tile(tile_x - 2, tile_y - 1, tile);

#if !defined(__SDCC) 
	render_player_sprite();

	if (player->extra2 < 2)
		put_gate_sprite(tile_x, tile_y);

#else
	if (player->extra2 < 2)
		put_gate_sprite(tile_x, tile_y);

	render_player_sprite();
#endif

	
	if (player->extra > count)
	{
		player->extra = 0;
		player->extra2++;
	}
}

extern uint8_t is_blocked(uint8_t x, uint8_t y);


uint8_t process_end_gate_animation(uint8_t tile_x, uint8_t tile_y)
{
	static uint8_t count = 0;
	uint8_t result = 0;

	count++;

	put_gate_sprite(tile_x, tile_y);
	render_player_sprite();




	if (++player->delay == 2)
	{
		player->x += 2;
		player->y--;

		player->delay = 0;
		if (++player->frame == WALK_CYCLE)
			player->frame = 0;
	}

	if (count >= 8 * FRAME_WAIT) {
		count = 0;
		result = 1;
	}



	return result;
}

void run_door_opening()
{
	self = player;

	uint8_t tile_x = player->x >> 3;
	uint8_t tile_y = player->y >> 3;


	player->x += 8;
	player->y -= 8;
	player->dir = 1;
	player->delay = 0;

	uint8_t count = 30;
	uint8_t step = 0;
	uint8_t tile = GATE_LOCK_DOWN_TILE;
	
	while (1) {

		ubox_update();

		player->extra++;

		switch (player->extra2) {
		case 1:
			count = 8 * FRAME_WAIT;
			break;
		case 2:
			step = 1;
			break;
		case 3:
			step = 2;
			break;
		case 4:
			step = 2;
			tile = (player->extra % 4) ? GATE_LOCK_UP_TILE : BLANK_TILE;

			break;
		case 5: {
			ubox_put_tile(tile_x - 2, tile_y - 1, 0);
			put_gate_tiles(tile_x - 1, tile_y - 1, 3);
			render_player_sprite();

			return;
		}

		}

		play_animation(tile_x, tile_y, count, step, tile);

		if (player->extra2 == 1) {
			if (++player->delay == FRAME_WAIT) {

				if (!is_blocked(player->x - 2, player->y + 1 + 15)) {
					player->x -= 2;
					player->y++;
				}

				player->delay = 0;
				if (++player->frame == WALK_CYCLE)
					player->frame = 0;
			}
		}

		ubox_wait();
		spman_update();
	}
}