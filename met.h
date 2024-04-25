#ifndef MET_H
#define MET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "constants.h"
#include "timer.h"


struct Met_t{ //remember to change default value in met.c
    SDL_Window* window;
    SDL_Event e;
    SDL_Renderer* renderer;
    SDL_Texture* dog;
    SDL_TimerID timer;
    int bpm;
    TTF_Font* font;
    char count;
    int max_count;
    SDL_Texture* count_tex;
};


typedef struct Met_t Met;



//Met init();
int  setup(Met* met);
int  draw(Met* met);
bool eventHandle(Met* met);
int leave(Met* met);

int drawDog(Met* met);
int click(Met* met);
int drawCount(Met* met);

#endif