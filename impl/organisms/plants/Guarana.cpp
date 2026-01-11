//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "organisms/plants/Guarana.h"
#include "../../../abstract/World.h"

void Guarana::solveCollision(Organism *other) {
    other->addStrength(3);
    world->deleteOrganism(this);
}

void Guarana::createChild(int x, int y) {
    world->addOrganism(new Guarana(world, x, y, 0));
}
