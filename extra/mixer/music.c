#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <stdbool.h>

#define MUSIC "../../sounds/extra/devil.wav"

int main(){

SDL_Init(SDL_INIT_AUDIO);

Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096); //Default audio chunksize

Mix_Music* music = Mix_LoadMUS(MUSIC);

Mix_PlayMusic(music,1);

while (true);

return 0;
}