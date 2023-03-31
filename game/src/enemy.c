#include "enemy.h"
#include "game_util.h"
#include "ubox.h"
#include "game.h"
#include <spman.h>
#include <mplayer.h>
#include "main.h"

extern void player_die();
extern void change_object_state(struct entity* object, uint8_t state, uint8_t move_Type);
extern void update_character();

enum enemy_type
{
	ENEMY_STATIC = 0,
	ENEMY_MOVE,
	ENEMY_WANDERER,
	ENEMY_WANDERER_STAIR,
	ENEMY_TRACER,
};

void update_enemy_static();
void update_enemy_move();
void update_enemy_wanderer();
void update_enemy_wanderer_stair();
void update_enemy_tracer();



static void process_intersect_player() {

	if (player->roomId != self->roomId)
		return;

	if (gameover_delay || invuln)
		return;

	if (player->state == PS_STAIR) {
		if (self->state != PS_STAIR)
			return;
	}

	if (self->state == PS_STAIR) {
		if (player->state != PS_STAIR)
			return;
	}


	struct rect_ rect1 = { player->x + 1, player->y, player->width - 1, player->height - 3 };
	struct rect_ rect2 = { self->x + 1, self->y + 3, self->width - 1, self->height - 3 };

	if (is_intersect_by_rect(&rect1, &rect2))
		player_die();


}

void render_enemy_sprite(uint8_t sprite_attribute)
{
	if (g_cur_room_id != self->roomId)
		return;

	sp.x = self->x - self->pivot_x;
	sp.y = self->y - self->pivot_y;

	uint8_t current_frame = 0;

	switch (self->state)
	{
	case PS_NONE:
	{
		if (self->regentime <= ENEMY_REBORN_CYCLE * 2)
			current_frame = enemy_reborn_frames[self->frame];
		else return;
	}
	break;
	case PS_DEAD:
	{
		if (self->frame == 0)
		{

			sp.pattern = self->pat + (3) * 4;
			sp.attr = sprite_attribute;
			spman_alloc_fixed_sprite(&sp);

		}
		return;
	}
	break;
	case PS_ATTACK:
	case PS_MOVE:
	case PS_STAIR:
	case PS_IDLE:
	{
		current_frame = walk_frames[self->frame];

		if (!current_frame) // character vibration
			sp.y -= 1;
	}
	break;
	case PS_JUMP:
	{

		current_frame = 2;
	}
	break;
	}

	sp.pattern = self->pat + (current_frame + (self->dir) * 6) * 4;
	sp.attr = sprite_attribute;
	spman_alloc_sprite(&sp);
}

void update_common_state() {

	if (self->state == PS_NONE)
	{
		if (self->delay++ == 20) {

			self->delay = 0;

			if (++self->frame == ENEMY_REBORN_CYCLE)
				self->frame = 0;

			if (self->regentime > 0) {
				self->regentime--;
			}
			else {
				self->state = PS_IDLE;
				self->regentime = 10;
			}
		}
	}
	else if (self->state == PS_DEAD) {
		if (self->delay++ == 20) {

			self->delay = 0;

			if (self->frame < 1)
				self->frame++;
			else
				self->state = PS_NONE;

		}
	}
}

uint8_t get_enemy_color() {
	switch (self->subtype) {

	case ENEMY_STATIC:
		return 15;
	case ENEMY_MOVE:
		return 8;
	case ENEMY_WANDERER:
		return 15;
	case ENEMY_TRACER:
		return 6;
	case ENEMY_WANDERER_STAIR:
		return 7;
	}

	return 0;
}

#define MAP_W 32
/*void ubox_render_background(int object_type, uint8_t x, uint8_t y, uint8_t frame)
{

	uint32_t tile = cur_map_data[self->roomId][(x / 8) + (y / 8) * MAP_W];
	uint32_t tile1 = cur_map_data[self->roomId][(x / 8) + 1 + (y / 8) * MAP_W];
	uint32_t tile2 = cur_map_data[self->roomId][(x / 8) + (y / 8 + 1) * MAP_W];
	uint32_t tile3 = cur_map_data[self->roomId][(x / 8 + 1) + (y / 8 + 1) * MAP_W];

	uint32_t tile5 = cur_map_data[self->roomId][(x / 8) + 2 + (y / 8) * MAP_W];
	uint32_t tile6 = cur_map_data[self->roomId][(x / 8) + 2 + (y / 8 + 1) * MAP_W];

	


	ubox_put_tile(x / 8, y / 8, tile);
	ubox_put_tile(x / 8 + 1, y / 8, tile1);
	ubox_put_tile(x / 8, y / 8 + 1, tile2);
	ubox_put_tile(x / 8 + 1, y / 8 + 1, tile3);

	ubox_put_tile(x / 8 + 2, y / 8, tile5);
	ubox_put_tile(x / 8 + 2, y / 8 + 1, tile6);

	if ((x / 8) > 0)
	{
		uint32_t tile7 = cur_map_data[self->roomId][(x / 8) - 1 + (y / 8) * MAP_W];
		uint32_t tile8 = cur_map_data[self->roomId][(x / 8) - 1 + (y / 8 + 1) * MAP_W];
		ubox_put_tile(x / 8 -1, y / 8, tile7);
		ubox_put_tile(x / 8 -1, y / 8 + 1, tile8);
	}


}*/

void update_enemy() {

	uint8_t sprite_attribute = get_enemy_color();
	uint8_t enemy_type = self->subtype;

	update_common_state();
	update_character();

	if (self->state != PS_DEAD && self->state != PS_NONE) {

		switch (enemy_type) {

		case ENEMY_STATIC:
			update_enemy_static();
			break;
		case ENEMY_MOVE:
			update_enemy_move();
			break;
		case ENEMY_WANDERER:
			update_enemy_wanderer();
			break;
		case ENEMY_TRACER:
			update_enemy_tracer();
			break;
		case ENEMY_WANDERER_STAIR:
			update_enemy_wanderer_stair();
			break;
		}

		process_intersect_player();
	}

	//ubox_render_background(self->type, self->x, self->y, walk_frames[self->frame]);


	render_enemy_sprite(sprite_attribute);
}

void enemy_strategy_look_around() {
	self->frame = 3;
	if (++self->delay == 30) {
		self->delay = 0;
		self->dir ^= 1;
	}

	self->control = 0;
}


void enemy_strategy_move() {
	if (self->state == PS_MOVE || self->state == PS_IDLE) {

		self->control = self->dir ? UBOX_MSX_CTL_LEFT : UBOX_MSX_CTL_RIGHT;

		int8_t x_offset = self->dir ? -1 : 8;
		if (is_map_blocked(self->x + x_offset, self->y + 15) || is_map_blocked(self->x + x_offset, self->y + 7))
		{
			if (!is_map_blocked(self->x + x_offset, self->y + 7) && !is_map_blocked(self->x + x_offset, self->y - 1) && !is_map_blocked(self->x, self->y - 1))
				self->control |= UBOX_MSX_CTL_FIRE1;
			else
				self->control = self->dir ? UBOX_MSX_CTL_RIGHT : UBOX_MSX_CTL_LEFT;
		}

	}
	else if (self->state == PS_STAIR) {
		self->control = self->dir ? UBOX_MSX_CTL_LEFT : UBOX_MSX_CTL_RIGHT;
	}

}

void enemy_strategy_no_fall() {

	int8_t x_offset = self->dir ? -8 : 8;

	if (!check_floor(self->x + x_offset, self->y + 16, 6) && !check_floor(self->x + x_offset, self->y + 16 + 8, 6)) {

		if (check_floor(self->x + x_offset * 2, self->y + 16, 6))
			self->control |= UBOX_MSX_CTL_FIRE1;
		else
			self->control = self->dir ? UBOX_MSX_CTL_RIGHT : UBOX_MSX_CTL_LEFT;

	}
}


void enemy_strategy_stair()
{
	if (self->state == PS_MOVE) {

		if(!(self->flags & 64))
			enemy_strategy_no_fall();

		if (player->y < self->y) {
			if (self->dir) {
				uint8_t tile_index = get_tile_index(self->x, self->y + 15);

				if (tile_index == STAIR_LEFT_UP_TILE)
					self->control |= UBOX_MSX_CTL_UP;
			}
			else {
				uint8_t tile_index = get_tile_index(self->x + 8, self->y + 15);

				if (tile_index == STAIR_RIGHT_UP_TILE)
					self->control |= UBOX_MSX_CTL_UP;
			}
		}
		else if (player->y > self->y)
		{
			if (self->dir) {
				uint8_t tile_index = get_tile_index(self->x, self->y + 16);

				if (tile_index == STAIR_LEFT_DOWN_TILE)
					self->control |= UBOX_MSX_CTL_DOWN;
			}
			else {
				uint8_t tile_index = get_tile_index(self->x + 8, self->y + 16);

				if (tile_index == STAIR_RIGHT_DOWN_TILE)
					self->control |= UBOX_MSX_CTL_DOWN;

			}
		}
	}
}


void enemy_strategy_wander_stair() {

	enemy_strategy_move();

	enemy_strategy_stair();

}

void update_enemy_wanderer() {

	self->control = 0;

	self->thinkingtime++;

	if (self->thinkingtime++ > 150)
	{
		self->thinkingtime = 0;

		if (self->state == PS_MOVE || self->state == PS_IDLE) {
			self->strategy++;

			if (self->strategy == 3)
				self->strategy = 0;


			self->delay = 0;

			//self->dir ^= 1;// now() % 2;
			self->frame = 0;
		}

	}

	if (self->strategy == 0)
		enemy_strategy_move();
	else if (self->strategy == 1)
		enemy_strategy_look_around();
	else
		enemy_strategy_wander_stair();
}

void update_enemy_wanderer_stair() {

	enemy_strategy_wander_stair();
}

void update_enemy_static() {
	enemy_strategy_look_around();
}

void update_enemy_move() {

	enemy_strategy_move();

	enemy_strategy_no_fall();

}

void update_enemy_tracer()
{
	self->control = 0;

	enemy_strategy_move();

	if (self->control & UBOX_MSX_CTL_FIRE1)
		return;

	enemy_strategy_stair();
}