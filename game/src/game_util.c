#include "game_util.h"
#include <ubox.h>
#include <mplayer.h>

volatile long g_tick_count = 0; //Æ½ Ä«¿îÆ®

int now()
{
    return g_tick_count;
}

void my_isr()
{
    g_tick_count++;
    mplayer_play();
}

uint8_t get_tile_index(uint8_t x, uint8_t y)
{
    return cur_map_data[self->roomId][(x >> 3) + (y >> 3) * MAP_W];
}

void update_map_data_by_position(uint8_t x, uint8_t y, uint8_t tile_index) {
    cur_map_data[self->roomId][(x >> 3) + (y >> 3) * MAP_W] = tile_index;
}

uint8_t check_floor(uint8_t x, uint8_t y, uint8_t width)
{
    uint8_t tile_index = get_tile_index(x, y);
    uint8_t tile_index2 = get_tile_index(x + width, y);

    return isSolidTile(tile_index) || isSolidTile(tile_index2);
}

struct entity *find_object(uint8_t id) {
   
    struct entity* object = entities;
    for (uint8_t i = 0; i < g_maxEntities; i++, object++) {
        if (id == object->identifier)
            return object;
    }

    return 0;
}

struct entity* find_object_by_type(uint8_t type)
{
    uint8_t i;
    struct entity* object = entities;
    for (i = 0; i < g_maxEntities; i++, object++)
    {
        if (type == object->type)
            return object;
    }

    return 0;
}

struct entity* find_object_by_tile_index(uint8_t tile_x, uint8_t tile_y) {
    uint8_t x = tile_x * 8;
    uint8_t y = tile_y * 8;
    struct entity* object = entities;
    for (uint8_t i = 0 ; i < g_maxEntities; i++, object++)
    {
        if (g_cur_room_id == object->roomId) {
            if (object->x == x && object->y == y)
                return object;
        }
    }

    return 0;
}

// x and y in pixels
uint8_t is_map_blocked(uint8_t x, uint8_t y)
{
    uint8_t tile_index = get_tile_index(x, y);

    return isSolidTile(tile_index);
}

uint8_t isSolidTile(uint8_t tileIndex)
{
    return tileIndex == 2 || tileIndex == 3 || tileIndex == 65 || tileIndex == SOLID_TILE || tileIndex == 115 || tileIndex == 116 || tileIndex == 130 || tileIndex == 131 || tileIndex == MOVABLE_DOOR_TILE1 || tileIndex == MOVABLE_DOOR_TILE2 || tileIndex == MOVABLE_DOOR_TILE3 || tileIndex == MOVABLE_DOOR_TILE4;
}

uint8_t isStairTile(uint8_t tileIndex)
{
    return (tileIndex == 116 || tileIndex == 131 || tileIndex == 117 || tileIndex == 118);
}

uint8_t isStairTile2(uint8_t tileIndex)
{
    return (tileIndex == 116 || tileIndex == 131 || tileIndex == 132 || tileIndex == 133);
}

uint8_t is_movable_tile(uint8_t tileIndex)
{
    return (tileIndex == BLANK_TILE || tileIndex == 132 || tileIndex == 133 || tileIndex == 117 || tileIndex == 118);
}





uint8_t is_intersect_by_rect(struct rect_* object1, struct rect_* object2)
{
    if ((object1->x + object1->width) <= object2->x)
        return 0;

    if ((object2->x + object2->width) <=object1->x)
        return 0;

    if ((object1->y + object1->height) <= object2->y)
        return 0;

    if ((object2->y + object2->height) <= object1->y)
        return 0;

    return 1;
}

uint8_t is_intersect(struct entity* object1, struct entity* object2)
{
    struct rect_ rect1 = { object1->x, object1->y, object1->width, object1->height };
    struct rect_ rect2 = { object2->x, object2->y, object2->width, object2->height };

    return is_intersect_by_rect(&rect1, &rect2) && object1->roomId == object2->roomId;
}

uint8_t is_static_object(uint8_t tile_index) {
    return (tile_index == JEWEL_TILE) || (tile_index == PICKAX_TILE) || (tile_index == KNIFE_TILE);
}

void put_tile(uint8_t pos_x, uint8_t pos_y, uint8_t tile_index)
{
    ubox_put_tile(pos_x >> 3, pos_y >> 3, tile_index);
}

void change_object_state(struct entity* object, uint8_t state, uint8_t move_type) {
    object->state = state;
    object->movetype = move_type;
    object->delay = 0;
    object->frame = 0;
    object->extra = 0;
}


/**
 * Put a zero terminated string on the screen using tiles.
 *
 * The font starts on the tileset on tile 0 and the fist char in our has
 * ASCII value 32, so it is adjusted so we can use ASCII *uppercase* directly
 * in our C code.
 */
void put_text(uint8_t x, uint8_t y, const uint8_t* text)
{
    while (*text)
        ubox_put_tile(x++, y, *text++ - 32);
}


