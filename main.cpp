#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;

enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
};

void fillSurface(SDL_Surface *&surface, KeyPressSurfaces surfaceType) {
    Uint32 color = 0;

    switch (surfaceType) {
        case KEY_PRESS_SURFACE_DEFAULT:
            color = SDL_MapRGB(surface->format, 0x2F, 0x2F, 0x2F);
            break;
        case KEY_PRESS_SURFACE_LEFT:
            color = SDL_MapRGB(surface->format, 0xFF, 0x00, 0x00);
            break;
        case KEY_PRESS_SURFACE_RIGHT:
            color = SDL_MapRGB(surface->format, 0x00, 0xFF, 0x00);
            break;
        case KEY_PRESS_SURFACE_UP:
            color = SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF);
            break;
        case KEY_PRESS_SURFACE_DOWN:
            color = SDL_MapRGB(surface->format, 0xFF, 0xFF, 0x00);
            break;
        default:
            break;
    }

    SDL_FillRect(surface, NULL, color);
}

bool initialize(const char *windowTitle, SDL_Window *&window, SDL_Surface *&surface) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL coult not initialize. SDL_Error %s.\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        windowTitle,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        printf("Could not create window. SDL_Error: %s.\n", SDL_GetError());
        return false;
    }

    surface = SDL_GetWindowSurface(window);
    fillSurface(surface, KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);
    return true;
}

bool loadMedia(SDL_Surface *&mediaSurface) {
    mediaSurface = SDL_LoadBMP("assets/sample.bmp");

    if (mediaSurface == NULL) {
        printf("Could not load image: %s.\n", SDL_GetError());
        return false;
    }

    return true;
}

void dispose(SDL_Window *& window, SDL_Surface *&screenSurface, SDL_Surface *&mediaSurface) {
    SDL_FreeSurface(mediaSurface);
    SDL_FreeSurface(screenSurface);
    SDL_DestroyWindow(window);
    mediaSurface = NULL;
    screenSurface = NULL;
    window = NULL;
    SDL_Quit();
}

int main(int argc, char *args[]) {
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
    SDL_Surface *mediaSurface = NULL;

    if (!initialize("SDL", window, screenSurface)) {
        return -1;
    }

    if (!loadMedia(mediaSurface)) {
        return -1;
    }

    SDL_Event event;
    bool quit = false;
    
    while (!quit) {
        // Handle events.
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        fillSurface(screenSurface, KeyPressSurfaces::KEY_PRESS_SURFACE_UP);
                        break;
                    case SDLK_DOWN:
                        fillSurface(screenSurface, KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN);
                        break;
                    case SDLK_LEFT:
                        fillSurface(screenSurface, KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT);
                        break;
                    case SDLK_RIGHT:
                        fillSurface(screenSurface, KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT);
                        break;
                    case SDLK_SPACE:
                        fillSurface(screenSurface, KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT);
                    default:
                        break;
                }
            }
        }

        // Handle rendering.
        SDL_BlitSurface(mediaSurface, NULL, screenSurface, NULL);
        SDL_UpdateWindowSurface(window);
    }

    dispose(window, screenSurface, mediaSurface);
    return 0;
}