#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

Uint32 callback(Uint32 interval, void* p){
    printf("%s\n",(const char *) p);
    return interval;
}

int main(){

    
    SDL_Init(SDL_INIT_TIMER);

    SDL_TimerID timerID = SDL_AddTimer(1000, callback, "TIME!");

    int i = 1;

    while (true) {
        if (i == 1){
            i--;
        }
        else if (i == 0){
            i++;
        }

    }

    return 0;
}