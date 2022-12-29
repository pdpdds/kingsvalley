#ifndef _AP_H
#define _AP_H

#include <stdint.h>

// @aPLib compression
//
// The `ap.lib` library allows decompressing data compressed by
// [aPLib](https://ibsensoftware.com/products_aPLib.html).
//
// [apultra](https://github.com/emmanuel-marty/apultra) is an optimal
// compressor for the aPLib format and it is included in tools for convenience.
//
// It will be compiled as part of the tools, but you can compile it
// independently with:
//
// ```
// make bin/apultra
// ```
//
// The resulting binary will be placed in the `bin` directory.

/**
 * Uncompress the data pointed by `src` into the memory pointed by `dst`.
 *
 * The compressed data is expected to be in aPLib raw format.
 */
void ap_uncompress(const uint8_t *dst, const uint8_t *src);

#endif // _AP_H
