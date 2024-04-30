#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

struct Button_t{
    SDL_Texture* texture;
    int posx;
    int posy;
};

typedef struct Button_t Button;

extern Button button_default;

bool isInside(Button* button, int x, int y);
