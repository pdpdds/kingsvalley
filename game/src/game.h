#ifndef _GAME_H
#define _GAME_H
#ifndef LOCAL
#define LOCAL extern
#endif

#define MAP_W 32
#define MAP_H 23

#define KNIFE_TILE        75
#define PICKAX_TILE        76
#define JEWEL_TILE          134
#define JEWEL_EFFECT_UP_TILE          81
#define JEWEL_EFFECT_LEFT_TILE          82
#define JEWEL_EFFECT_RIGHT_TILE          83

#define WARP_TILE          83

#define LAST_SOLID_TILE     10


#define EXIT_TILE           19
#define BLANK_TILE          0

#define MOVABLE_DOOR_TILE1          104
#define MOVABLE_DOOR_TILE2              105

#define MOVABLE_DOOR_TILE3              119
#define MOVABLE_DOOR_TILE4              120

#define SOLID_TILE          64
#define SOLID_TILE2          2
#define BROKEN_SOLID_TILE          67

#define STAIR_RIGHT_DOWN_TILE          116
#define STAIR_LEFT_DOWN_TILE          131

#define STAIR_RIGHT_UP_TILE          133
#define STAIR_LEFT_UP_TILE          118

#define STAIR_PART_TILE          84


#define GATE_LOCK_DOWN_TILE 92
#define GATE_LOCK_UP_TILE 93

#define LOCK_TILE 146

#define MAX_LIVES 2

#define MAX_ENTITIES 30
#define MAX_ROOM_COUNT 5

#define DIR_FLAG 128

#define DIR_LEFT 1
#define DIR_RIGHT 0
#define DIR_DOWN 2
#define DIR_UP 3

#define ENEMY_FRAME_WAIT 2
#define WATERDROP_FRAME_WAIT 5
#define WATERFALL_FRAME_WAIT 3
#define FRAME_WAIT 2
#define INVUL_TIME 64
#define GAMEOVER_DELAY 72

enum pattern_type
{
    PAT_ENEMY = 0,
    PAT_ENEMY_FLIP,
    PAT_KNIFE,
    PAT_KNIFE_FLIP, 
    PAT_ATTACK,
    PAT_ATTACK_FLIP,
    PAT_DIGGING,
    PAT_DIGGING_FLIP,
    PAT_PLAYER_MOVE,
    PAT_PLAYER_MOVE_FLIP,
    PAT_PLAYER_PICKAX,
    PAT_PLAYER_PICKAX_FLIP,
    PAT_PLAYER_KNIFE,
    PAT_PLAYER_KNIFE_FLIP,
    PAT_PLAYER_DOOR,
    PAT_PLAYER_KNIFE_DOOR,
};

enum GAME_STATE
{
    STATE_TITLE = 0,
    STATE_IN_GAME_ENTER,
    STATE_IN_GAME_EXIT,
    STATE_IN_GAME,
    STATE_NO_MAP,
    STATE_GAME_OVER,
    STATE_GAME_CLEAR,
    STATE_GAME_RESET,
    STATE_EXIT,
};

enum entity_type
{
    ET_UNUSED = 0,
    ET_PLAYER,
    ET_ENEMY,
    ET_JEWEL,
    ET_KNIFE,
    ET_PICKAX,
    ET_START,
    ET_EXIT,
    ET_LOCK,
    ET_TRAP,
    ET_PUSHDOOR,
};

enum player_state
{
    PS_NONE = 0,
    PS_IDLE,
    PS_ATTACK,
    PS_DEAD,
    PS_MOVE,
    PS_FALL,
    PS_MOVABLE_DOOR,
    PS_STAIR,
    PS_JUMP,
    PS_DIGGING,
};

enum player_move_type
{
    MOVE_NORMAL = 0,
    MOVE_KNIFE,
    MOVE_PICKAX,
};

enum character_action
{
    ACTION_IDLE = 0,
    ACTION_LEFT_JUMP,
    ACTION_RIGHT_JUMP,
    ACTION_JUMP_IN_PLACE,
    ACTION_LEFT_MOVE,
    ACTION_RIGHT_MOVE,
    ACTION_STAIR_UP,
    ACTION_STAIR_LEFT_UP,
    ACTION_STAIR_RIGHT_UP,
    ACTION_STAIR_DOWN,
    ACTION_STAIR_LEFT_DOWN,
    ACTION_STAIR_RIGHT_DOWN,
    ACTION_ATTACK_KNIFE,
    ACTION_PICKAX_DIGGING,
};

struct entity
{
    uint8_t type;
    uint8_t subtype;
    uint8_t state;
    uint8_t movetype;
    uint8_t control;
    uint8_t pat;
    uint8_t identifier;
    uint8_t roomId;
    uint8_t x;
    uint8_t y;
    uint8_t regentime;
    uint8_t thinkingtime;
    uint8_t width;
    uint8_t height;
    uint8_t pivot_x;
    uint8_t pivot_y;
    uint8_t dir;
    uint8_t delay;
    uint8_t frame;
    
    uint8_t strategy;
    uint8_t extra;
    int8_t extra2;
    uint8_t flags;
    uint8_t temp;
    uint8_t item;

    void (*update)();
};

struct PLAYER_INFO
{
    uint8_t jewels;
    uint8_t digging_count;
    uint32_t score;
    
};

void run_game(uint8_t stage);


LOCAL struct entity entities[MAX_ENTITIES];

LOCAL uint8_t control;

LOCAL const uint8_t** cur_map;
extern uint8_t cur_map_data[MAX_ROOM_COUNT][MAP_W * MAP_H];

LOCAL uint8_t lives;
LOCAL uint8_t invuln;
LOCAL uint8_t g_jewels_count;
LOCAL uint8_t gameover_delay;
LOCAL uint8_t g_gamestate;
LOCAL uint8_t g_cur_room_id;
LOCAL uint8_t g_stage;
LOCAL struct PLAYER_INFO g_player_info;
LOCAL uint8_t g_maxEntities;

LOCAL struct sprite_attr sp;
LOCAL struct entity *self;
LOCAL struct entity* player;

#define ENEMY_REBORN_CYCLE 2

#define WALK_CYCLE 4
#define STAIR_CYCLE 2
#define ATTACK_CYCLE 2
#define KNIFE_CYCLE 4
#define DIGGING_CYCLE 2


extern const uint8_t enemy_reborn_frames[ENEMY_REBORN_CYCLE];

extern const uint8_t walk_frames[WALK_CYCLE];
extern const uint8_t stair_frames[STAIR_CYCLE];
extern const uint8_t attack_frames[ATTACK_CYCLE];
extern const uint8_t knife_frames[KNIFE_CYCLE];
extern const uint8_t digging_frames[DIGGING_CYCLE];


extern void update_screen();


#ifdef LOCAL
#undef LOCAL
#endif

#endif // _GAME_H
