#ifndef TWK_BASEFIGURE_H
#define TWK_BASEFIGURE_H
class GameMode;

class BaseFigure {
public:
    BaseFigure(GameMode* newGameMode);
    virtual void DrawFigure(int x,int y,int size);
    int GetCurrentX() const{return currentX;}
    int GetCurrentY() const{return currentY;}

    int GetWinCount() const{return winCount;}
protected:
    GameMode* gameMode;
    int currentX=0;
    int currentY=0;
    int winCount=0;
};


#endif //TWK_BASEFIGURE_H
