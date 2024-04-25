#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define FONT_SIZE 100

int main(int argc, char *argv[]) {
    SDL_Event event;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *dog = NULL;
    SDL_Texture* letter = NULL;
    SDL_Window *window = NULL;
    TTF_Font* font = NULL;
    SDL_Color white = {0xFF, 0xFF, 0xFF};


    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    window = SDL_CreateWindow(
        "example",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    dog = IMG_LoadTexture(renderer, "../../images/dogs.png");

    font = TTF_OpenFont("../../fonts/Comic Sans MS.ttf", FONT_SIZE);
    SDL_Surface* text_surface = TTF_RenderText_Solid_Wrapped(font, "You really a bitch", white, 1080-400);
    letter = SDL_CreateTextureFromSurface(renderer, text_surface);




    while (1) {
        SDL_RenderClear(renderer);

        //draw dog
        int dw, dh;
        SDL_QueryTexture(dog, NULL, NULL, &dw, &dh);
        SDL_Rect pic = {.x = 0, .y =0, .w = dw, .h = dh};
        SDL_RenderCopy(renderer, dog, NULL, &pic);

        //draw letter
        int lw, lh;
        SDL_QueryTexture(letter, NULL, NULL, &lw, &lh);
        SDL_Rect let = {.x = 400, .y = 200, .w = lw, .h =lh};
        SDL_RenderCopy(renderer, letter, NULL, &let);

        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }



    SDL_DestroyTexture(dog);
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}