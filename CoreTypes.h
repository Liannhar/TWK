#ifndef TWK_CORETYPES_H
#define TWK_CORETYPES_H

enum States:int
{
    Idle=0,
    Game=1,
    EndGame=2,
};


struct WindowSize
{
    WindowSize()= default;
    WindowSize(int newW,int newH):width(newW),height(newH){};
public:
    int width=0;
    int height=0;
};



#endif //TWK_CORETYPES_H
