#ifndef TWK_BUTTON_H
#define TWK_BUTTON_H
#include <string>
#include "../Game/GameMode.h"

class Button {
public:
    Button(std::string text,GameMode* gMode);
    void Draw(int x,int y,int size);
    bool Check(int mx,int my);
protected:
    std::string buttonText;
    GameMode* gameMode;
    int BoxSizeModifier=10;
    SDL_Rect sizeButton;

};


#endif //TWK_BUTTON_H
