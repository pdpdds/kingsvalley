#include <ubox.h>
#include <spman.h>
#include "game_util.h"
#include "game.h"

extern void change_object_state(struct entity* object, uint8_t state, uint8_t move_type);
extern void draw_hud();




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

uint8_t get_pattern_gate() {
	struct entity* knife = find_object_by_type(ET_KNIFE);
	return knife->pat;
}


void put_gate_sprite(uint8_t tile_x, uint8_t tile_y) {
	uint8_t pattern_gate = get_pattern_gate();
	sp.x = (tile_x + 2) * 8;
	sp.y = (tile_y - 2) * 8 - 1;

	for (uint8_t i = 0; i < 4; i++) {
		sp.pattern = pattern_gate + (4 + i) * 4;
		sp.attr = 1 + i % 2;
		spman_alloc_fixed_sprite(&sp);

		if (i == 1)
			sp.y += 16;
	}

}

void put_player_sprite(uint8_t frame)
{
	sp.x = player->x - player->pivot_x;
	sp.y = player->y + player->pivot_y;

	uint8_t current_frame = walk_frames[frame];

	sp.pattern = player->pat + (current_frame * 2 + 6) * 4;
	sp.attr = 14;
	spman_alloc_fixed_sprite(&sp);

	sp.pattern = sp.pattern + 4;
	sp.attr = 6;
	spman_alloc_fixed_sprite(&sp);
}

void play_animation(uint8_t tile_x, uint8_t tile_y, uint8_t player_frame, uint8_t count, uint8_t step, uint8_t tile) {

#if defined(WIN32) || defined(__linux) || defined(DJGPP)
	self = player;
	ubox_put_tile(tile_x - 2, tile_y - 1, tile);
	put_gate_tiles(tile_x - 1, tile_y - 1, step);
	put_player_sprite(player_frame);


	//if (player->extra2 < 2)
	//	put_gate_sprite(tile_x, tile_y);

	if (player->extra2 < 2)
	{
		uint8_t pattern_gate = get_pattern_gate();
		sp.x = (tile_x + 2) * 8;
		sp.y = (tile_y - 2) * 8 - 1;

		sp.pattern = pattern_gate + (5) * 4;
		sp.attr = 2;
		spman_alloc_fixed_sprite(&sp);


		sp.pattern = pattern_gate + (4) * 4;
		sp.attr = 1;
		spman_alloc_fixed_sprite(&sp);

		sp.y += 16;

		sp.pattern = pattern_gate + (7) * 4;
		sp.attr = 2;
		spman_alloc_fixed_sprite(&sp);


		sp.pattern = pattern_gate + (6) * 4;
		sp.attr = 1;
		spman_alloc_fixed_sprite(&sp);
	}


#else
	put_gate_tiles(tile_x - 1, tile_y - 1, step);
	ubox_put_tile(tile_x - 2, tile_y - 1, tile);

	if (player->extra2 < 2)
		put_gate_sprite(tile_x, tile_y);

	put_player_sprite(player_frame);
#endif

	if (player->extra > count)
	{
		player->extra = 0;
		player->extra2++;
	}
}

extern uint8_t is_blocked(uint8_t x, uint8_t y);

uint8_t process_start_gate_animation(uint8_t tile_x, uint8_t tile_y)
{
	player->extra++;

	uint8_t frame = 0;
	uint8_t count = 30;
	uint8_t step = 0;
	uint8_t tile = GATE_LOCK_DOWN_TILE;

	switch (player->extra2)
	{
	case 1:
		frame = player->frame;
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
		put_player_sprite(0);

		return 1;
	}

	}

	play_animation(tile_x, tile_y, frame, count, step, tile);

	if (player->extra2 == 1)
	{
		if (++player->delay == FRAME_WAIT)
		{
			

			if (!is_blocked(player->x - 2, player->y + 1 + 15))
			{
				player->x -= 2;
				player->y++;
			}
			

			player->delay = 0;
			if (++player->frame == WALK_CYCLE)
				player->frame = 0;
		}
	}

	return 0;
}

uint8_t process_end_gate_animation(uint8_t tile_x, uint8_t tile_y)
{
	static uint8_t count = 0;
	uint8_t result = 0;

	count++;

	put_gate_sprite(tile_x, tile_y);
	put_player_sprite(player->frame);




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
