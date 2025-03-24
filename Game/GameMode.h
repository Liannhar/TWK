#ifndef TWK_GAMEMODE_H
#define TWK_GAMEMODE_H

#include <SDL.h>
#include <vector>
#include "../CoreTypes.h"
#include "../Figure/BaseFigure.h"

class Button;
class Random;

class GameMode {
public:
    explicit GameMode(SDL_Window* newWindow);
    ~GameMode();
    void StartGame();
    void BeginPlay();
    void CheckButtons();
    WindowSize GetWindowSize();
    SDL_Renderer* GetRenderer(){return gRenderer;}
    int GetFiguresCount() const{return figuresCount;}
    void Tick();

protected:
    SDL_Window* window;
    SDL_Renderer* gRenderer{};
    States currentState=States::Idle;
    Button* startButton= nullptr;
    Button* stopButton= nullptr;
    Random* random;

    Uint32 gameTimeMilliseconds=3000;
    Uint32 startTime=0;

    int gameSpeed=-1;
    int lineCount=3;
    int figuresCount=3;
    std::vector<std::vector<BaseFigure*>> figures;

    int blockSizeX=0;
    int blockSizeY=0;
    int posBlockX=0;
    int posBlockY=0;
    int elementSize=0;

    int winPriceRequired=6;

    void StopGame();
    void DrawGame(int changePos);
    void UpdateGameWindow();
    void CreateFigures();
    BaseFigure* CreateOneFigure(int number);
    void DrawStartGame();
    bool CheckFiguresEndGamePosition();
    void BlockGameSizes();
    void CheckWinState();

};


#endif //TWK_GAMEMODE_H
