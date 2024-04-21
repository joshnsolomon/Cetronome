#ifndef MET_H
#define MET_H

#include <SDL2/SDL.h>
#include <stdbool.h>

struct Met_t{
    SDL_Window* window;
    SDL_Event* e;
    SDL_Renderer* renderer;
    SDL_Texture* dog;
};

typedef struct Met_t Met;

//Met init();
int  setup(Met* met);
int  draw(Met* met);
bool eventHandle(Met* met);
int leave(Met* met);

SDL_Rect drawDog(Met* met);

#endif