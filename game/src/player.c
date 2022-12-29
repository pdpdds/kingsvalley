#include "ubox.h"
#include "game.h"
#include "game_util.h"
#include <spman.h>
#include <mplayer.h>
#include "character.h"
#include "main.h"

extern void player_die();
extern void change_object_state(struct entity* object, uint8_t state, uint8_t move_Type);
extern void reset_sprite(uint8_t mode);
extern void draw_hud();


extern uint8_t pattern_attack;
extern uint8_t pattern_digging;

void render_player_sprite();
void process_object_interaction();
void process_tile_object_interaction();

void player_die() {
	lives--;
	invuln = INVUL_TIME;

	if (!lives)
	{
		mplayer_init(SONG, SONG_SILENCE);
		mplayer_play_effect_p(EFX_DEAD, EFX_CHAN_NO, 0);
		gameover_delay = GAMEOVER_DELAY;
		g_gamestate = STATE_GAME_OVER;
	}
	else
	{
		mplayer_init(SONG, SONG_SILENCE);
		mplayer_play_effect_p(EFX_DEAD, EFX_CHAN_NO, 0);
		gameover_delay = GAMEOVER_DELAY;
		g_gamestate = STATE_GAME_RESET;
	}
}


void update_player()
{
	self->control = control;

	if ((ubox_read_keys(4) == UBOX_MSX_KEY_P) && !gameover_delay)
	{
		player_die();
		return;
	}

	if (invuln)
		invuln--;

	if (!gameover_delay)
		update_character();

	if (g_cur_room_id != self->roomId) {
		g_cur_room_id = self->roomId;
		update_screen();
	}

	process_object_interaction();
	process_tile_object_interaction();


	if (invuln & 1)
		return;

	render_player_sprite();
}


void render_player_sprite()
{
	sp.x = self->x - self->pivot_x;
	sp.y = self->y + self->pivot_y - 1;

	uint8_t vibration = self->state == PS_MOVE;
	uint8_t current_frame = walk_frames[self->frame];

	if (vibration && !current_frame) // character vibration
		sp.y -= 1;

	uint8_t offset = 0;
	uint8_t pattern = self->pat;

	switch (self->state)
	{
	case PS_JUMP:
		offset = 6;
		current_frame = 2;
		break;
	case PS_ATTACK:
		pattern = pattern_attack;
		offset = 4;
		break;
	case PS_DIGGING:
		pattern = pattern_digging;
		offset = 4;
		break;
	default:
	{
		offset = 6;
	}
	break;
	}

	sp.pattern = pattern + (current_frame * 2 + self->dir * offset) * 4;

	sp.attr = 14;
	spman_alloc_fixed_sprite(&sp);

	sp.pattern = sp.pattern + 4;
	sp.attr = 6;
	spman_alloc_fixed_sprite(&sp);
}
extern void put_gate_tiles(uint8_t tile_x, uint8_t  tile_y, uint8_t step);
void process_tile_object_interaction() {

	if (self->movetype != MOVE_NORMAL)
		return;

	for (uint8_t i = 0; i < 2; i++) {

		uint8_t x = self->x + 4;
		uint8_t y = self->y + i * 8;
		uint8_t tile = get_tile_index(x, y);

		if (tile == PICKAX_TILE) {
			put_tile(x, y, BLANK_TILE);
			update_map_data_by_position(x, y, BLANK_TILE);

			self->movetype = MOVE_PICKAX;
			reset_sprite(self->movetype);
		}
		if (tile == GATE_LOCK_DOWN_TILE) {

			struct entity* object = find_object_by_tile_index((x >> 3) + 2, (y >> 3));

			if (object && object->type == ET_EXIT && object->extra != 1) {
				
				object->extra = 1;
				uint8_t tile_x = object->x >> 3;
				uint8_t tile_y = object->y >> 3;
				put_gate_tiles(tile_x - 1, tile_y, 0);
			}
		}

	}
}



void process_object_interaction() {

	struct entity* object = entities;
	for (uint8_t i = 0; i < g_maxEntities; i++, object++)
	{
		if (object->state == PS_DEAD || object->roomId != g_cur_room_id)
			continue;

		switch (object->type)
		{
		case ET_JEWEL:
		{
			if (is_intersect(self, object)) {
				put_tile(object->x, object->y, BLANK_TILE);
				put_tile(object->x, object->y - 8, BLANK_TILE);
				put_tile(object->x - 8, object->y, BLANK_TILE);
				put_tile(object->x + 8, object->y, BLANK_TILE);

				object->type = ET_UNUSED;
				g_player_info.jewels++;
				g_jewels_count--;
				g_player_info.score += 2000;

				draw_hud();

				mplayer_play_effect_p(EFX_HIT, EFX_CHAN_NO, 0);

				if (g_jewels_count == 0) {
					struct entity* exit = find_object_by_type(ET_EXIT);

					if (exit) {
						cur_map_data[exit->roomId][((exit->x - 16) >> 3) + (exit->y >> 3) * MAP_W] = GATE_LOCK_DOWN_TILE;
						exit->state = PS_ATTACK;
						exit->extra = 0;

						uint8_t tile_x = exit->x >> 3;
						uint8_t tile_y = exit->y >> 3;
						put_gate_tiles(tile_x - 1, tile_y, 2);
					}
				}

			}
		}
		break;
		case ET_KNIFE:
		{
			if (self->movetype == MOVE_NORMAL && object->state == PS_IDLE && (self->state != PS_FALL && self->state != PS_JUMP))
			{
				if (is_intersect(self, object)) {

					uint8_t tile_index = get_tile_index(object->x, object->y);
					put_tile(object->x, object->y, tile_index);

					object->state = PS_MOVE;
					change_object_state(self, PS_MOVE, MOVE_KNIFE);
					self->item = object->identifier;

					reset_sprite(self->movetype);
				}
			}

		}
		break;
		case ET_EXIT:
		{
			if (object->state == PS_ATTACK)
			{
				if ((self->x == object->x) && ((self->y + 16) == (object->y + object->height)) && object->extra == 1)
				{
					self->frame = 0;

					g_gamestate = STATE_IN_GAME_EXIT;

				}

			}
		}
		break;


		}
	}
}