//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#ifndef UNTITLED_GUARANA_H
#define UNTITLED_GUARANA_H

#include "Plant.h"

class Guarana : public Plant {
public:
    Guarana(World* world, int x, int y, int age = 0)
        : Plant(world, 0, "G", x, y, 0, age) {
    }

    void solveCollision(Organism *other) override;
    void createChild(int x, int y) override;
};

#endif //UNTITLED_GUARANA_H
