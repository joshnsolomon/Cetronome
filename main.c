#include "met.h"

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>


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
    exit(0);
}