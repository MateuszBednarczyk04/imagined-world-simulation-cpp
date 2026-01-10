//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "../abstract/Sheep.h"
#include "../abstract/World.h"

void Sheep::createChild(int x, int y) {
    Sheep* child = new Sheep(world, x, y, 0);
    world->addOrganism(child);
}
