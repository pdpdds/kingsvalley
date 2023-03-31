#include "ubox.h"
#include "game_util.h"
#include "game.h"
#include <spman.h>
#include <mplayer.h>
#include "main.h"

#include "character_move.h"

extern void player_die();
extern void update_character();
extern void reset_sprite(uint8_t mode);
extern void draw_hud();

#define DEFAULT_PLAYER_JUMP_VELOCITY 6


void update_character_fall()
{
	uint8_t next_y = self->y + 4;

	if (check_floor(self->x, next_y + 16, 8 - 1)) {

		self->y = (next_y >> 3) * 8;
		self->state = PS_IDLE;
		return;
	}

	self->y = next_y;

}

uint8_t next_x = 0;
uint8_t next_y = 0;


uint8_t escape_stair() {

	uint8_t tileIndex = 0;
	if (self->extra2 == ACTION_STAIR_RIGHT_UP || self->extra2 == ACTION_STAIR_LEFT_DOWN) {
		tileIndex = get_tile_index(next_x + 8, next_y + 16);
		if (isStairTile2(tileIndex))
			return 0;
	}

	else {
		tileIndex = get_tile_index(next_x, next_y + 16);
		if (isStairTile(tileIndex))
			return 0;
	}

	return 1;
}

void update_character_stair() {

	uint8_t move_offset = 1;
	if (self->flags & 128) {
		move_offset *= 2;
	}

	if (self->control & UBOX_MSX_CTL_RIGHT) {
		next_x = self->x + move_offset;
		self->dir = DIR_RIGHT;

		if (self->extra2 == ACTION_STAIR_RIGHT_UP || self->extra2 == ACTION_STAIR_LEFT_DOWN)
			next_y = self->y - move_offset;
		else
			next_y = self->y + move_offset;
	}
	else if (self->control & UBOX_MSX_CTL_LEFT) {
		next_x = self->x - move_offset;
		self->dir = DIR_LEFT;

		if (self->extra2 == ACTION_STAIR_RIGHT_UP || self->extra2 == ACTION_STAIR_LEFT_DOWN)
			next_y = self->y + move_offset;
		else
			next_y = self->y - move_offset;
	}
	else 
		return;

	if (escape_stair())
		change_object_state(self, PS_FALL, self->movetype);

	self->x = next_x;
	self->y = next_y;

	if (self->delay++ == 4) {

		self->delay = 0;
		if (++self->frame == WALK_CYCLE)
			self->frame = 0;
	}

}

uint8_t is_special_digging() {

	uint8_t tile_index = get_tile_index(self->x - 8, self->y);

	if (tile_index != SOLID_TILE && tile_index != SOLID_TILE2)
		return 0;

	if ((self->x - 8) < 8 && self->dir)
		return 0;

	tile_index = get_tile_index(self->x - 8, self->y + 8);

	if (tile_index != SOLID_TILE && tile_index != SOLID_TILE2)
		return 0;

	tile_index = get_tile_index(self->x + 8, self->y);

	if (tile_index != SOLID_TILE && tile_index != SOLID_TILE2)
		return 0;

	if ((self->x + 8) > 247 && !self->dir)
		return 0;

	tile_index = get_tile_index(self->x + 8, self->y + 8);

	if (tile_index != SOLID_TILE && tile_index != SOLID_TILE2)
		return 0;


	return 1;
}

void process_digging() {

	uint8_t tile_index = 0;
	uint8_t pos_x = self->x;

	if (is_special_digging()) {
		change_object_state(self, PS_DIGGING, MOVE_PICKAX);

		if (self->dir)
			self->extra = pos_x - 8;
		else
			self->extra = pos_x + 8;
		self->extra2 = self->y;
		g_player_info.digging_count = 0;
		
		return;
	}

	if (self->dir) {

		if ((self->x % 8) < 4)
			pos_x -= 8;
	}
	else {

		if ((self->x % 8) < 4)
			pos_x += 8;
		else
			pos_x += 16;

	}

	tile_index = get_tile_index(pos_x, self->y + 15);
	if (!is_movable_tile(tile_index))
		return;

	tile_index = get_tile_index(pos_x, self->y + 16);

	if (tile_index != SOLID_TILE && tile_index != SOLID_TILE2)
		return;

	change_object_state(self, PS_DIGGING, MOVE_PICKAX);
	self->extra = pos_x;
	self->extra2 = self->y + 16;
	g_player_info.digging_count = 0;
	
}

void update_character_idle()
{
	uint8_t moved = (self->control & UBOX_MSX_CTL_RIGHT) || (self->control & UBOX_MSX_CTL_LEFT);

	self->frame = 0;
	//self->delay = 0;

	if (moved) {
		self->state = PS_MOVE;
		return;
	}

	if (self->control & UBOX_MSX_CTL_FIRE1) {

		if (self->movetype == MOVE_KNIFE)
		{
			self->state = PS_ATTACK;
		}
		else if (self->movetype == MOVE_PICKAX)
		{

			process_digging();

		}
		else
		{
			if (!is_map_blocked(self->x, self->y - 8) && !is_map_blocked(self->x + 8 - 1, self->y - 8))
			{
				change_object_state(self, PS_JUMP, self->movetype);
				self->extra = self->y;
				self->extra2 = DEFAULT_PLAYER_JUMP_VELOCITY * -1;
				self->temp = 0;
			
			}
		}

	}
}

void process_stair_action(uint8_t action) {

	if (self->state == PS_MOVE) {
		if (self->dir)
			move_left();
		else
			move_right();
	}

	uint8_t tile_index = 0;

	if (action == ACTION_STAIR_LEFT_UP || action == ACTION_STAIR_RIGHT_UP)
	{
		tile_index = get_tile_index(self->x + 4, self->y + 15);

		if (tile_index == STAIR_RIGHT_UP_TILE ||
			tile_index == STAIR_LEFT_UP_TILE)
			return;
	}

	if (action == ACTION_STAIR_LEFT_DOWN)
	{
		tile_index = get_tile_index(self->x + 8, self->y + 16);

		if (tile_index == STAIR_LEFT_DOWN_TILE ||
			tile_index == STAIR_RIGHT_DOWN_TILE)
			return;
	}


	if (action == ACTION_STAIR_RIGHT_DOWN)
	{
		tile_index = get_tile_index(self->x + 8, self->y + 16);

		if (tile_index == STAIR_LEFT_DOWN_TILE ||
			tile_index == STAIR_RIGHT_DOWN_TILE)
			return;
	}

	int8_t offset = 0;
	uint8_t isStair = 0;


	switch (action) {
	case ACTION_STAIR_LEFT_UP:
		if (self->dir)
		{
			tile_index = get_tile_index(self->x, self->y + 15);
			isStair = (tile_index == STAIR_LEFT_UP_TILE);
			offset = -1;
		}
		break;
	case ACTION_STAIR_RIGHT_UP:
		if (!self->dir)
		{
			tile_index = get_tile_index(self->x + 7, self->y + 15);
			isStair = (tile_index == STAIR_RIGHT_UP_TILE);
			offset = -1;
		}
		break;
	case ACTION_STAIR_LEFT_DOWN:
		if (self->dir)
		{
			tile_index = get_tile_index(self->x + 7, self->y + 16);
			isStair = (tile_index == STAIR_LEFT_DOWN_TILE);
			offset = 1;
		}
		break;
	case ACTION_STAIR_RIGHT_DOWN:

		if (!self->dir)
		{
			tile_index = get_tile_index(self->x, self->y + 16);
			isStair = (tile_index == STAIR_RIGHT_DOWN_TILE);
			offset = 1;
		}

		break;
	}


	if (isStair) {

		self->y += offset;
		self->state = PS_STAIR;
		self->extra2 = action;
	}
}

void update_character_digging()
{
	if (self->delay++ == 4)
	{
		self->delay = 0;
		uint8_t tile_x = self->extra;
		uint8_t tile_y = self->extra2;

		if (self->frame < 2)
			put_tile(tile_x, tile_y, BROKEN_SOLID_TILE + self->frame);

		if (++self->frame == DIGGING_CYCLE)
		{
			mplayer_play_effect_p(EFX_DIG, EFX_CHAN_NO, 0);
			put_tile(tile_x, tile_y, BLANK_TILE);
			self->frame = 0;
			update_map_data_by_position(tile_x, tile_y, BLANK_TILE);
			self->extra2 += 8;
			g_player_info.digging_count++;

			
		}
	}


	if (g_player_info.digging_count == 2 || (get_tile_index(self->extra, self->extra2) != SOLID_TILE) && get_tile_index(self->extra, self->extra2) != SOLID_TILE2) {
		change_object_state(self, PS_FALL, MOVE_NORMAL);
		reset_sprite(self->movetype);
	}
}



void update_character_attack()
{
	if (self->delay++ == 4) {
		self->delay = 0;

		if (self->frame == 1) {

			reset_sprite(MOVE_NORMAL);
			change_object_state(self, PS_IDLE, MOVE_NORMAL);

		}
		else {
			struct entity* knife = find_object(self->item);

			if (knife) {

				change_object_state(knife, PS_ATTACK, 0);

				knife->dir = self->dir;
				knife->x = self->x;
				knife->y = self->y;
				knife->roomId = self->roomId;

				knife->pivot_x = knife->dir ? 8 : 0;
				self->item = 0;

			}

			++self->frame;
		}
	}
}

void update_character_movable_door()
{
	int i = 0;
	uint8_t x = self->extra;
	uint8_t y = self->y + 8;
	uint8_t dest_x = x + 16;
	uint8_t height = self->extra2;

	if (self->dir)
		dest_x = x - 8;

	self->delay++;

	if (self->delay < 15)
	{
		
		for (i = 0; i < height; i++)
		{
			if (!self->dir) {
				put_tile(x, y - i * 8, 106);
				put_tile(x + 8, y - i * 8, 107);
			}
			else {
				put_tile(x, y - i * 8, 122);
				put_tile(x + 8, y - i * 8, 121);
			}


		}
	}
	else if (self->delay < 40)
	{
		for (i = 0; i < height; i++)
		{
			put_tile(x, y - i * 8, 84);
			put_tile(x + 8, y - i * 8, 85);
		}
	}
	else
	{
		for (i = 0; i < height; i++)
		{
			if (self->dir) {
				put_tile(x, y - i * 8, MOVABLE_DOOR_TILE1);
				put_tile(x + 8, y - i * 8, MOVABLE_DOOR_TILE2);
				update_map_data_by_position(self->extra, self->y - i * 8 + 8, MOVABLE_DOOR_TILE1);
				update_map_data_by_position(self->extra + 8, self->y - i * 8 + 8, MOVABLE_DOOR_TILE2);

			}
			else {

				put_tile(x, y - i * 8, MOVABLE_DOOR_TILE4);
				put_tile(x + 8, y - i * 8, MOVABLE_DOOR_TILE3);
				update_map_data_by_position(self->extra, self->y - i * 8 + 8, MOVABLE_DOOR_TILE4);
				update_map_data_by_position(self->extra + 8, self->y - i * 8 + 8, MOVABLE_DOOR_TILE3);
			}
		}

	}

	if (self->x != (uint8_t)dest_x)
	{
		if ((self->delay % 2) == 0) {
			if (self->dir)
				self->x -= 1;
			else
				self->x += 1;
		}

		if ((self->delay % 4) == 0) {

			if (++self->frame == WALK_CYCLE)
				self->frame = 0;
		}
	}


	if (self->x == (uint8_t)dest_x && self->delay > 50)
		change_object_state(player, PS_IDLE, player->movetype);
}


void update_character_jump()
{
	uint8_t next_x = self->x;
	uint8_t next_y = self->y;

	next_y += self->extra2;

	if (self->temp == 1)
	{
		if (self->dir) {
			next_x -= 2;
		}
		else
			next_x += 2;
	}

	if (next_y < (self->extra - 16))
		next_y = (self->extra - 16);

	if (self->extra2 < 0) {
		if (is_blocked(next_x, next_y + 8)) {

			if (is_blocked(next_x, next_y + 16)) {

				if (next_y > (self->extra - 8) && !is_blocked(next_x, next_y)) {

				}
				else
				{
					change_object_state(self, PS_FALL, self->movetype);
					return;
				}


			}
		}
	}
	else {
		if (is_blocked(next_x, next_y + 15)) {

			change_object_state(self, PS_FALL, self->movetype);
			return;
		}
	}

	self->x = next_x;
	self->y = next_y;

	if (self->extra2 < DEFAULT_PLAYER_JUMP_VELOCITY) {
		self->extra2 += 1;
	}
}

void update_character_room()
{
	if (self->state == PS_JUMP || 
		self->state == PS_MOVE ) {
		if (!self->dir) { //right move
			if (self->x >= 255 - 8)
			{
				self->x = 1;
				self->roomId += 1;
			}
		}
		else {
			if (self->x <= 4)
			{

				self->roomId -= 1;
				self->x = (uint8_t)(255 - 8);
			}
		}
	}
}

void update_character() {
	switch (self->state)
	{
	case PS_IDLE:
		update_character_idle();
		break;
	case PS_MOVE:
		update_character_move();
		break;
	case PS_FALL:
		update_character_fall();
		break;
	case PS_STAIR:
		update_character_stair();
		break;
	case PS_JUMP:
		update_character_jump();
		break;
	case PS_ATTACK:
		update_character_attack();
		break;
	case PS_DIGGING:
		update_character_digging();
		break;
	case PS_MOVABLE_DOOR:
		update_character_movable_door();
		break;
	}

	update_character_room();
}
