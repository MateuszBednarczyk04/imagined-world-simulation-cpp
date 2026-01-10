//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#ifndef UNTITLED_WOLF_H
#define UNTITLED_WOLF_H

#include "Animal.h"

class Wolf : public Animal {
public:
    Wolf(World* world, int x, int y, int age = 0)
        : Animal(world, 9, "W", x, y, 5, age) {
    }

    void createChild(int x, int y) override;
};

#endif //UNTITLED_WOLF_H
