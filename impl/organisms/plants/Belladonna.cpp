//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "organisms/plants/Belladonna.h"
#include "../../../abstract/World.h"

void Belladonna::solveCollision(Organism *other) {
    world->deleteOrganism(other);
    world->deleteOrganism(this);
}

void Belladonna::createChild(const int x, const int y) {
    world->addOrganism(new Belladonna(world, x, y, 0));
}
