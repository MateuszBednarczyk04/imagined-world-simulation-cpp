//
// Created by Mateusz Bednarczyk on 04/01/2026.
//

#include "../abstract/SosnowskyHogweed.h"
#include "../abstract/World.h"
#include "../abstract/Animal.h"
#include "../abstract/CyberSheep.h"

void SosnowskyHogweed::action() {
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            const int checkX = x + dx;
            const int checkY = y + dy;

            if (checkX >= 0 && checkX < world->getWidth() && checkY >= 0 && checkY < world->getHeight()) {
                if (Organism *neighbor = world->getOrganismOnPosition(checkX, checkY);
                    neighbor != nullptr && dynamic_cast<Animal *>(neighbor)) {
                    if (typeid(*neighbor) != typeid(CyberSheep)) {
                        world->deleteOrganism(neighbor);
                    }
                }
            }
        }
    }
    Plant::action();
}

void SosnowskyHogweed::solveCollision(Organism *other) {
    if (typeid(*other) != typeid(CyberSheep)) {
        world->deleteOrganism(other);
    }
    world->deleteOrganism(this);
}

void SosnowskyHogweed::createChild(int x, int y) {
    SosnowskyHogweed *child = new SosnowskyHogweed(world, x, y, 0);
    world->addOrganism(child);
}
