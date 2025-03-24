#ifndef TWK_RECTANGLE_H
#define TWK_RECTANGLE_H
#include "BaseFigure.h"
class Rectangle: public BaseFigure {
public:
    Rectangle(GameMode *gMode);

    void DrawFigure(int x,int y,int size) override;

};
#endif //TWK_RECTANGLE_H
