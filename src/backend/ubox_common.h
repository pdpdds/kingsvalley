#ifndef UBOXCOMMON_H
#define UBOXCOMMON_H
#include <ubox.h>
#include <mplayer.h>
#include <spman.h>

#define MAX_TITLE_NAME 64

enum SPRITE_MODE {
	SPRITE_PIXEL = 0,
	SPRITE_PATTERN_IMAGE,
	SPRITE_FILE_IMAGE,
};

typedef struct tag_GameSystemInfo {
	
	char _title_name[MAX_TITLE_NAME];	
	int _sprite_mode;
	int _msx_screen_width;
	int _msx_screen_height;
	int _screen_width;
	int _screen_height;	
	int _room_width;
	int _room_height;
	int _color_depth;
	int _fps;
	int _show_fps;
}GameSystemInfo;

extern GameSystemInfo* g_system_info;

#ifdef __cplusplus
extern "C" {
#endif
	//special exported api for other platform
		UBOX_EXPORT_API void ubox_init_game_system(GameSystemInfo* info);
		UBOX_EXPORT_API void ubox_set_tiles_from_file(const char* filename);

		UBOX_EXPORT_API void ubox_load_music(uint8_t music_index, char* filename, uint8_t loop);
		UBOX_EXPORT_API void ubox_load_effect(uint8_t music_index, char* filename, uint8_t loop);

		UBOX_EXPORT_API void ubox_load_sprite(uint8_t sprite_index, char* filename, uint8_t flip);

		UBOX_EXPORT_API void ubox_finalize();
		
#ifdef __cplusplus
}
#endif

#endif