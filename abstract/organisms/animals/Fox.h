//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#ifndef UNTITLED_FOX_H
#define UNTITLED_FOX_H

#include "Animal.h"

class Fox : public Animal {
public:
    Fox(World* world, int x, int y, int age = 0)
        : Animal(world, 3, "F", x, y, 7, age) {
    }

    void action() override;
    void createChild(int x, int y) override;
};

#endif //UNTITLED_FOX_H
