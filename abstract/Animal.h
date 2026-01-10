//
// Created by Mateusz Bednarczyk on 03/01/2026.
//

#ifndef UNTITLED_ANIMAL_H
#define UNTITLED_ANIMAL_H
#include "Organism.h"
#include "World.h"
#include "Plant.h"
#include <typeinfo>
#include <vector>
#include <random>

class Animal : public Organism {
protected:
    bool attackerAfterReflectionCantMove = false;

public:
    Animal(World *world, int strength, const string &asciiRepresentation, int x, int y, int initiative, int age)
        : Organism(world, strength, asciiRepresentation, x, y, initiative, age) {
    }

    void action() override {
        std::vector<pair<int, int> > possibleMoves;
        for (const auto &dir: World::CARDINAL_DIRECTIONS) {
            const int newX = x + dir.first;
            const int newY = y + dir.second;

            if (newX >= 0 && newX < world->getWidth() && newY >= 0 && newY < world->getHeight()) {
                possibleMoves.push_back({newX, newY});
            }
        }

        if (possibleMoves.empty()) {
            return;
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, possibleMoves.size() - 1);
        pair<int, int> chosenMove = possibleMoves[distrib(gen)];

        const int finalX = chosenMove.first;
        const int finalY = chosenMove.second;

        if (Organism *target = world->getOrganismOnPosition(finalX, finalY); target != nullptr && target != this) {
            solveCollision(target);
        } else {
            world->moveOrganism(this, finalX, finalY);
        }
    }

    void solveCollision(Organism *other) override {
        if (typeid(*this) == typeid(*other)) {
            if (int childX, childY; world->findFreeAdjacentSpot(this->getX(), this->getY(), childX, childY)) {
                createChild(childX, childY);
            } else if (world->findFreeAdjacentSpot(other->getX(), other->getY(), childX, childY)) {
                createChild(childX, childY);
            }
            return;
        }

        const int targetX = other->getX();
        const int targetY = other->getY();

        if (other->didReflectAttack(this)) {
            if (world->getOrganismOnPosition(targetX, targetY) == nullptr) {
                if (typeid(*other) == typeid(Animal) && dynamic_cast<Animal *>(other)->
                    getAttackerAfterReflectionCantMove()) {
                    return;
                }
                world->moveOrganism(this, targetX, targetY);
            }
            return;
        }

        if (dynamic_cast<Plant *>(other)) {
            other->solveCollision(this);
            if (world->isOrganismAlive(this)) {
                world->moveOrganism(this, targetX, targetY);
            }
            return;
        }

        if (this->getStrength() >= other->getStrength()) {
            world->deleteOrganism(other);
            world->moveOrganism(this, targetX, targetY);
        } else {
            world->deleteOrganism(this);
        }
    }

    bool getAttackerAfterReflectionCantMove() const {
        return this->attackerAfterReflectionCantMove;
    }
};

#endif //UNTITLED_ANIMAL_H
