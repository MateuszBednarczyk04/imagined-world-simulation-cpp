//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#ifndef UNTITLED_TURTLE_H
#define UNTITLED_TURTLE_H

#include "Animal.h"

class Turtle : public Animal {
public:
    Turtle(World* world, int x, int y, int age = 0)
        : Animal(world, 2, "T", x, y, 1, age) {
    }

    void action() override;
    bool didReflectAttack(Organism *attacker) override;
    void createChild(int x, int y) override;
};

#endif //UNTITLED_TURTLE_H
