#include <ubox.h>
#include "game_util.h"
#include "game.h"


void update_jewel()
{
	if (self->roomId != g_cur_room_id)
		return;

	if (self->delay++ == FRAME_WAIT)
	{
		self->delay = 0;

		if (++self->frame == FRAME_WAIT)
			self->frame = 0;

		if (self->frame == 0)
		{
			put_tile(self->x, self->y - 8, JEWEL_EFFECT_UP_TILE);
			put_tile(self->x - 8, self->y, JEWEL_EFFECT_LEFT_TILE);
			put_tile(self->x + 8, self->y, JEWEL_EFFECT_RIGHT_TILE);
		}
		else
		{

			put_tile(self->x, self->y - 8, get_tile_index(self->x, self->y - 8));
			put_tile(self->x - 8, self->y, get_tile_index(self->x - 8, self->y));
			put_tile(self->x + 8, self->y, get_tile_index(self->x + 8, self->y));
		}
	}
}

