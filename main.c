#include "met.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


int main(int argc, char* args[]){
    printf("Hello, world!\n");

    
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Event* e;
    Met newMet = {.window = window, .screenSurface = screenSurface, .e = e};
    Met* met = &newMet;

    setup(met);

    draw(met);

    bool quit = false;
    while (!quit){
        quit = eventHandle(met);
    }
    
    int output = leave(met);

    return output;
}