#include <iostream>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include "GameMode.h"
#include "../Figure/Rectangle.h"
#include "../Figure/Circle.h"
#include "../Figure/Triangle.h"
#include "../Buttons/Button.h"
#include "../Random/Random.h"

GameMode::GameMode(SDL_Window *newWindow) {
    window = newWindow;
    random = new Random(this);
}

void GameMode::BeginPlay() {
    if (!window) {
        printf("Window is null");
    }

    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    BlockGameSizes();
    SDL_Rect fillRect = {posBlockX, posBlockY, blockSizeX, blockSizeY};
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawRect(gRenderer, &fillRect);
    CreateFigures();
    DrawStartGame();
    SDL_RenderSetClipRect(gRenderer, nullptr);

    WindowSize size = GetWindowSize();
    //buttons draw
    startButton = new Button("Start", this);
    startButton->Draw(size.width * 6 / 8, size.height / 8, size.width / 18);
    stopButton = new Button("Stop", this);
    stopButton->Draw(size.width * 6 / 8, size.height / 8 + size.width / 18 + size.height / 10, size.width / 18);
    SDL_RenderPresent(gRenderer);

    currentState = States::Idle;
}

void GameMode::BlockGameSizes() {
    WindowSize size = GetWindowSize();
    blockSizeX = size.width / 2;
    blockSizeY = size.height * 2 / 3;
    posBlockX = size.width / 8;
    posBlockY = size.height / 8;
    elementSize = blockSizeY / 9;
}

WindowSize GameMode::GetWindowSize() {
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    return {window_width, window_height};
}

void GameMode::CheckButtons() {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (startButton && startButton->Check(mouseX, mouseY) && currentState == States::Idle) {
        StartGame();
    }
    if (stopButton && stopButton->Check(mouseX, mouseY) && currentState == States::Game) {
        StopGame();
    }
}

void GameMode::Tick() {
    switch (currentState) {
        case States::Game: {
            if (gameTimeMilliseconds > SDL_GetTicks() - startTime) {
                UpdateGameWindow();
                DrawGame(gameSpeed);
                SDL_RenderPresent(gRenderer);
            } else {
                StopGame();
            }
        }
        case States::EndGame: {
            if (!CheckFiguresEndGamePosition()) {
                UpdateGameWindow();
                DrawGame(gameSpeed);
                SDL_RenderPresent(gRenderer);
            } else {
                CheckWinState();
                currentState = States::Idle;
            }
        }
        case Idle:
            break;
    }

}


void GameMode::StartGame() {
    currentState = States::Game;
    startTime = SDL_GetTicks();
}


void GameMode::StopGame() {
    currentState = States::EndGame;
}



void GameMode::DrawStartGame() {
    if (!random) {
        printf("random is null");
        return;
    }
    SDL_RenderDrawLine(gRenderer, posBlockX + blockSizeX / 3, posBlockY, posBlockX + blockSizeX / 3,
                       posBlockY + blockSizeY);
    SDL_RenderDrawLine(gRenderer, posBlockX + blockSizeX * 2 / 3, posBlockY, posBlockX + blockSizeX * 2 / 3,
                       posBlockY + blockSizeY);

    for (int i = 0; i < lineCount; i++) {
        int currentFigureYPosition = posBlockY + blockSizeY / 9;
        int currentFigureXPosition = posBlockX + blockSizeX / 9 + i * blockSizeX / 3;
        int PositionModifier = blockSizeY / 3;
        for (int j = 0; j < figures[i].size(); j++) {
            figures[i][j]->DrawFigure(currentFigureXPosition, currentFigureYPosition + j * PositionModifier,
                                      elementSize);
        }
    }
}


void GameMode::DrawGame(int changePos) {
    if (!random) {
        printf("random is null");
        return;
    }

    SDL_Rect fillRect = {posBlockX, posBlockY, blockSizeX, blockSizeY};
    SDL_RenderSetClipRect(gRenderer, &fillRect);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine(gRenderer, posBlockX + blockSizeX / 3, posBlockY, posBlockX + blockSizeX / 3,
                       posBlockY + blockSizeY);
    SDL_RenderDrawLine(gRenderer, posBlockX + blockSizeX * 2 / 3, posBlockY, posBlockX + blockSizeX * 2 / 3,
                       posBlockY + blockSizeY);

    for (int i = 0; i < lineCount; i++) {
        int currentFigureXPosition = posBlockX + blockSizeX / 9 + i * blockSizeX / 3;
        int PositionModifier = blockSizeY / 3;
        if (figures[i][0]->GetCurrentY() + changePos + elementSize <= posBlockY) {
            figures[i].erase(figures[i].begin());
        }
        for (auto &figure: figures[i]) {
            figure->DrawFigure(currentFigureXPosition, figure->GetCurrentY() + changePos, elementSize);
        }
        if (figures[i][figures[i].size() - 1]->GetCurrentY() + PositionModifier < posBlockY + blockSizeY) {
            figures[i].push_back(CreateOneFigure(random->GetRandomNumber()));
            figures[i][figures[i].size() - 1]->DrawFigure(currentFigureXPosition,
                                                          figures[i][figures[i].size() - 2]->GetCurrentY() +
                                                          PositionModifier, elementSize);
        }
    }
    SDL_RenderSetClipRect(gRenderer, nullptr);
}

void GameMode::UpdateGameWindow() {
    SDL_Rect fillRect = {posBlockX + 1, posBlockY + 1, blockSizeX - 2, blockSizeY - 2};
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &fillRect);

}

void GameMode::CreateFigures() {
    if (!random) {
        printf("random is null");
        return;
    }

    for (int i = 0; i < lineCount; i++) {
        std::vector<BaseFigure *> line;
        for (int j = 0; j < figuresCount; j++) {
            BaseFigure *figure = CreateOneFigure(random->GetRandomNumber());
            line.push_back(figure);
        }
        figures.push_back(line);
    }
}

BaseFigure *GameMode::CreateOneFigure(int number) {
    if (number == 1) {
        return new Rectangle(this);
    }
    if (number == 2) {
        return new Triangle(this);
    }
    if (number == 3) {
        return new Circle(this);
    }
    return nullptr;
}

bool GameMode::CheckFiguresEndGamePosition() {
    for (int i = 0; i < lineCount; i++) {
        for (auto &figure: figures[i]) {
            if (figure->GetCurrentY() + elementSize / 2 == posBlockY + blockSizeY / 2) {
                return true;
            }
        }
    }
    return false;
}

void GameMode::CheckWinState() {
    int summ = 0;
    for (auto &figure: figures) {
        summ += figure[figure.size() / 2]->GetWinCount();
    }

    if (summ >= winPriceRequired) {
        int win = 100 * summ / winPriceRequired;
        std::string text = std::to_string(win) + "$";
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawLine(gRenderer, posBlockX, posBlockY + blockSizeY / 2, posBlockX + blockSizeX,
                           posBlockY + blockSizeY / 2);
        TTF_Font *font = TTF_OpenFont("D:/DZ/TWK/Buttons/font/Regv2c.ttf", 18);
        if (!font) {
            printf("TTF_Error: %s\n", TTF_GetError());
            return;
        }
        SDL_Color textColor = {255, 255, 255};
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
        if (!textSurface) {
            printf("TTF_Error: %s\n", TTF_GetError());
            return;
        }
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (!textTexture) {
            printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
            return;
        }
        WindowSize size = GetWindowSize();
        int textSize = size.width > size.height ? size.width / 20 : size.height / 20;
        SDL_Rect renderQuad = {posBlockX + blockSizeX / 2 - textSize, posBlockY + blockSizeY / 2 - textSize / 2,
                               textSize * 2, textSize};
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &renderQuad);
        SDL_RenderCopy(gRenderer, textTexture, nullptr, &renderQuad);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
        TTF_CloseFont(font);
        SDL_RenderPresent(gRenderer);

    }

}

GameMode::~GameMode() {
    if (gRenderer) {
        SDL_DestroyRenderer(gRenderer);
    }
    delete startButton;
    delete stopButton;
    delete random;

    for (auto &row: figures) {
        for (BaseFigure *figure: row) {
            delete figure;
        }
    }
}






