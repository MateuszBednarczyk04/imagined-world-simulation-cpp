//
// Created by Mateusz Bednarczyk on 03/01/2026.
//

#ifndef UNTITLED_PLANT_H
#define UNTITLED_PLANT_H
#include "Organism.h"

class Plant : public Organism {
public:
    Plant(int strength, const string &asciiRepresentation, int x, int y, int initiative, int age)
        : Organism(strength, asciiRepresentation, x, y, initiative, age) {
    }

    void action() override;

    void solveCollision(const Organism *other) override;
};

#endif //UNTITLED_PLANT_H
