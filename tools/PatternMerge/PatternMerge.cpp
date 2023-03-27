#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Define constants for the tile size and number of tiles
const int TILE_SIZE = 16;
int NUM_TILES = 2;
int NUM_TILES_X = 2;
int NUM_TILES_Y = 1;
int NUM_MERGE_COUNT = 1;

typedef struct tag_Color
{
    uint8_t R;
    uint8_t G;
    uint8_t B;
}Color;

Uint32 SDL_GetPixel(SDL_Surface* surface, int x, int y);
bool SetPixel(SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b);

SDL_Surface* mergeTiles(SDL_Surface* tiles[], int mergeTileStart, int mergeTileEnd, Uint32 backgroundColor, Color secondColor) {
    // Create the output surface
    int tileSizeX = (mergeTileEnd - mergeTileStart + 1)* TILE_SIZE / 2;
    SDL_Surface* outputSurface = SDL_CreateRGBSurface(0, tileSizeX, TILE_SIZE, 24, 0, 0, 0, 0);

    int mergeloop = (mergeTileEnd - mergeTileStart + 1) / 2;

    for (int i = 0; i < mergeloop; i++)
    {
        int tileIndex1 = (i * 2 + mergeTileStart) ;
        int tileIndex2 = (i * 2 + mergeTileStart) + 1;
        // Copy the pixels from the tiles to the output surface
        for (int y = 0; y < TILE_SIZE; y++) {
            for (int x = 0; x < TILE_SIZE; x++) {

                Uint32 tile1Pixel = SDL_GetPixel(tiles[tileIndex1], x, y);

                if (x < TILE_SIZE && y < TILE_SIZE && tile1Pixel != backgroundColor) {
                    Color current;
                    current.R = tile1Pixel;
                    current.G = tile1Pixel >> 8;
                    current.B = tile1Pixel >> 16;
                    SetPixel(outputSurface, x + TILE_SIZE * i, y, current.R, current.G, current.B);
                }

                Uint32 tile2Pixel = SDL_GetPixel(tiles[tileIndex2], x, y);

                if (x < TILE_SIZE && y < TILE_SIZE && tile2Pixel != backgroundColor) {
                    /*Color current;
                    current.R = tile2Pixel;
                    current.G = tile2Pixel >> 8;
                    current.B = tile2Pixel >> 16;*/
                    SetPixel(outputSurface, x + TILE_SIZE * i, y, secondColor.R, secondColor.G, secondColor.B);

                }
            }
        }
    }

    return outputSurface;
}

Uint32 SDL_GetPixel(SDL_Surface * surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    switch (bpp) {
    case 1:
        return *p;
    case 2:
        return *(Uint16*)p;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            return p[0] << 16 | p[1] << 8 | p[2];
        }
        else {
            return p[0] | p[1] << 8 | p[2] << 16;
        }
    case 4:
        return *(Uint32*)p;
    default:
        return 0;
    }
}


#undef main
int main(int argc, char* argv[]) {
    // Initialize SDL and SDL_image
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    // Check that a command-line argument was provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file.png>" << std::endl;
        return 1;
    }

    // Load the input PNG file
    const char* inputFile = argv[1];
    SDL_Surface* inputSurface = IMG_Load(inputFile);
    if (!inputSurface) {
        std::cerr << "Failed to load input file: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Check that the input file size is a multiple of 16
    if ((inputSurface->w % 16) != 0 || (inputSurface->h % 16) != 0) {
        std::cerr << "Input file size must be a multiple of 16" << std::endl;
        return 1;
    }

    NUM_TILES_X = inputSurface->w / 16;
    NUM_TILES_Y = inputSurface->h / 16;
    NUM_TILES = NUM_TILES_X * NUM_TILES_Y;
    NUM_MERGE_COUNT = NUM_TILES / 2;
    
    // Create an array to hold the individual tiles
    // Allocate the array
    SDL_Surface** tiles = (new SDL_Surface * [NUM_TILES]);

    
    // Extract the tiles from the input image
    for (int i = 0; i < NUM_TILES_X; i++) {
        for (int j = 0; j < NUM_TILES_Y; j++) {
            int tileX = i * TILE_SIZE;
            int tileY = j * TILE_SIZE;
            tiles[i + j * NUM_TILES_X] = (SDL_Surface*)SDL_CreateRGBSurface(0, TILE_SIZE, TILE_SIZE, 32, 0, 0, 0, 0);
            SDL_Rect srcRect = { tileX, tileY, TILE_SIZE, TILE_SIZE };
            SDL_Rect dstRect = { 0, 0, TILE_SIZE, TILE_SIZE };
            SDL_BlitSurface(inputSurface, &srcRect, tiles[i + j * NUM_TILES_X], &dstRect);
        }
    }
    /*Uint32 background = 16711935;
    Color current;
    current.R = background;
    current.G = background >> 8;
    current.B = background >> 16;
    */
    //Uint32 background = SDL_GetPixel(inputSurface, 8, 0);

    int mergeTileStart = 54;
    int mergeTileEnd = 55;
    Uint32 background = 0;

    Uint32 secondColor = 0xbb5555;
    Color color;
    color.R = secondColor;
    color.G = secondColor >> 8;
    color.B = secondColor >> 16;
    SDL_Surface* outputSurface = mergeTiles(tiles, mergeTileStart, mergeTileEnd, background, color);

    // Write the output image to a new PNG file
    IMG_SavePNG(outputSurface, "output.png");

  
    // Clean up resources and exit
    SDL_FreeSurface(inputSurface);
    for (int i = 0; i < NUM_TILES; i++) {
        SDL_FreeSurface(tiles[i]);
    }

    // Deallocate the array
    delete[] tiles;

    SDL_FreeSurface(outputSurface);

    IMG_Quit();
    SDL_Quit();

    return 0;
}

bool SetPixel(SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    int bpp = surface->format->BytesPerPixel;

    SDL_assert(bpp == 3);

    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;


    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
        p[0] = b;
        p[1] = g;
        p[2] = r;
    }
    else
    {
        p[0] = r;
        p[1] = g;
        p[2] = b;
    }

    return true;
}
