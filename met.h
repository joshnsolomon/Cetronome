#ifndef MET_H
#define MET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#include "constants.h"
#include "timer.h"
#include "widgets.h"


struct Met_t{ //remember to change default value in met.c
    SDL_Window* window;
    SDL_Event e;
    SDL_Renderer* renderer;
    SDL_TimerID timer;
    int bpm;
    TTF_Font* big_font;
    TTF_Font* small_font;

    //Buttons
    Button datsun;
    Button drake;
    Button up;
    Button down;

    //Switches
    Switch play;
    Switch notes;

    //stuff for the count
    int count;
    int max_count;
    SDL_Texture* count_1;
    SDL_Texture* count_2;
    SDL_Texture* count_3;
    SDL_Texture* count_4;
    
    //sounds
    Mix_Chunk* rim;
    Mix_Chunk* kick;
    Mix_Chunk* snare;
    Mix_Chunk* hat;

    Mix_Chunk* drake_sound;
    Mix_Chunk* datsun_sound;

    Mix_Chunk* note_A;
    Mix_Chunk* note_B;
    Mix_Chunk* note_C;
    Mix_Chunk* note_D;
    Mix_Chunk* note_E;
    Mix_Chunk* note_F;
    Mix_Chunk* note_G;
    
};


typedef struct Met_t Met;

extern Met met_default;

//functions
int  setup(Met* met);
int  draw(Met* met);
bool eventHandle(Met* met);
int leave(Met* met);

SDL_Texture* textureFromText(SDL_Renderer* r, TTF_Font* font, SDL_Color color, char* text);
int drawDog(Met* met);
int click(Met* met);
int drawCount(Met* met);
int drawDatsun(Met* met);
int drawBPM(Met* met);
int drawNotes(Met* met);

int min(int i, int min);
int max(int i, int max);
int start_stop(Met* met);

#endif