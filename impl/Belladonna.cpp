//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "../abstract/Belladonna.h"
#include "../abstract/World.h"

void Belladonna::solveCollision(Organism *other) {
    // Poison: The animal that eats this plant dies instantly.
    world->deleteOrganism(other);
    // The plant is also removed.
    world->deleteOrganism(this);
}

void Belladonna::createChild(int x, int y) {
    world->addOrganism(new Belladonna(world, x, y, 0));
}
