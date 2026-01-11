//
// Created by Mateusz Bednarczyk on 04/01/2026.
//

#include "organisms/animals/CyberSheep.h"
#include "../../../abstract/World.h"
#include <vector>
#include <limits>
#include "organisms/plants/SosnowskyHogweed.h"

using namespace std;

void CyberSheep::action() {
    Organism *closestHogweed = nullptr;
    double minDistance = numeric_limits<double>::max();

    for (Organism *org: world->getOrganisms()) {
        if (dynamic_cast<SosnowskyHogweed *>(org)) {
            const double distance = sqrt(pow(org->getX() - this->x, 2) + pow(org->getY() - this->y, 2));
            if (distance < minDistance) {
                minDistance = distance;
                closestHogweed = org;
            }
        }
    }

    if (closestHogweed != nullptr) {
        const int targetX = closestHogweed->getX();
        const int targetY = closestHogweed->getY();
        int newX = x;
        int newY = y;

        if (x < targetX) newX++;
        else if (x > targetX) newX--;

        if (y < targetY) newY++;
        else if (y > targetY) newY--;

        if (Organism *other = world->getOrganismOnPosition(newX, newY); other != nullptr && other != this) {
            solveCollision(other);
        } else {
            world->moveOrganism(this, newX, newY);
        }
    } else {
        Animal::action();
    }
}

void CyberSheep::solveCollision(Organism *other) {
    if (dynamic_cast<SosnowskyHogweed *>(other)) {
        const int targetX = other->getX();
        const int targetY = other->getY();
        world->deleteOrganism(other);
        world->moveOrganism(this, targetX, targetY);
    } else {
        Animal::solveCollision(other);
    }
}

void CyberSheep::createChild(int x, int y) {
    const auto child = new CyberSheep(world, x, y, 0);
    world->addOrganism(child);
}
