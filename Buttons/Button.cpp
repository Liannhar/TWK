#include "Button.h"
#include <SDL_ttf.h>
#include <cstdio>
#include <string>
#include <utility>

Button::Button(std::string text,GameMode* gMode) {
    buttonText=std::move(text);
    gameMode=gMode;
}


void Button::Draw(int x,int y,int size) {
    if(!gameMode)
    {
        printf("GameMode is null\n");
        return;
    }
    TTF_Font* font = TTF_OpenFont("D:/DZ/TWK/Buttons/font/Regv2c.ttf", 14);
    if (!font) {
        printf("TTF_Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttonText.c_str(), textColor);
    if (!textSurface) {
        printf("TTF_Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gameMode->GetRenderer(), textSurface);
    if (!textTexture) {
        printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    SDL_Rect renderQuad = {x+BoxSizeModifier/2, y+BoxSizeModifier/2, size, size};
    SDL_RenderCopy(gameMode->GetRenderer(), textTexture, nullptr, &renderQuad);
    SDL_SetRenderDrawColor( gameMode->GetRenderer(), 0xFF, 0xFF, 0xFF, 0xFF );
    sizeButton = {x, y, size+BoxSizeModifier, size+BoxSizeModifier};
    SDL_RenderDrawRect( gameMode->GetRenderer(), &sizeButton );
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

bool Button::Check(int mx,int my) {
    if (mx >= sizeButton.x && mx <= sizeButton.x + sizeButton.w &&
            my >= sizeButton.y && my <= sizeButton.y + sizeButton.h) {
        return true;
    }
    return false;
}


