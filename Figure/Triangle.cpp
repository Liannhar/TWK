#include <iostream>
#include "../Game/GameMode.h"
#include "Triangle.h"

Triangle::Triangle(GameMode *gMode): BaseFigure(gMode) {
    winCount=1;
}


void Triangle::DrawFigure(int x, int y,int size) {
    if(!gameMode)
    {
        printf("Gamemode is null");
        return;
    }
    BaseFigure::DrawFigure(x, y,size);
    SDL_Point points[3] = {
            {x, y+size},
            {x+size/2, y},
            {x+size, y+size}
    };
    SDL_RenderDrawLines(gameMode->GetRenderer(), points, 3);
    SDL_RenderDrawLine(gameMode->GetRenderer(), points[2].x, points[2].y, points[0].x, points[0].y);
}


