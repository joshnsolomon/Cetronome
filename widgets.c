#include "widgets.h"

//button stuff

bool button_isInside(Button button, int x, int y){
    //formula from math stack exchange https://math.stackexchange.com/questions/76457/check-if-a-point-is-within-an-ellipse
    int w, h;
    SDL_QueryTexture(button.texture, NULL, NULL, &w, &h);

    double height, width, offset_x, offset_y, mouse_x, mouse_y;
    height = h;
    width = w;
    offset_x = button.posx;
    offset_y = button.posy;
    mouse_x = x;
    mouse_y = y;

    double term1Top = (mouse_x - offset_x - width/2);
    term1Top = term1Top * term1Top;
    double term1Bot = (width/2) * (width/2);
    double term2Top = (mouse_y - offset_y - height/2);
    term2Top = term2Top * term2Top;
    double term2Bot = (height/2) * (height/2);

    double output = (term1Top/term1Bot) + (term2Top/term2Bot);

    if (output <= 1.0)
        return true;
    else
        return false;
}



bool button_isInsideSquare(Button button, int x, int y){
    int w, h;
    SDL_QueryTexture(button.texture, NULL, NULL, &w, &h);

    int xp = button.posx;
    int yp = button.posy;

    return !(x < xp || x > xp + w || y < yp || y >yp + h);
}



//switch stuff
bool switch_isInside(Switch sw, int x, int y){
    //formula from math stack exchange https://math.stackexchange.com/questions/76457/check-if-a-point-is-within-an-ellipse
    int w, h;
    SDL_QueryTexture(sw.current_tex, NULL, NULL, &w, &h);

    double height, width, offset_x, offset_y, mouse_x, mouse_y;
    height = h;
    width = w;
    offset_x = sw.posx;
    offset_y = sw.posy;
    mouse_x = x;
    mouse_y = y;

    double term1Top = (mouse_x - offset_x - width/2);
    term1Top = term1Top * term1Top;
    double term1Bot = (width/2) * (width/2);
    double term2Top = (mouse_y - offset_y - height/2);
    term2Top = term2Top * term2Top;
    double term2Bot = (height/2) * (height/2);

    double output = (term1Top/term1Bot) + (term2Top/term2Bot);

    if (output <= 1.0)
        return true;
    else
        return false;
}

int switch_setPaths(SDL_Renderer* renderer, Switch* sw, char* path1, char* path2){
    sw->tex1 = IMG_LoadTexture(renderer, path1);
    sw->tex2 = IMG_LoadTexture(renderer, path2);
    sw->current_tex = sw->tex1;
    return 0;
}

int switch_toggle(Switch* sw){
    sw->state = !sw->state;

    if(sw->state)
        sw->current_tex = sw->tex1;
    else
        sw->current_tex = sw->tex2;

    return 0;
}


