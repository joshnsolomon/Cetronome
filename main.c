#include "met.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

extern Met met_default; //defined in met.c


int main(int argc, char* args[]){
    printf("Hello, world!\n");
    
    //initialize stuff for met
    Met newMet = met_default;
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