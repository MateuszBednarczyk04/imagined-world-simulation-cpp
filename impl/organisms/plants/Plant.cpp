//
// Created by Mateusz Bednarczyk on 10/01/2026.
//

#include "organisms/plants/Plant.h"
#include "../../../abstract/World.h"

void Plant::action() {
    if ((rand() / (double) RAND_MAX) < SPREAD_PROBABILITY) {
        if (int newX, newY; world->findFreeAdjacentSpot(x, y, newX, newY)) {
            createChild(newX, newY);
        }
    }
}

void Plant::solveCollision(Organism *attacker) {
    world->deleteOrganism(this);
}
