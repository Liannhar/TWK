#ifndef TWK_CIRCLE_H
#define TWK_CIRCLE_H


#include "BaseFigure.h"

class Circle: public BaseFigure {

public:
    Circle(GameMode *gMode);

    void DrawFigure(int x, int y,int size) override;
protected:
    int radius=100;
};


#endif //TWK_CIRCLE_H
