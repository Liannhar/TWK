#include <SDL.h>
#include <iostream>
#include "Rectangle.h"
#include "../Game/GameMode.h"


Rectangle::Rectangle(GameMode *gMode) : BaseFigure(gMode) {
    winCount=2;
}

void Rectangle::DrawFigure(int x,int y,int size) {
    if(!gameMode)
    {
        printf("Gamemode is null");
        return;
    }
    BaseFigure::DrawFigure(x,y,size);
    SDL_Rect fillRect = { x, y, size, size };
    SDL_RenderDrawRect( gameMode->GetRenderer(), &fillRect );
}

