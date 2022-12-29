## Overview

**mplayer** provides easy access to Arkos 2 Minimal Player (AKM) ROM version
from SDCC.

The library adds support for priority based sound effects, so it is possible
to have two uninterrupted channels for music and leave the third one for
effects.

When the priority effects are used, an effect is played if no effect is
already being played or if the effect being played has less priority. The
effect number is used as priority, being effect number 1 the one with lowest
priority.

Arkos 2 Player is licensed MIT, please check `src/mplayer/akm/` directory for
further info.

Visit [Arkos Tracker 2 website](http://www.julien-nevo.com/arkostracker/) to
download the tracker.

## Exporting songs and effects

The player is quite complex and has a lot of options that can be disabled if
not used, reducing space and CPU use.

**mplayer** is only a fixed interface, and the player is compiled customised to
the song and effects used by the game.

Currently AKM can only be compiled with **rasm** (included in `./tools`), and then
processed with `Disark` to generate ASM compatible with `SDCC`. Once that code is
compiled, it will be relocated by the linker.

Notes on **Disark**:

  - It is not open source yet, so it needs to be put in the PATH. It is
    distributed as part of Arkos 2 Traker tools.
  - Because it uses uppercase labels, the variable exported and accessible from
    C will be all uppercase. For example: for `song` we will use `SONG`.

This is automated, and the only counter-intuitive step is making an ASM file
for **rasm** such as:

```
;
; to build the custom AKM player with song + effects
;

include "song_playerconfig.asm"
include "effects_playerconfig.asm"

include "../../src/mplayer/akm/akm_ubox.asm"

songDisarkGenerateExternalLabel:
include "song.asm"

effectsDisarkGenerateExternalLabel:
include "effects.asm"
```

See the example game and the commands run automatically for further details.

### Exporting the song

In Arkos Tracker 2, export the song as "AKM", using "Export as source file" and
"Generate configuration file for players".

Save the file as `song.asm`.

It should create `song_playerconfig.asm` in the same directory.

### Exporting the effects

In Arkos Tracker 2, export the effects as "AKX", using "Export as source file" and
"Generate configuration file for players".

Save the file as `effects.asm`.

It should create `effects_playerconfig.asm` in the same directory.

