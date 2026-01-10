//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#ifndef UNTITLED_SHEEP_H
#define UNTITLED_SHEEP_H

#include "Animal.h"

class Sheep : public Animal {
public:
    Sheep(World* world, int x, int y, int age = 0)
        : Animal(world, 4, "S", x, y, 4, age) {
    }

    void createChild(int x, int y) override;
};

#endif //UNTITLED_SHEEP_H
