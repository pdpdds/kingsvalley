#include "ubox.h"
#include "game_util.h"
#include "character.h"

#define DEFAULT_PLAYER_JUMP_VELOCITY 6

static uint8_t get_character_action()
{
	uint8_t right = (self->control & UBOX_MSX_CTL_RIGHT);
	uint8_t left = (self->control & UBOX_MSX_CTL_LEFT);
	uint8_t up = (self->control & UBOX_MSX_CTL_UP);
	uint8_t down = (self->control & UBOX_MSX_CTL_DOWN);
	uint8_t fire = (self->control & UBOX_MSX_CTL_FIRE1);

	if (left)
	{
		self->dir = DIR_LEFT;
	}
	else if (right)
		self->dir = DIR_RIGHT;

	if (fire)
	{
		if (self->movetype == MOVE_KNIFE)
			return ACTION_ATTACK_KNIFE;

		if (self->movetype == MOVE_PICKAX)
			return ACTION_PICKAX_DIGGING;

		if (left)
			return ACTION_LEFT_JUMP;

		if (right)
			return ACTION_RIGHT_JUMP;

		return ACTION_JUMP_IN_PLACE;
	}

	if (up)
	{
		if (left)
			return ACTION_STAIR_LEFT_UP;

		if (right)
			return ACTION_STAIR_RIGHT_UP;

		return ACTION_STAIR_UP;
	}

	if (down)
	{
		if (left)
			return ACTION_STAIR_LEFT_DOWN;

		if (right)
			return ACTION_STAIR_RIGHT_DOWN;

		return ACTION_STAIR_DOWN;
	}

	if (left)
		return ACTION_LEFT_MOVE;

	if (right)
		return ACTION_RIGHT_MOVE;

	return ACTION_IDLE;
}



void move_left() {

	if (is_map_blocked(self->x, self->y + 15) || is_map_blocked(self->x, self->y + 7))
		return;

	self->x -= 1;
}

void move_right() {

	if (is_map_blocked(self->x + 8, self->y + 15) || is_map_blocked(self->x + 8, self->y + 7))
		return;

	self->x += 1;
}

void process_jump()
{
	if (!is_map_blocked(self->x, self->y - 8) && !is_map_blocked(self->x + 8 - 1, self->y - 8))
	{
		int8_t x_offset = self->dir ? -8 : 8;

		uint8_t check_tile_x = (self->x >> 3) * 8 + x_offset;
		uint8_t check_tile_y = (self->y >> 3) * 8 - 8;

		if (!is_map_blocked(check_tile_x, check_tile_y))
		{
			change_object_state(self, PS_JUMP, self->movetype);
			self->extra2 = DEFAULT_PLAYER_JUMP_VELOCITY * -1;
			self->extra = self->y;
			self->temp = 1;
		}

	}
}

void process_jump_inplace() {
	if (!is_map_blocked(self->x, self->y - 8) && !is_map_blocked(self->x + 8 - 1, self->y - 8))
	{
		change_object_state(self, PS_JUMP, self->movetype);
		self->extra2 = DEFAULT_PLAYER_JUMP_VELOCITY * -1;
		self->extra = self->y;
		self->temp = 0;


	}
}

void process_action_right() {
	if (!is_map_blocked(self->x + 8, self->y + 15) && !is_map_blocked(self->x + 8, self->y + 7))
	{
		self->dir = DIR_RIGHT;
		self->x += 1;
	}
}

void process_action_left() {
	if (!is_map_blocked(self->x - 1, self->y + 15) && !is_map_blocked(self->x - 1, self->y + 7))
	{
		self->dir = DIR_LEFT;
		self->x -= 1;
	}
}


void update_character_move()
{
	//걷기 애니메이션을 갱신
	if (self->delay++ == FRAME_WAIT)
	{
		self->delay = 0;
		if (++self->frame == WALK_CYCLE)
			self->frame = 0;
	}

	uint8_t action = get_character_action();

	switch (action)
	{
	case ACTION_IDLE:
	{
		self->state = PS_IDLE;
		self->frame = 0;
		return;
	}
	break;
	case ACTION_RIGHT_MOVE:
		process_action_right();
		break;
	case ACTION_LEFT_MOVE:
		process_action_left();
		break;

	case ACTION_ATTACK_KNIFE:
		change_object_state(self, PS_ATTACK, MOVE_KNIFE);
		break;

	case ACTION_PICKAX_DIGGING:
		process_digging();
		break;

	case ACTION_JUMP_IN_PLACE:
		process_jump_inplace();
		break;
	case ACTION_RIGHT_JUMP:
	case ACTION_LEFT_JUMP:
		process_jump();
		break;
	case ACTION_STAIR_LEFT_UP:
	case ACTION_STAIR_LEFT_DOWN:
	case ACTION_STAIR_RIGHT_DOWN:
	case ACTION_STAIR_RIGHT_UP:
		process_stair_action(action);
		break;
	}

	if (self->state == PS_MOVE)
	{
		if (!check_floor(self->x, self->y + 16, 6)) {

			self->state = PS_FALL;
			self->frame = 0;
			self->x = (self->x >> 3) * 8;
			self->y = ((self->y + 16) >> 3) * 8 - 16;
		}

	}
}
