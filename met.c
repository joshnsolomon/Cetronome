#include "met.h"
#include "constants.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>


int setup(Met* met){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return -1;
    }

    IMG_Init(IMG_INIT_PNG);


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

    met->renderer = SDL_CreateRenderer(met->window,-1,SDL_RENDERER_ACCELERATED);
    met->dog = IMG_LoadTexture(met->renderer,DOG_IMAGE_PATH);

}

int draw(Met* met){
    SDL_RenderClear(met->renderer);

    drawDog(met);

    SDL_RenderPresent(met->renderer);
}

int drawDog(Met* met){
    int w, h;
    SDL_QueryTexture(met->dog, NULL, NULL, &w, &h);

    SDL_Rect texr;
    texr.x = SCREEN_WIDTH/2-w/2;
    texr.y = SCREEN_HEIGHT/2-h/2;
    texr.w = w;
    texr.h = h;

    SDL_RenderCopy(met->renderer, met->dog, NULL, &texr);

    return 0;
}

bool eventHandle(Met* met){
    SDL_WaitEvent(&(met->e));
    bool output = false;

    if(met->e.type == SDL_QUIT){
        output |= true;
    }
    if(met->e.type == SDL_KEYDOWN){
        output |= true;
    }
    if(met->e.type == SDL_MOUSEBUTTONDOWN){
        output |= true;
    }

    return output; 
}

int leave(Met* met){
    SDL_DestroyTexture(met->dog);
    IMG_Quit();
    SDL_DestroyRenderer(met->renderer);
    SDL_DestroyWindow(met->window);
    SDL_Quit();
    return 0;
}