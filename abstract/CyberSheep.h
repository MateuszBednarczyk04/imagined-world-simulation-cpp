//
// Created by Mateusz Bednarczyk on 04/01/2026.
//

#ifndef UNTITLED_CYBERSHEEP_H
#define UNTITLED_CYBERSHEEP_H

#include "Animal.h"

class CyberSheep : public Animal {
public:
    CyberSheep(World* world, int x, int y, int age = 0)
        : Animal(world, 11, "C", x, y, 4, age) {
    }

    void action() override;
    void solveCollision(Organism *other) override;
    void createChild(int x, int y) override;
};

#endif //UNTITLED_CYBERSHEEP_H
