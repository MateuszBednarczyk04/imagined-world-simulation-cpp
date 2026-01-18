//
// Created by Mateusz Bednarczyk on 03/01/2026.
//

#ifndef UNTITLED_ANIMAL_H
#define UNTITLED_ANIMAL_H

#include <string>
#include <vector>
#include "../Organism.h"

class World;
class Plant;

class Animal : public Organism {
public:
    Animal(World *world, int strength, const std::string &asciiRepresentation, int x, int y, int initiative, int age)
        : Organism(world, strength, asciiRepresentation, x, y, initiative, age) {
    }

    void action() override;

    void solveCollision(Organism *other) override;
};

#endif //UNTITLED_ANIMAL_H
