#include "met.h"
#include "constants.h"
#include "timer.h"

#include <SDL_image.h>
#include <stdio.h>

SDL_Color g_white = {0xFF, 0xFF, 0xFF};


Met met_default ={
    .window = NULL,
    .icon = NULL,
    .e = 0,
    .renderer = NULL,
    .timer = TIMER_OFF,
    .bpm = START_BPM,
    .big_font = NULL,
    .small_font = NULL,

    .datsun = DEFAULT_BUTTON,
    .drake = DEFAULT_BUTTON,
    .up = DEFAULT_BUTTON,
    .down = DEFAULT_BUTTON,

    .play = DEFAULT_SWITCH,
    .notes = DEFAULT_SWITCH,

    .count = 0, 
    .max_count = MAX_COUNT,
    .count_1 = NULL,
    .count_2 = NULL,
    .count_3 = NULL,
    .count_4 = NULL,


    .datsun_sound = NULL,
    .kick = NULL,
    .snare = NULL,
    .hat = NULL,

    .currentNote = 0,
    .nextNote = 0,
    .notesPlaying = false,

    .note_A = NULL,
    .note_B = NULL,
    .note_C = NULL,
    .note_D = NULL,
    .note_E = NULL,
    .note_F = NULL,
    .note_G = NULL,

    .tex_A = NULL,
    .tex_B = NULL,
    .tex_C = NULL,
    .tex_D = NULL,
    .tex_E = NULL,
    .tex_F = NULL,
    .tex_G = NULL
    };


int setup(Met* met){
    //init stuff
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0){
        printf("could not initialize sdl2: %s\n", SDL_GetError());
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
        printf("could not create window: %s\n", SDL_GetError());
        return -1;
    }

    //icon
    met->icon = IMG_Load(ICON_PATH);
    SDL_SetWindowIcon(met->window, met->icon);

    //renderer
    met->renderer = SDL_CreateRenderer(met->window,-1,SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(met->renderer, 0x01, 0x32, 0x20,255); //make background dark green

    //buttons
    met->drake.texture = IMG_LoadTexture(met->renderer, DOG_IMAGE_PATH);
    met->datsun.texture = IMG_LoadTexture(met->renderer, DATSUN_IMAGE_PATH);
    met->up.texture = IMG_LoadTexture(met->renderer, UP_IMAGE_PATH);
    met->down.texture = IMG_LoadTexture(met->renderer, DOWN_IMAGE_PATH);

    //switches
    switch_setPaths(met->renderer, &(met->play), PLAY_IMAGE_PATH, PAUSE_IMAGE_PATH);
    switch_setPaths(met->renderer, &(met->notes), OFF_IMAGE_PATH, ON_IMAGE_PATH);

    //fonts
    met->big_font = TTF_OpenFont(FONT_PATH, BIG_FONT_SIZE);
    met->small_font = TTF_OpenFont(FONT_PATH, SMALL_FONT_SIZE);

    //counts
    met->count_1 = textureFromText(met->renderer, met->big_font, g_white, "1");
    met->count_2 = textureFromText(met->renderer, met->big_font, g_white, "2");
    met->count_3 = textureFromText(met->renderer, met->big_font, g_white, "3");
    met->count_4 = textureFromText(met->renderer, met->big_font, g_white, "4");

    //audio stuff
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024); //Default audio chunksize
    met->rim = Mix_LoadWAV(RIM_PATH);
    met->kick = Mix_LoadWAV(KICK_PATH);
    met->snare = Mix_LoadWAV(SNARE_PATH);
    met->hat = Mix_LoadWAV(HAT_PATH);
    
    met->datsun_sound = Mix_LoadWAV(DATSUN_SOUND_PATH);
    met->drake_sound = Mix_LoadWAV(DRAKE_SOUND_PATH);

    //note stuff
    met->note_A = Mix_LoadWAV(NOTE_A_PATH);
    met->note_B = Mix_LoadWAV(NOTE_B_PATH);
    met->note_C = Mix_LoadWAV(NOTE_C_PATH);
    met->note_D = Mix_LoadWAV(NOTE_D_PATH);
    met->note_E = Mix_LoadWAV(NOTE_E_PATH);
    met->note_F = Mix_LoadWAV(NOTE_F_PATH);
    met->note_G = Mix_LoadWAV(NOTE_G_PATH);

    met->tex_A = textureFromText(met->renderer, met->big_font, g_white, "A");
    met->tex_B = textureFromText(met->renderer, met->big_font, g_white, "B");
    met->tex_C = textureFromText(met->renderer, met->big_font, g_white, "C");
    met->tex_D = textureFromText(met->renderer, met->big_font, g_white, "D");
    met->tex_E = textureFromText(met->renderer, met->big_font, g_white, "E");
    met->tex_F = textureFromText(met->renderer, met->big_font, g_white, "F");
    met->tex_G = textureFromText(met->renderer, met->big_font, g_white, "G");

    //timer don't start on open
    //timer_start(&(met->timer), met->bpm);

    return 0;
}

SDL_Texture* textureFromText(SDL_Renderer* r, TTF_Font* font, SDL_Color color, char* text){
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* t = SDL_CreateTextureFromSurface(r,surface);
    SDL_FreeSurface(surface);
    return t;
}




//draw stuff
int draw(Met* met){
    SDL_RenderClear(met->renderer);

    drawCount(met);

    drawDog(met);
    drawDatsun(met);
    
    drawBPM(met);
    drawNotes(met);

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
        case 0: //met paused
            t = met->count_1;
            break;
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
            break;

    }
    int x, y, w1, h1;
    SDL_GetWindowSize(met->window, &x, &y);
    SDL_QueryTexture(t, NULL, NULL, &w1, &h1);
    int x1 = (x-w1)/2;
    int y1 = (y-h1)/2;
    SDL_Rect box1 = {.x=x1, .y=y1, .w=w1, .h=h1};
    SDL_RenderCopy(met->renderer, t, NULL, &box1);    

    //draw play switch
    int w2, h2;
    SDL_QueryTexture(met->play.current_tex, NULL, NULL, &w2, &h2);
    int x2 = (x-w2)/2;
    int y2 = y1 + h1 - 60;
    met->play.posx = x2;
    met->play.posy = y2;
    SDL_Rect box2 = {.x=x2, .y=y2, .w=w2, .h=h2};
    SDL_RenderCopy(met->renderer, met->play.current_tex, NULL, &box2);


    return 0;
}

int drawBPM(Met* met){
    char tempo[10];
    sprintf(tempo,"%d BPM", met->bpm);

    static SDL_Texture* texture = NULL; //I think these two lines prevent a memory leak..
    SDL_DestroyTexture(texture);

    texture = textureFromText(met->renderer, met->small_font, g_white, tempo);

    int x, y, w, h;
    SDL_GetWindowSize(met->window, &x, &y);

    //label
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    int x1 = 415-w;
    int y1 = y - h - 10;
    SDL_Rect box1 = {.x=x1, .y=y1, .w=w, .h=h};
    SDL_RenderCopy(met->renderer, texture, NULL, &box1);    
    
    //down button
    SDL_QueryTexture(met->down.texture, NULL, NULL, &w, &h);
    int y2 = y1 - h - 10;
    int x2 = 10;
    met->down.posy = y2;
    met->down.posx = x2; 
    SDL_Rect box2 = {.x=x2, .y=y2, .w=w, .h=h};
    SDL_RenderCopy(met->renderer, met->down.texture, NULL, &box2);    
    
    //up button
    SDL_QueryTexture(met->up.texture, NULL, NULL, &w, &h);
    int y3 = y2 - h - 10;
    int x3 = 10;
    met->up.posy = y3;
    met->up.posx = x3; 
    SDL_Rect box3 = {.x=x3, .y=y3, .w=w, .h=h};
    SDL_RenderCopy(met->renderer, met->up.texture, NULL, &box3);    



    return 0;
}

int drawNotes(Met* met){

    int x, y, w1, h1;
    SDL_GetWindowSize(met->window, &x, &y);
    SDL_QueryTexture(met->notes.current_tex, NULL, NULL, &w1, &h1);
    int x1 = x - w1 - 120;
    int y1 = y - h1 + 20;
    met->notes.posx = x1;
    met->notes.posy = y1;
    SDL_Rect box1 = {.x=x1, .y=y1, .w=w1, .h=h1};
    SDL_RenderCopy(met->renderer, met->notes.current_tex, NULL, &box1);    

    if (met->notesPlaying){
        int a = x -250;
        int b = -20;
        int c = 270;

        switch(met->currentNote){
            case 0:
                break;
            case 1:
                drawNote(met->renderer, met->tex_C, a, b);
                break;
            case 2:
                drawNote(met->renderer, met->tex_D, a, b);
                break;
            case 3:
                drawNote(met->renderer, met->tex_E, a, b);
                break;
            case 4:
                drawNote(met->renderer, met->tex_F, a, b);
                break;
            case 5:
                drawNote(met->renderer, met->tex_G, a, b);
                break;
            case 6:
                drawNote(met->renderer, met->tex_A, a, b);
                break;
            case 7:
                drawNote(met->renderer, met->tex_B, a, b);
                break;
            default:
                printf("INVALID current NOTE VALUE\n");
                break;
        }

        switch(met->nextNote){
            case 0:
                break;
            case 1:
                drawNote(met->renderer, met->tex_C, a, c);
                break;
            case 2:
                drawNote(met->renderer, met->tex_D, a, c);
                break;
            case 3:
                drawNote(met->renderer, met->tex_E, a, c);
                break;
            case 4:
                drawNote(met->renderer, met->tex_F, a, c);
                break;
            case 5:
                drawNote(met->renderer, met->tex_G, a, c);
                break;
            case 6:
                drawNote(met->renderer, met->tex_A, a, c);
                break;
            case 7:
                drawNote(met->renderer, met->tex_B, a, c);
                break;
            default:
                printf("INVALID NEXT NOTE VALUE\n");
                break;
        }
    }
    return 0;
}

int drawNote(SDL_Renderer* ren, SDL_Texture* tex, int x, int y){
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    SDL_Rect box = {.x=x, .y=y, .w=w, .h=h};
    SDL_RenderCopy(ren, tex, NULL, &box);
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
        if(met->e.key.keysym.sym == SDLK_SPACE) //play pause
            start_stop(met);

        else if (met->e.key.keysym.sym == SDLK_UP) //tempo up
            met->bpm = min(met->bpm + BPM_STEP, MAX_BPM);

        else if (met->e.key.keysym.sym == SDLK_DOWN) //tempo down
            met->bpm = max(met->bpm - BPM_STEP, BPM_STEP);
        
        else if (met->e.key.keysym.sym == SDLK_n) //tempo down
            toggle_Notes(met);

    }
    if(met->e.type == SDL_MOUSEBUTTONDOWN){
        int x, y;
        SDL_GetMouseState(&x,&y);

        if( button_isInside(met->datsun, x, y) ) //datsun button
            Mix_PlayChannel(7, met->datsun_sound, 0);

        else if (button_isInsideSquare(met->drake, x, y)) //drake button
            Mix_PlayChannel(6, met->drake_sound,0);

        else if (button_isInside(met->up, x, y)){ //tempo up
            met->bpm = min(met->bpm + BPM_STEP, MAX_BPM);
        }

        else if (button_isInside(met->down, x, y)){ // tempo down
            met->bpm = max(met->bpm - BPM_STEP, BPM_STEP);
        }

        else if (switch_isInside(met->play, x, y)){ //play pause
            start_stop(met);
        }

        else if (switch_isInside(met->notes, x, y)){
            toggle_Notes(met);
        }
    }
    if(met->e.type == SDL_USEREVENT){
        click(met);
        if (met->timer != TIMER_OFF)
            timer_start(&(met->timer), met->bpm);
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

    if(met->notesPlaying)
        play_Note(met);

    return 0;
}

int toggle_Notes(Met* met){
    //change state of switch
    switch_toggle(&(met->notes));
    
    if (met->notesPlaying)
        stop_Note(met);
    
    met->notesPlaying = !(met->notesPlaying);

    return 0;
}

int play_Note(Met* met){
    if(met->count == 1){
        //new random note        
        met->currentNote = met->nextNote;
        while (met->currentNote == met->nextNote){
            met->nextNote = (rand() % 7) + 1;
        } 

        switch(met->currentNote){
            case 0:
                break;
            case 1:
                Mix_PlayChannel(5, met->note_C, 0);
                break;
            case 2:
                Mix_PlayChannel(5, met->note_D, 0);
                break;
            case 3:
                Mix_PlayChannel(5, met->note_E, 0);
                break;
            case 4:
                Mix_PlayChannel(5, met->note_F, 0);
                break;
            case 5:
                Mix_PlayChannel(5, met->note_G, 0);
                break;
            case 6:
                Mix_PlayChannel(5, met->note_A, 0);
                break;
            case 7:
                Mix_PlayChannel(5, met->note_B, 0);
                break;
            default:
                printf("INVALID NOTE VALUE\n");
                break;
        }
    }
    return 0;
}

int stop_Note(Met* met){
    Mix_HaltChannel(NOTE_CHANNEL);
    met->currentNote = met->nextNote =  0;
    return 0;
}

int min(int i, int max){
    if (i >= max)
        return max;
    else 
        return i;
}

int max(int i, int min){
    if( i <= min)
        return min;
    else
        return i;
}

int start_stop(Met* met){
    if(met->timer == TIMER_OFF){
        click(met);
        timer_start(&(met->timer), met->bpm);
        switch_toggle(&(met->play));
    } else {
        timer_stop(&(met->timer));
        met->count = 0;
        switch_toggle(&(met->play));
        stop_Note(met);
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