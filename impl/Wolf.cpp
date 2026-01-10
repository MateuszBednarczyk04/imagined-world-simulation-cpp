//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "../abstract/Wolf.h"
#include "../abstract/World.h"

void Wolf::createChild(int x, int y) {
    Wolf* child = new Wolf(world, x, y, 0);
    world->addOrganism(child);
}
