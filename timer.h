#ifndef TIMER_H
#define TIMER_H

#include<SDL.h>

#define TIMER_OFF 0

Uint32 callback(Uint32 interval, void* p);
int timer_start(SDL_TimerID* timer, int bpm);
int timer_stop(SDL_TimerID* timer);
int timer_restart(SDL_TimerID* timer, int bpm);

#endif