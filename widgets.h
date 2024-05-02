#ifndef WIDGETS_H
#define WIDGETS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

//button
struct Button_t{
    SDL_Texture* texture;
    int posx;
    int posy;
};

typedef struct Button_t Button;

#define DEFAULT_BUTTON {.texture = NULL, .posx = 0, .posy = 0}

//button functions
bool button_isInside(Button button, int x, int y);
bool button_isInsideSquare(Button button, int x, int y);

//switch
struct Switch_t{
    SDL_Texture* tex1;
    SDL_Texture* tex2;
    SDL_Texture* current_tex;
    bool state;
    int posx;
    int posy;
};

typedef struct Switch_t Switch;

#define DEFAULT_SWITCH {.tex1 = NULL, .tex2 = NULL, .current_tex = NULL, .state = true, .posx = 0, .posy = 0}

bool switch_isInside(Switch sw, int x, int y);
int switch_setPaths(SDL_Renderer* renderer, Switch* sw, char* path1, char* path2);
int switch_toggle(Switch* sw);

#endif