#include "timer.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


Uint32 callback(Uint32 interval, void* p){
    //all this shit is from stack overflow
    SDL_Event e;
    SDL_UserEvent ue;

    ue.type = SDL_USEREVENT;
    ue.code = 0;
    ue.data1 = NULL;
    ue.data2 = NULL;

    e.type = SDL_USEREVENT;
    e.user = ue;

    SDL_PushEvent(&e);
    return interval;
}


int timer_start(SDL_TimerID* timer, int bpm){
    *timer =  SDL_AddTimer(60000/bpm, callback, NULL); //bpm to ms
    return 0;
}

int timer_stop(SDL_TimerID* timer){
    bool success = SDL_RemoveTimer(*timer);
    if (success){
        *timer = TIMER_OFF;
    }
    return !success;
}



