#include "met.h"
#include "constants.h"

#include <stdio.h>

/*
Met init(){
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Event* e;

    window = malloc(sizeof(SDL_Window));

    Met newMet = {.window = window, .screenSurface = screenSurface, .e = e};
    return newMet;
}
*/

int setup(Met* met){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return -1;
    }

    met->window = SDL_CreateWindow(
            "Cetronome",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
            );
    
    if (met->window == NULL){
        fprintf("could not create window: %s\n", SDL_GetError());
        return -1;
    }

    met->screenSurface = SDL_GetWindowSurface(met->window);

}

int draw(Met* met){
    SDL_FillRect(met->screenSurface, NULL, SDL_MapRGB((met->screenSurface)->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(met->window);
}

bool eventHandle(Met* met){
    SDL_PollEvent(met->e);
    bool output = false;

    if(met->e->type == SDL_QUIT){
        output |= true;
    }
    if(met->e->type == SDL_KEYDOWN){
        output |= true;
    }
    if(met->e->type == SDL_MOUSEBUTTONDOWN){
        output |= true;
    }

    return output; 
}

int leave(Met* met){
    SDL_DestroyWindow(met->window);
    SDL_Quit();
    return 0;
}