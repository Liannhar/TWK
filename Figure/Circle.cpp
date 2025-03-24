#include "../Game/GameMode.h"
#include <iostream>
#include "Circle.h"


Circle::Circle(GameMode *gMode) : BaseFigure(gMode) {
    winCount=3;
}

void Circle::DrawFigure(int x, int y,int size) {
    if(!gameMode)
    {
        printf("Gamemode is null");
        return;
    }
    BaseFigure::DrawFigure(x, y,size);
    radius=size/2;
    int cx = radius - 1;
    int cy = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    SDL_Renderer* renderer=gameMode->GetRenderer();
    while (cx >= cy) {
        SDL_RenderDrawPoint(renderer, x+radius + cx, y+radius + cy);
        SDL_RenderDrawPoint(renderer, x+radius + cy, y+radius + cx);
        SDL_RenderDrawPoint(renderer, x+radius - cy, y+radius + cx);
        SDL_RenderDrawPoint(renderer, x+radius - cx, y+radius + cy);
        SDL_RenderDrawPoint(renderer, x+radius - cx, y+radius - cy);
        SDL_RenderDrawPoint(renderer, x+radius - cy, y+radius - cx);
        SDL_RenderDrawPoint(renderer, x+radius + cy, y+radius - cx);
        SDL_RenderDrawPoint(renderer, x+radius + cx, y+radius - cy);

        if (err <= 0) {
            cy++;
            err += dy;
            dy += 2;
        }

        if (err > 0) {
            cx--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

