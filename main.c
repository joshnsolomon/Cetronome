#include "met.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


int main(int argc, char* args[]){
    printf("Hello, world!\n");
    
    //initialize stuff for met
    SDL_Window* window;
    SDL_Event* e;
    SDL_Renderer* renderer;
    SDL_Texture* dog;
    Met newMet = {.window = window, .e = e, .renderer = renderer, 
                  .dog = dog};
    Met* met = &newMet;

    setup(met);

    //main loop
    bool quit = false;
    while (!quit){
        draw(met);
        quit = eventHandle(met);
    }

    leave(met);
    
    exit(EXIT_SUCCESS);
}