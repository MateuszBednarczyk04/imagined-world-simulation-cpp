//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "../abstract/Sheep.h"
#include "../abstract/World.h"

void Sheep::createChild(const int x, const int y) {
    world->addOrganism(new Sheep(world, x, y, 0));
}
