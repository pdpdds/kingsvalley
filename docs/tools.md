## Overview

These are some tools written in Python that are required to build the example
game and can be used in new projects.

This reference should complement both the command line help available in all
tools (with `-h` flag), and the example game itself.

## Data conversion tools

### png2tiles.py

This tool converts an image in PNG RGB image into a tileset of up to 256 tiles.

The image is expected to use an approximation to RGB for the colours in the
Toshiba palette.

| Palette index | RGB value | Notes |
| --- | --- | --- |
| 0 | 255, 0, 255 | Transparent |
| 1| 0,   0,   0 | |
| 2 | 102, 204, 102 | |
| 3 | 136, 238, 136 | |
| 4 | 68,  68, 221 | |
| 5 | 119, 119, 255 | |
| 6 | 187,  85,  85 | |
| 7 | 119, 221, 221 | |
| 8 | 221, 102, 102 | |
| 9 | 255, 119, 119 | |
| 10 | 204, 204,  85 | |
| 11 | 238, 238, 136 | |
| 12 | 85, 170,  85 | |
| 13 | 187,  85, 187 | |
| 14 | 204, 204, 204 | |
| 15 | 238, 238, 238 | |

Any other colour will result in an error converting the image.

The tool ensures that the tiles follow the *screen 2* mode restrictions: 2
colours per line on each 8x8 tile.

By default the generated file will include a colour map, with `ID_colors` as
identifier (if the default "tiles" is used, the table will use `tiles_colors`).

The colour table can be omitted using the `--no-colors` flag.

Example of use:
```
png2tiles.py tiles.png > tiles.h
```
This will result in a C include output. To generate assembler, use `--asm` flag.

The output can be used with [ubox_set_tiles](ubox-lib-ref.html#ubox_set_tiles) and
[ubox_set_tiles_colors](ubox-lib-ref.html#ubox_set_tiles_colors), and the rest
of the [tiles functions](ubox-lib-ref.html#tile-functions).

### png2sprites.py

This tool converts a PNG RGB image that is a multiple of 16x16 into a sprite
(or sprites), to be used by [ubox's sprite
functions](ubox-lib-ref.html#sprite-functions).

The result is 1 bit per pixel data without colour information. The colour will
be provided as part of the `attr` field in the `sprite_attr` struct when
calling [ubox_set_sprite_attr](ubox-lib-ref.html#ubox_set_sprite_attr).

The tool interprets dark grey (RGB: 28, 28, 28) as transparent in the MSX
palette, and any other colour will be used as visible monochrome data. If the
image has more than one colour, it will be used to identify different sprites.

For example:

![Example sprite with 2 colours per frame](images/player.png)

Will be translated into 6 sprites: 3 frames (16x16) with 2 sprites per frame,
corresponding to the sprite defined by the green colour and the sprite
defined by the white colour.

Usage following the example:
```
png2sprites.py -i player_sprite player.png > player.h
```

### map.py

This is a map importer to use with [tiled](https://www.mapeditor.org/) JSON format.

The map importer supports:

- **entities**: an object layer describing game entities such as enemies.
- **map**: a tile layer describing the map itself.

#### Map requirements

The map file is expected to follow this conventions:

- It is in JSON format (File > Export > JSON file format; after exported, the
  map file can be opened and saved normally with tiled).
- The map entities will be in an object layer named "Entities".
- The map tiles will be in a tile layer named "Map".
- The tileset used will be named "default".

Please check `map.json` of the example game for a reference.

#### Configuration

The map importer requires a configuration file in JSON format that provides
information about the valid entities in the map.

For each entity it expects:

- **bytes**: number of bytes, if `--max-bytes` is used, otherwise use 0.
- **w**: weight, if `--max-entities` is used, otherwise use 0.
- **name**: name to refer to this entity in tiled (required).

This allows the tool to validate the map and ensure that:

- Unknown entities are not referenced.
- The entities follow the same order expected by the game (the order is the
  entity type).
- No room has more bytes or entities than expected.

Please check `data/map_conf.json` in the example game for an example.

#### Rooms

Tiled doesn't have support to define rooms in a big map, so this importer will
split the map in rooms of a specific size (32x24 tiles by default), translating
the information of any entity on that area.

The map size must be multiple of the room size and the result will be a number
of rooms to be used independently by the game.

Each of these rooms will have the following structure:

| Size | Description |
| --- | --- |
| 2 bytes | map data length (0 for empty map, and no more data will be included) |
| 1 byte | entities length in bytes, including the terminator byte (0xff) |
| n bytes | map data (n-bit per tile, default 8-bit), may be compressed |
| m bytes | entity data (ends with 0xff) |

The output by default is a C include file.

For example:
```
map.py --aplib map.json rooms > rooms.h
```

Will generate an include file with a `rooms` array pointing to the generated
rooms. In this case, the output is compressed with [aPLib](extra-lib-ref.html#aplib-compression).

The include by default will not include the data if `LOCAL` is undefined. It
should be included as follows in **one** C module:

```
/* in data.c for example */
#define LOCAL
#include "rooms.h"
#undef LOCAL

```

Refer to the example game and `run_game()` in `game.c` for a full example.

#### Entities

Entities are defined in the `Entities` layer by using rectangle objects.

The expected properties are:

- **x** and **y** for the position.
- **name** for the entity type, and it should match a name in the map configuration.
- **width** and **height** optionally, see "Custom properties".

In "Custom properties" the map importer supports:

- **param** (type int, 0 or 1): a bit encoded in as MSB in the entity type.
- **fixed** (type int, 0 or 1): if the width or the height should be encoded as
  part of the entity.

The entities are encoded as 3 bytes by default, as follows.

| Byte | Description |
| --- | --- |
| t | MSB is set if param is 1, the rest (7 lower bits, from 0 to 127) is the index of the entity in the configuration file |
| x | x position in the room, in pixels|
| y | y position in the room, in pixels|

If the entity has the `fixed` property, an extra byte is added with the width
or height (whatever is bigger) *in tiles*. This can be used for entities that
cover an area, for example a moving platform. The example game doesn't use
this property.

The entities are encoded in a stream that ends with the byte `0xff` as terminator.

Refer to the example game and `init_map_entities()` in `game.c` for a full example.

## Build helpers

### chksize

This tool is used to calculate how much much space in the DATA and CODE
sections is used by the game.

It takes three parameters:

- the CODE limit (in hexadecimal)
- the DATA limit (in hexadecimal)
- the map file (output of SDCC)

For example:
```
chksize 8000 4000 game.map
```

Has the output:
```
ROM: CODE  11430 bytes
     INIT  00016 bytes
     Total 11446 bytes
RAM:       01256 bytes
```

If the CODE + INIT (ROM) or the DATA (RAM) is over the provided limits, the
tool will report it with an error.

### mkdeps.py

This is a wrapper around `sdcc -MM` to automatically generate a `Makefile.deps`
with the dependencies to build a project.

This ensures that only the required files are compiled when there is a change
in the project, reducing the compilation time during development.

See `game/Makefile` for an example.

