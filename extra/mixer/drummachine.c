#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define FONT_SIZE 120
#define MUSIC "../../sounds/extra/soul.wav"
#define KICK "../../sounds/KICK.wav"
#define SNARE "../../sounds/SNARE.wav"
#define HAT "../../sounds/HAT.wav"

int main(int argc, char *argv[]) {
    SDL_Event event;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *dog = NULL;
    SDL_Texture* letter = NULL;
    SDL_Window *window = NULL;
    TTF_Font* font = NULL;
    SDL_Color white = {0xFF, 0xFF, 0xFF};
    Mix_Music* music = NULL;
    Mix_Chunk* kick = NULL;
    Mix_Chunk* snare = NULL;
    Mix_Chunk* hat = NULL;
    //SDL_Color dark_green = {0x01, 0x32, 0x20};


    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    window = SDL_CreateWindow(
        "example",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0x01, 0x32, 0x20,255);


    dog = IMG_LoadTexture(renderer, "../../images/dogs.png");

    font = TTF_OpenFont("../../fonts/Comic Sans MS.ttf", FONT_SIZE);
    SDL_Surface* text_surface = TTF_RenderText_Solid_Wrapped(font, "PRESS J, K, L..", white, 1080-400);
    letter = SDL_CreateTextureFromSurface(renderer, text_surface);


    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096); //Default audio chunksize
    music = Mix_LoadMUS(MUSIC);
    Mix_PlayMusic(music,1);

    kick = Mix_LoadWAV(KICK);
    snare = Mix_LoadWAV(SNARE);
    hat = Mix_LoadWAV(HAT);


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


        SDL_PollEvent(&event); 
        if (event.type == SDL_QUIT)
            break;
        if (event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_j)
                Mix_PlayChannel(1,kick,0);
            if(event.key.keysym.sym == SDLK_k)
                Mix_PlayChannel(2,snare,0);
            if(event.key.keysym.sym == SDLK_l)
                Mix_PlayChannel(3,hat,0);
        }

    }



    SDL_DestroyTexture(dog);
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}