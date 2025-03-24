#ifndef TWK_TRIANGLE_H
#define TWK_TRIANGLE_H


#include "BaseFigure.h"

class Triangle: public BaseFigure {
public:
    Triangle(GameMode *gMode);
    void DrawFigure(int x, int y, int size) override;
};


#endif //TWK_TRIANGLE_H
