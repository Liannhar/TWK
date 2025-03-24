#include "../Game/GameMode.h"
#include "Random.h"
int Random::GetRandomNumber() {
    return dist(gen);
}

Random::Random(GameMode* gameMode) {
    if(gameMode)
    {
        std::random_device rd;
        std::mt19937 newGen(rd());
        gen=newGen;
        std::uniform_int_distribution<> newDist(1, gameMode->GetFiguresCount());;
        dist=newDist;
    }

}
