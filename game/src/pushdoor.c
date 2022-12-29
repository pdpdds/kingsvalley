#include <ubox.h>
#include <spman.h>
#include "game_util.h"
#include "game.h"

extern void change_object_state(struct entity* object, uint8_t state, uint8_t move_type);

void update_pushdoor() {

	if (self->roomId != g_cur_room_id || self->state == PS_DEAD)
		return;

	if (player->state != PS_MOVE) {
		self->extra = 0;
		return;
	}

	if (player->y + 8 != self->y) {
		return;
	}


	if (!player->dir && self->dir) {
		if ((player->x + 8) == self->x)
			self->extra++;
	}	
	else if (player->dir && !self->dir) {
		if ((player->x - 16) == self->x)
			self->extra++;
	}

	if (self->extra > 30) {
		self->dir ^= 1;

		change_object_state(player, PS_MOVABLE_DOOR, player->movetype);
		player->extra = self->x;
		player->extra2 = self->height / 8;
	}
}