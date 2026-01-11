//
// Created by Mateusz Bednarczyk on 04/01/2026.
//

#ifndef UNTITLED_GRASS_H
#define UNTITLED_GRASS_H

#include "Plant.h"

class Grass : public Plant {
public:
    Grass(World* world, int x, int y, int age = 0)
        : Plant(world, 0, "G", x, y, 0, age) {
    }

    void action() override;
    void createChild(int x, int y) override;
};

#endif //UNTITLED_GRASS_H
