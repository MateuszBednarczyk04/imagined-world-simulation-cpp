//
// Created by Mateusz Bednarczyk on 03/01/2026.
//

#ifndef UNTITLED_ANIMAL_H
#define UNTITLED_ANIMAL_H
#include "Organism.h"
#include "World.h"
#include "Plant.h" // Include Plant header for dynamic_cast
#include <cstdlib>
#include <typeinfo>

class Animal : public Organism {
public:
    Animal(World* world, int strength, const string &asciiRepresentation, int x, int y, int initiative, int age)
        : Organism(world, strength, asciiRepresentation, x, y, initiative, age) {
    }

    void action() override {
        int oldX = x;
        int oldY = y;

        int dx = 0;
        int dy = 0;
        int direction = rand() % 4;

        switch(direction) {
            case 0: dy = -1; break; // Up
            case 1: dy = 1; break;  // Down
            case 2: dx = -1; break; // Left
            case 3: dx = 1; break;  // Right
        }

        int newX = x + dx;
        int newY = y + dy;

        if (newX >= 0 && newX < world->getWidth() && newY >= 0 && newY < world->getHeight()) {
            Organism* other = world->getOrganismOnPosition(newX, newY);
            if (other != nullptr && other != this) {
                solveCollision(other);
            } else {
                x = newX;
                y = newY;
            }
        }
    }

    void solveCollision(Organism *other) override {
        // Case 1: Same species -> Reproduce
        if (typeid(*this) == typeid(*other)) {
            int childX, childY;
            if (world->findFreeAdjacentSpot(this->getX(), this->getY(), childX, childY)) {
                createChild(childX, childY);
            }
            else if (world->findFreeAdjacentSpot(other->getX(), other->getY(), childX, childY)) {
                createChild(childX, childY);
            }
            return;
        }

        // Case 2: The other organism is a Plant -> Eat it
        if (dynamic_cast<Plant*>(other)) {
            int plantX = other->getX();
            int plantY = other->getY();
            other->solveCollision(this);
            if (world->isOrganismAlive(this)) {
                 this->setX(plantX);
                 this->setY(plantY);
            }
            return;
        }

        // Case 3: The other organism is an Animal -> Fight
        if (other->didReflectAttack(this)) {
            return;
        }

        if (this->getStrength() >= other->getStrength()) {
            int targetX = other->getX();
            int targetY = other->getY();
            world->deleteOrganism(other);
            this->setX(targetX);
            this->setY(targetY);
        } else {
            world->deleteOrganism(this);
        }
    }
};

#endif //UNTITLED_ANIMAL_H
