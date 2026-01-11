//
// Created by Mateusz Bednarczyk on 04/01/2026.
//

#ifndef UNTITLED_SOSNOWSKYHOGWEED_H
#define UNTITLED_SOSNOWSKYHOGWEED_H

#include "Plant.h"

class SosnowskyHogweed : public Plant {
public:
    SosnowskyHogweed(World* world, int x, int y, int age = 0)
        : Plant(world, 10, "H", x, y, 0, age) {
    }

    void action() override;
    void solveCollision(Organism *other) override;
    void createChild(int x, int y) override;
};

#endif //UNTITLED_SOSNOWSKYHOGWEED_H
