#include "BaseFigure.h"
#include "../Game/GameMode.h"
BaseFigure::BaseFigure(GameMode *newGameMode) {
    gameMode=newGameMode;
}

void BaseFigure::DrawFigure(int x,int y,int size) {

    SDL_SetRenderDrawColor( gameMode->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
    currentX=x;
    currentY=y;
}



