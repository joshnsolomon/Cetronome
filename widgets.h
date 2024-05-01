#ifndef WIDGETS_H
#define WIDGETS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

struct Button_t{
    SDL_Texture* texture;
    int posx;
    int posy;
};

typedef struct Button_t Button;

#define DEFAULT_BUTTON {.texture = NULL, .posx = 0, .posy = 0}

//functions
bool isInside(Button button, int x, int y);
bool isInsideSquare(Button button, int x, int y);

#endif