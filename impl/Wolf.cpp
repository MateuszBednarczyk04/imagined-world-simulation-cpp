//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "../abstract/Wolf.h"
#include "../abstract/World.h"

void Wolf::createChild(const int x, const int y) {
    world->addOrganism(new Wolf(world, x, y, 0));
}
