#include <SDL.h>
#include <cstdio>
#include <SDL_ttf.h>
#include "Game/GameMode.h"

int main(int argc, char *args[]) {
    SDL_Window *window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_Error: %s\n", TTF_GetError());
        return -1;
    }
    int display_index = 0;
    SDL_DisplayMode display_mode;
    if (SDL_GetCurrentDisplayMode(display_index, &display_mode)) {
        printf("Could not get display mode for video display #%d: %s", display_index, SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
            "Fullscreen Window",
            SDL_WINDOWPOS_CENTERED_DISPLAY(display_index),
            SDL_WINDOWPOS_CENTERED_DISPLAY(display_index),
            display_mode.w, display_mode.h,
            SDL_WINDOW_FULLSCREEN_DESKTOP
    );
    if (window == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    } else {
        SDL_Event e;
        bool quit = false;
        GameMode *gameMode = new GameMode(window);
        gameMode->BeginPlay();
        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    gameMode->CheckButtons();
                }
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        quit = true;
                    }
                }
            }
            gameMode->Tick();
        }
        delete gameMode;
    }
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();

    return 0;
}