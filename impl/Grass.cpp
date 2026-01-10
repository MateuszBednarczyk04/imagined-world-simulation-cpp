//
// Created by Mateusz Bednarczyk on 04/01/2026.
//

#include "../abstract/Grass.h"
#include "../abstract/World.h"

void Grass::action() {
    // Grass does nothing in its turn, as per specification.
}

void Grass::createChild(int x, int y) {
    world->addOrganism(new Grass(world, x, y, 0));
}
