#include "met.h"
#include "constants.h"
#include "timer.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>


Met met_default =
    {.window = NULL,
    .e = 0,
    .renderer = NULL,
    .dog = NULL,
    .timer = TIMER_OFF,
    .bpm = START_BPM
    };


int setup(Met* met){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0){
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

    timer_start(&(met->timer), met->bpm);

    return 0;
}

int draw(Met* met){
    SDL_RenderClear(met->renderer);

    drawDog(met);

    SDL_RenderPresent(met->renderer);
    return 0;
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
    bool stop = false;

    if(met->e.type == SDL_QUIT){
        stop |= true;
    }
    if(met->e.type == SDL_KEYDOWN){
        if(met->e.key.keysym.sym == SDLK_SPACE){
            if(met->timer == TIMER_OFF){
                timer_start(&(met->timer), met->bpm);
            } else {
                timer_stop(&(met->timer));
            }
        } else {
            stop |= true;
        }
    }
    if(met->e.type == SDL_MOUSEBUTTONDOWN){
        stop |= true;
    }
    if(met->e.type == SDL_USEREVENT){
        printf("CLICK\n");
    }

    return stop; 
}

int leave(Met* met){
    SDL_DestroyTexture(met->dog);
    IMG_Quit();
    SDL_DestroyRenderer(met->renderer);
    SDL_DestroyWindow(met->window);
    SDL_Quit();
    return 0;
}