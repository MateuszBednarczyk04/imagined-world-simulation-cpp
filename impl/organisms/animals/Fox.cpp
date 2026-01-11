//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "organisms/animals/Fox.h"

#include "../../../abstract/World.h"
#include <vector>
#include <random>

void Fox::action() {
    std::vector<pair<int, int> > possibleMoves;

    for (auto &dir: World::CARDINAL_DIRECTIONS) {
        const int newX = x + dir.first;
        const int newY = y + dir.second;

        if (newX >= 0 && newX < world->getWidth() && newY >= 0 && newY < world->getHeight()) {
            if (const Organism *other = world->getOrganismOnPosition(newX, newY);
                other == nullptr || other->getStrength() <= this->getStrength()) {
                possibleMoves.push_back({newX, newY});
            }
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

    if (Organism *target = world->getOrganismOnPosition(finalX, finalY); target != nullptr) {
        solveCollision(target);
    } else {
        world->moveOrganism(this, finalX, finalY);
    }
}

void Fox::createChild(const int x, const int y) {
    world->addOrganism(new Fox(world, x, y, 0));
}
