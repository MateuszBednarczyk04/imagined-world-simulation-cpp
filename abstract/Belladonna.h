//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#ifndef UNTITLED_BELLADONNA_H
#define UNTITLED_BELLADONNA_H

#include "Plant.h"

class Belladonna : public Plant {
public:
    Belladonna(World* world, int x, int y, int age = 0)
        : Plant(world, 99, "B", x, y, 0, age) {
    }

    void solveCollision(Organism *other) override;
    void createChild(int x, int y) override;
};

#endif //UNTITLED_BELLADONNA_H
