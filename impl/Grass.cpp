//
// Created by Mateusz Bednarczyk on 04/01/2026.
//

#include "../abstract/Grass.h"
#include "../abstract/World.h"

void Grass::action() {
    // Grass does nothing in its turn, as per specification.
}

void Grass::createChild(int x, int y) {
    Grass* child = new Grass(world, x, y, 0);
    world->addOrganism(child);
}
