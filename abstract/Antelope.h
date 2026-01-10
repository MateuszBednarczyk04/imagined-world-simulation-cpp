//
// Created by Mateusz Bednarczyk on 03/01/2026.
//

#ifndef UNTITLED_ANTELOPE_H
#define UNTITLED_ANTELOPE_H

#include "Animal.h"

class Antelope : public Animal {
public:
    Antelope(World* world, int x, int y, int age = 0)
        : Animal(world, 4, "A", x, y, 4, age) {
    }

    void action() override;
    void solveCollision(Organism *other) override;
    bool didReflectAttack(Organism *attacker) override;
    void createChild(int x, int y) override;
};

#endif //UNTITLED_ANTELOPE_H
