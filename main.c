#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "met.h"


int main(int argc, char* args[]){
    printf("Hello, world!\n");

    SDL_Window* window;
    SDL_Surface* screenSurface;

    setup(&window, &screenSurface);

    draw(&window, &screenSurface);

    SDL_Event e;
    bool quit = false;

    while (!quit){
        quit = eventHandle(&e);
    }

    return leave(window);
}