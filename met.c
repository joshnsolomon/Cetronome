#include "met.h"
#include "constants.h"
#include "timer.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>

SDL_Color g_white = {0xFF, 0xFF, 0xFF};


Met met_default =
    {.window = NULL,
    .e = 0,
    .renderer = NULL,
    .timer = TIMER_OFF,
    .bpm = START_BPM,
    .font = NULL,

    .datsun = DEFAULT_BUTTON,
    .drake = DEFAULT_BUTTON,

    .count = 0, 
    .max_count = MAX_COUNT,
    .count_1 = NULL,
    .count_2 = NULL,
    .count_3 = NULL,
    .count_4 = NULL,

    .datsun_sound = NULL,
    .kick = NULL,
    .snare = NULL,
    .hat = NULL
    };


int setup(Met* met){
    //init stuff
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0){
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return -1;
    }
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();


    //insert window
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

    //renderer
    met->renderer = SDL_CreateRenderer(met->window,-1,SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(met->renderer, 0x01, 0x32, 0x20,255); //make background dark green

    //renders that don't change, the ones that do are in draw functions
    met->drake.texture = IMG_LoadTexture(met->renderer, DOG_IMAGE_PATH);
    met->datsun.texture = IMG_LoadTexture(met->renderer, DATSUN_IMAGE_PATH);

    //fonts
    met->font = TTF_OpenFont(FONT_PATH, FONT_SIZE);

    //counts
    met->count_1 = textureFromText(met->renderer, met->font, g_white, "1");
    met->count_2 = textureFromText(met->renderer, met->font, g_white, "2");
    met->count_3 = textureFromText(met->renderer, met->font, g_white, "3");
    met->count_4 = textureFromText(met->renderer, met->font, g_white, "4");

    //audio stuff
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024); //Default audio chunksize
    met->rim = Mix_LoadWAV(RIM_PATH);
    met->kick = Mix_LoadWAV(KICK_PATH);
    met->snare = Mix_LoadWAV(SNARE_PATH);
    met->hat = Mix_LoadWAV(HAT_PATH);
    
    met->datsun_sound = Mix_LoadWAV(DATSUN_SOUND_PATH);
    met->drake_sound = Mix_LoadWAV(DRAKE_SOUND_PATH);

    //timer
    timer_start(&(met->timer), met->bpm);

    return 0;
}

SDL_Texture* textureFromText(SDL_Renderer* r, TTF_Font* font, SDL_Color color, char* text){
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* t = SDL_CreateTextureFromSurface(r,surface);
    //SDL_FreeSurface(surface);
    return t;
}




//draw stuff
int draw(Met* met){
    SDL_RenderClear(met->renderer);

    drawDog(met);
    drawCount(met);

    drawDatsun(met);

    SDL_RenderPresent(met->renderer);
    return 0;
}

int drawDog(Met* met){
    int w, h;
    SDL_QueryTexture(met->drake.texture, NULL, NULL, &w, &h);
    SDL_Rect texr;
    texr.x = 0;
    texr.y = 0;
    texr.w = w;
    texr.h = h;

    SDL_RenderCopy(met->renderer, met->drake.texture, NULL, &texr);

    return 0;
}

int drawDatsun(Met* met){
    int x, y, w, h;
    SDL_GetWindowSize(met->window, &x, &y);
    SDL_QueryTexture(met->datsun.texture, NULL, NULL, &w, &h);
    SDL_Rect box = {.x=x-w, .y=y-h -10, .w=w, .h=h};

    //you have to save where you're drawing it to the struct
    met->datsun.posx = box.x;
    met->datsun.posy = box.y;

    SDL_RenderCopy(met->renderer, met->datsun.texture, NULL, &box);    
    return 0;

}

int drawCount(Met* met){
    SDL_Texture* t;
    switch(met->count){
        case 0: //don't draw anything
            return 0;
        case 1:
            t = met->count_1;
            break;
        case 2:
            t = met->count_2;
            break;
        case 3:
            t = met->count_3;
            break;
        case 4:
            t = met->count_4;
            break;
        default:
            printf("INVALID CASE IN DRAWCOUNT\n");

    }
    int x, y, w, h;
    SDL_GetWindowSize(met->window, &x, &y);
    SDL_QueryTexture(t, NULL, NULL, &w, &h);
    SDL_Rect box = {.x=(x-w)/2, .y=(y-h)/2, .w=w, .h=h};
    SDL_RenderCopy(met->renderer, t, NULL, &box);    
    return 0;
}

//event stuff
bool eventHandle(Met* met){
    SDL_WaitEvent(&(met->e));
    bool stop = false;

    if(met->e.type == SDL_QUIT){
        stop |= true;
    }
    if(met->e.type == SDL_KEYDOWN){
        if(met->e.key.keysym.sym == SDLK_SPACE){
            if(met->timer == TIMER_OFF){
                click(met);
                timer_start(&(met->timer), met->bpm);
            } else {
                timer_stop(&(met->timer));
                met->count = 0;
            }
        } else {
            stop |= true;
        }
    }
    if(met->e.type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x,&y);
        if( isInside(met->datsun, x, y) )
            Mix_PlayChannel(7, met->datsun_sound, 0);
        else if (isInsideSquare(met->drake, x, y))
            Mix_PlayChannel(6, met->drake_sound,0);
        else
            stop |= true;
    }
    if(met->e.type == SDL_USEREVENT){
        click(met);
    }

    return stop; 
}

int click(Met* met){
    met->count = (met->count) % met->max_count  + 1; //increment count
    switch(met->count){
        case 1:
            Mix_PlayChannel(1, met->kick, 0); //play click sound
            break;
        case 2:
            Mix_PlayChannel(2, met->hat, 0); //play click sound
            break;
        case 3:
            Mix_PlayChannel(3, met->snare, 0); //play click sound
            break;
        case 4:
            Mix_PlayChannel(4, met->hat, 0); //play click sound
            break;
        default:
            printf("INVALID COUNT NUMBER\n");
    }
    return 0;
}


//clean up
int leave(Met* met){
    SDL_DestroyTexture(met->count_1);
    SDL_DestroyTexture(met->count_2);
    SDL_DestroyTexture(met->count_3);
    SDL_DestroyTexture(met->count_4);

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();

    SDL_DestroyRenderer(met->renderer);
    SDL_DestroyWindow(met->window);
    SDL_Quit();
    return 0;
}