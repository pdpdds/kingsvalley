#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define WORLD_WIDTH 256
#define WORLD_HEIGHT 192

// 실제 좌표를 화면 좌표로 변환하는 함수
int to_screen_coord_x(int world_coord) {
    return world_coord * SCREEN_WIDTH / WORLD_WIDTH;
}

int to_screen_coord_y(int world_coord) {
    return world_coord * SCREEN_HEIGHT / WORLD_HEIGHT;
}

// 화면 좌표를 실제 좌표로 변환하는 함수
int to_world_coord_x(int screen_coord) {
    return screen_coord * WORLD_WIDTH / SCREEN_WIDTH;
}

int to_world_coord_y(int screen_coord) {
    return screen_coord * WORLD_HEIGHT / SCREEN_HEIGHT;
}

// Define a structure to hold the waypoint data
typedef struct {
    int x;
    int y;
} Waypoint;

// Define a function to generate the waypoints
void generateWaypoints(Waypoint* waypoints, int numWaypoints) {
    int screenWidth = 640;
    int screenHeight = 480;

    // Generate the waypoints randomly within the screen bounds
    for (int i = 0; i < numWaypoints; i++) {
        waypoints[i].x = rand() % screenWidth;
        waypoints[i].y = rand() % screenHeight;
    }
}


void saveWaypointStructToHeaderFile(const char* filename);
void saveWaypointsToHeaderFile(Waypoint * waypoints, int numWaypoints, const char* structName, const char* varName, const char* filename);

int main(int agrc, char** argv) {
    // Define the number of waypoints to generate
    const int MAX_WAYPOINTS = 100;

    // Allocate memory for the waypoints
    Waypoint* waypoints = (Waypoint*)malloc(sizeof(Waypoint) * MAX_WAYPOINTS);
    int numWaypoints = 0;

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Waypoint Generation Example",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640, 480, SDL_WINDOW_SHOWN);

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Generate the initial waypoints
    generateWaypoints(waypoints, numWaypoints);

    // Update the window
    SDL_RenderPresent(renderer);

    // Wait for a key press before exiting
    SDL_Event e;
    int quit = 0;
    // While application is running
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            // Handle mouse button events
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    // Add a new waypoint where the mouse was clicked
                    if (numWaypoints < MAX_WAYPOINTS) {
                        waypoints[numWaypoints].x = e.button.x;
                        waypoints[numWaypoints].y = e.button.y;
                        numWaypoints++;
                    }
                }
                else if (e.button.button == SDL_BUTTON_RIGHT) {
                    // Remove the last waypoint
                    if (numWaypoints > 0) {
                        numWaypoints--;
                    }
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        // Render the waypoints as circles
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        for (int i = 0; i < numWaypoints; i++) {
            SDL_RenderDrawPoint(renderer, waypoints[i].x, waypoints[i].y);
            SDL_RenderDrawPoint(renderer, waypoints[i].x + 1, waypoints[i].y);
            SDL_RenderDrawPoint(renderer, waypoints[i].x, waypoints[i].y + 1);
            SDL_RenderDrawPoint(renderer, waypoints[i].x + 1, waypoints[i].y + 1);
            SDL_RenderDrawPoint(renderer, waypoints[i].x - 1, waypoints[i].y);
            SDL_RenderDrawPoint(renderer, waypoints[i].x, waypoints[i].y - 1);
            SDL_RenderDrawPoint(renderer, waypoints[i].x - 1, waypoints[i].y - 1);
            SDL_RenderDrawPoint(renderer, waypoints[i].x - 1, waypoints[i].y + 1);

            if (i < numWaypoints - 1) {
                // Connect the waypoints with lines
                SDL_RenderDrawLine(renderer, waypoints[i].x, waypoints[i].y, waypoints[i + 1].x, waypoints[i + 1].y);
            }
        }

        // Update the window
        SDL_RenderPresent(renderer);
    }

    saveWaypointStructToHeaderFile("Waypoint.h");
    saveWaypointsToHeaderFile(waypoints, numWaypoints, "Waypoint", "pattern1", "Pattern1.h");

    // Destroy the renderer and window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Free the memory
    free(waypoints);

    // Quit SDL
    SDL_Quit();

    return 0;
}

void saveWaypointStructToHeaderFile(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    // Waypoint 구조체 선언문 작성
    fprintf(fp, "#ifndef WAYPOINT_H\n#define WAYPOINT_H\n\n");
    fprintf(fp, "typedef struct {\n    int x;\n    int y;\n} Waypoint;\n\n");
    fprintf(fp, "#endif // WAYPOINT_H");

    fclose(fp);
}

void saveWaypointsToHeaderFile(Waypoint* waypoints, int numWaypoints, const char* structName, const char* varName, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    // 헤더 파일에 구조체와 변수 선언문 작성
    fprintf(fp, "#ifndef %s_H\n#define %s_H\n\n", varName, varName);
    fprintf(fp, "#include \"%s.h\"\n\n", structName);
    fprintf(fp, "const int num%s = %d;\n", varName, numWaypoints);
    fprintf(fp, "%s %s[] = {\n", structName, varName);

    // Waypoint 배열 데이터 저장
    for (int i = 0; i < numWaypoints; i++) {
        fprintf(fp, "    {%d, %d}", waypoints[i].x, waypoints[i].y);
        if (i < numWaypoints - 1) {
            fprintf(fp, ",");
        }
        fprintf(fp, "\n");
    }

    // 헤더 파일 끝부분 작성
    fprintf(fp, "};\n\n#endif // %s_H", varName);

    fclose(fp);
}






    
