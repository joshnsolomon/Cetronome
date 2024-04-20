#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int  setup(SDL_Window** window, SDL_Surface** screenSurface);
int  draw(SDL_Window** window, SDL_Surface** screenSurface);
bool eventHandle(SDL_Event* e);
int leave(SDL_Window* window);


int main(int argc, char* args[]){
    printf("Hello, world!\n");

    SDL_Window* window;
    SDL_Surface* screenSurface;

    setup(&window, &screenSurface);

    draw(&window, &screenSurface);

    SDL_Event e;
    bool quit = false;

    while (!quit){
        quit = eventHandle(&e);
    }

    return leave(window);
}

int setup(SDL_Window** window, SDL_Surface** screenSurface){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return -1;
    }

    *window = SDL_CreateWindow(
            "Cetronome",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
            );
    
    if (*window == NULL){
        fprintf("could not create window: %s\n", SDL_GetError());
        return -1;
    }

    *screenSurface = SDL_GetWindowSurface(*window);

}

int draw(SDL_Window** window, SDL_Surface** screenSurface){
    SDL_FillRect(*screenSurface, NULL, SDL_MapRGB((*screenSurface)->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(*window);
}

bool eventHandle(SDL_Event* e){
    SDL_PollEvent(e);
    bool output = false;

    if(e->type == SDL_QUIT){
        output |= true;
    }
    if(e->type == SDL_KEYDOWN){
        output |= true;
    }
    if(e->type == SDL_MOUSEBUTTONDOWN){
        output |= true;
    }

    return output; 
}

int leave(SDL_Window* window){
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

