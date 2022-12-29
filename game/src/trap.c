#include <ubox.h>
#include <spman.h>
#include "item.h"
#include "game_util.h"
#include "game.h"

void update_trap() {
	if (self->roomId != g_cur_room_id || self->state == PS_DEAD)
		return;

	switch (self->state) {
	case PS_IDLE:
	{
		uint8_t tile_x = player->x >> 3;

		if (tile_x == (self->x >> 3)) {
			struct rect_ rect1 = { player->x, player->y, player->width, player->height };
			struct rect_ rect2 = { self->x, self->y, 8, 8 * self->extra };

			if (is_intersect_by_rect(&rect1, &rect2)) {
				self->state = PS_ATTACK;
				self->extra2 = 0;
				self->delay = 0;
			}
		}

	}
	break;
	case PS_ATTACK:
	{
		if (self->delay++ == 30) {
			self->delay = 0;

			uint8_t solid_tile = SOLID_TILE;

			if (self->extra & 128)
				solid_tile = SOLID_TILE2;

			put_tile(self->x, self->y + self->extra2 * 8, solid_tile);
			update_map_data_by_position(self->x, self->y + self->extra2 * 8, solid_tile);

			self->extra2++;
			if ((uint8_t)self->extra2 == (self->extra & (~128)))
				self->state = PS_DEAD;
		}

	}
	break;
	}

}




