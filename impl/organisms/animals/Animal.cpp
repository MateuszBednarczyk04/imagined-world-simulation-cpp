//
// Created by Mateusz Bednarczyk on 10/01/2026.
//

#include <random>
#include <vector>
#include "organisms/animals/Animal.h"
#include "World.h"
#include "organisms/plants/Plant.h"
#include "organisms/animals/Turtle.h"

using namespace std;

void Animal::action() {
    vector<pair<int, int> > possibleMoves;
    for (const auto &dir: World::CARDINAL_DIRECTIONS) {
        int newX = x + dir.first;
        int newY = y + dir.second;

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

    int finalX = chosenMove.first;
    int finalY = chosenMove.second;

    Organism *target = world->getOrganismOnPosition(finalX, finalY);

    if (target != nullptr && target != this) {
        solveCollision(target);
    } else {
        world->moveOrganism(this, finalX, finalY);
    }
}

void Animal::solveCollision(Organism *other) {
    if (typeid(*this) == typeid(*other)) {
        int childX, childY;
        if (world->findFreeAdjacentSpot(this->getX(), this->getY(), childX, childY)) {
            createChild(childX, childY);
        } else if (world->findFreeAdjacentSpot(other->getX(), other->getY(), childX, childY)) {
            createChild(childX, childY);
        }
        return;
    }

    int targetX = other->getX();
    int targetY = other->getY();

    if (other->didReflectAttack(this)) {
        if (other->getAttackerAfterReflectionCantMove()) {
            return;
        }

        bool defenderEscaped = (world->getOrganismOnPosition(targetX, targetY) == nullptr);
        if (defenderEscaped) {
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
