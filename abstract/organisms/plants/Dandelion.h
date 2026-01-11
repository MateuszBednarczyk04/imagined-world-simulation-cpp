//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#ifndef UNTITLED_DANDELION_H
#define UNTITLED_DANDELION_H

#include "Plant.h"

class Dandelion : public Plant {
public:
    Dandelion(World* world, int x, int y, int age = 0)
        : Plant(world, 0, "D", x, y, 0, age) {
    }

    void action() override;
    void createChild(int x, int y) override;
};

#endif //UNTITLED_DANDELION_H
