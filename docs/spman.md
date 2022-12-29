## Overview

**spman** is a simple sprite manager that provides:

- support for 16x16 sprites.
- an easy way to manage sprite patterns.
- a simple yet effective sprite flicker that allows displaying more than 4 sprites
  on the same line, with support for "fixed" sprites that are excluded from
  flickering.

It should be easy to modify and customize (`spman.c` is around 100 lines of code).

The manager is used as follows:

1. Initialize the manager with [spman_init](#spman_init).
2. Allocate patterns with [spman_alloc](#spman_alloc). This can be done at any
   time, it is not needed to allocate all the patterns in one go.
3. In the game loop:
   - Allocate sprites to be drawn on screen, using
     [spman_alloc_fixed_sprite](#spman_alloc_fixed_sprite) for sprites excluded
     from the flicker and [spman_alloc_sprite](#spman_alloc_sprite) for any
     other sprite.
   - Update the sprites on screen with  [spman_update](#spman_update).

The allocate/update cycle needs to happen per frame, so the flicker function is
effective. The longer between updates, the slower the flickering will be. If
the game updates at least 25/30 FPS, that's good enough for most games.

There are other functions to flush allocated sprites without updating the
screen, or to hide all the sprites on screen.

The manager supports all 64 patterns and up to 31 visible sprites (one sprite
is used by the flicker).

**spman** comes from "Sprite Pattern MANager".

