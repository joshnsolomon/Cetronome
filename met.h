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

    int count;
    int max_count;
    SDL_Texture* count_1;
    SDL_Texture* count_2;
    SDL_Texture* count_3;
    SDL_Texture* count_4;
};


typedef struct Met_t Met;



//Met init();
int  setup(Met* met);
int  draw(Met* met);
bool eventHandle(Met* met);
int leave(Met* met);

SDL_Texture* textureFromText(SDL_Renderer* r, TTF_Font* font, SDL_Color color, char* text);
int drawDog(Met* met);
int click(Met* met);
int drawCount(Met* met);

#endif