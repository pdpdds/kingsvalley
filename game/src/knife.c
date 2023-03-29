#include <ubox.h>
#include <spman.h>
#include "game_util.h"


extern void change_object_state(struct entity* object, uint8_t state, uint8_t move_type);
extern void draw_hud();

char height_variation[14] = { 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1 };
char height_variation_double[22] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1 };

#define KNIFE_SPEED 2

#define KNIFE_FALL_PHASE1 1
#define KNIFE_FALL_PHASE2 2
#define KNIFE_FALL_PHASE3 3

#define KNIFE_COLLIDE_STATIC_OBJECT 0
#define KNIFE_COLLIDE_ENEMY 1

static void init_knife_fall(uint8_t collison_type) {
	self->state = PS_FALL;
	self->dir ^= 1;
	self->subtype = KNIFE_FALL_PHASE1;
	self->extra = 0;
	self->extra2 = 8 * collison_type;


	self->pivot_x = self->dir ? 8 : 0;
	self->extra2 += self->dir ? -(self->x % 8) : ((self->x % 8) ? 8 - (self->x % 8) : 0);
}

void process_knife_fall() {

	switch (self->subtype) {
	case KNIFE_FALL_PHASE1:
	{

		self->y -= height_variation[self->extra];


		if (self->extra2 != 0 && ((self->extra % 2) == 0)) {
			if (self->dir)
				self->x -= 1;
			else
				self->x += 1;

			self->extra2--;

		}

		if (self->extra >= 14)
		{
			self->subtype = KNIFE_FALL_PHASE2;
		}

		self->extra++;
	}
	break;


	case KNIFE_FALL_PHASE2:
	{
		self->y += height_variation[self->extra];

		struct entity* object = entities;

		for (uint8_t i = 0; i < g_maxEntities; i++, object++) {

			if (object == self)
				continue;

			if (object->state == PS_ATTACK || object->state == PS_IDLE)
			{
				if (is_intersect(object, self))
				{

					switch (object->type)
					{
					case ET_ENEMY:
					case ET_JEWEL:
					case ET_KNIFE:
						init_knife_fall(KNIFE_COLLIDE_STATIC_OBJECT);
						return;
					}
				}


			}
		}


		if (self->extra == 0)
		{
			self->y += height_variation[self->extra];
			if (check_floor(self->x, self->y + 8, 8 - 1)) {

				self->subtype = 0;

				self->state = PS_IDLE;
				self->extra = 0;
				self->x = (self->x >> 3) * 8;
				self->y = ((self->y) >> 3) * 8;

				if (self->roomId == g_cur_room_id)
					put_tile(self->x, self->y, KNIFE_TILE);

			}
		}
		else
		{
			if (self->extra2 != 0 && ((self->extra % 2) == 0)) {
				if (self->dir)
				{
					if (self->x == 0)
					{
						self->x = 255;
						self->roomId -= 1;
					}
					else self->x -= 1;
				}
				else
				{
					if (self->x == 255)
					{
						self->x = 0;
						self->roomId += 1;
					}
					else self->x += 1;
				}

				self->extra2--;
			}

			self->extra--;
		}
	}
	break;
	}
}

void process_knife_attack() {

	uint8_t offset = self->dir ? 0 : 7;

	uint8_t next_x = self->x;

	if (!self->dir) {
		if ((next_x + offset) < 248) {
			next_x += KNIFE_SPEED;
		}
	}
	else
		next_x -= KNIFE_SPEED;


	uint8_t tile = get_tile_index(next_x + offset, self->y);

	if (is_map_blocked(next_x + offset, self->y) || is_static_object(tile)) {
		init_knife_fall(KNIFE_COLLIDE_STATIC_OBJECT);

		return;
	}



	if (self->dir) {
		if (next_x < 8)
		{
			next_x = 247;
			self->roomId -= 1;
		}
	}
	else {
		if ((next_x + offset) >= 248)
		{
			next_x = 0;
			self->roomId += 1;
		}
	}

	self->x = next_x;


	struct entity* object = entities;

	for (uint8_t i = 0; i < g_maxEntities; i++, object++) {
		if (object->type != ET_ENEMY)
			continue;

		if (object->state == PS_NONE || object->state == PS_DEAD)
			continue;

		if (is_intersect(object, self)) {
			init_knife_fall(KNIFE_COLLIDE_ENEMY);
			object->state = PS_DEAD;
			object->frame = 0;
			g_player_info.score += 1000;
			draw_hud();
			return;
		}
	}
}

void render_knife() {
	if (g_cur_room_id != self->roomId)
		return;

	sp.x = self->x - self->pivot_x;
	sp.y = self->y + self->pivot_y;

	uint8_t current_frame = knife_frames[self->frame];

	sp.pattern = self->pat + (current_frame + (self->dir) * 4) * 4;
	sp.attr = 14;
	spman_alloc_sprite(&sp);
}

void update_knife() {
	if (self->state == PS_IDLE || self->state == PS_MOVE)
		return;

	if (self->delay++ == 2) {

		self->delay = 0;
		if (++self->frame == KNIFE_CYCLE)
			self->frame = 0;

	}

	switch (self->state) {
	case PS_FALL:
		process_knife_fall();
		break;
	case PS_ATTACK:
		process_knife_attack();
		break;
	}
	
	render_knife();

}


