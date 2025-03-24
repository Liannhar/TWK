#ifndef TWK_RANDOM_H
#define TWK_RANDOM_H

#include <random>

class Random {
public:
    Random(GameMode* gameMode);
    int GetRandomNumber();
protected:
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
};


#endif //TWK_RANDOM_H
