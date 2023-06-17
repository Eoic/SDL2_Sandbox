#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL coult not initialize. SDL_Error %s.\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Sandbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Could not create window. SDL_Error: %s.\n", SDL_GetError());
        return -1;
    }
}