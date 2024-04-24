#include "met.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


int main(int argc, char* args[]){
    printf("Hello, world!\n");
    
    //initialize stuff for met
    INIT_DEFAULT_MET_VARS
    Met newMet = DEFAULY_MET;
    Met* met = &newMet;

    setup(met);

    //main loop
    bool quit = false;
    while (!quit){
        quit = eventHandle(met);
        draw(met);
    }

    leave(met);
    
    exit(EXIT_SUCCESS);
}