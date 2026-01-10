#include "../abstract/Dandelion.h"
#include "../abstract/World.h"

void Dandelion::action() {
    for (int i = 0; i < 3; ++i) {
        if ((rand() / (double) RAND_MAX) < SPREAD_PROBABILITY) {
            if (int newX, newY; world->findFreeAdjacentSpot(x, y, newX, newY)) {
                createChild(newX, newY);
                break;
            }
        }
    }
}

void Dandelion::createChild(const int x, const int y) {
    world->addOrganism(new Dandelion(world, x, y));
}
