//
// Created by Mateusz Bednarczyk on 04/01/2026.
//

#include "../abstract/CyberSheep.h"
#include "../abstract/World.h"
#include "../abstract/SosnowskyHogweed.h"
#include <vector>
#include <cmath>
#include <limits>

void CyberSheep::action() {
    Organism* closestHogweed = nullptr;
    double minDistance = std::numeric_limits<double>::max();

    // Find the closest Sosnowsky's Hogweed
    for (Organism* org : world->getOrganisms()) {
        if (dynamic_cast<SosnowskyHogweed*>(org)) {
            double distance = std::sqrt(std::pow(org->getX() - this->x, 2) + std::pow(org->getY() - this->y, 2));
            if (distance < minDistance) {
                minDistance = distance;
                closestHogweed = org;
            }
        }
    }

    if (closestHogweed != nullptr) {
        // Move towards the closest hogweed
        int targetX = closestHogweed->getX();
        int targetY = closestHogweed->getY();
        int newX = x;
        int newY = y;

        if (x < targetX) newX++;
        else if (x > targetX) newX--;

        if (y < targetY) newY++;
        else if (y > targetY) newY--;

        // Check for collision at the new position
        Organism* other = world->getOrganismOnPosition(newX, newY);
        if (other != nullptr && other != this) {
            solveCollision(other);
        } else {
            x = newX;
            y = newY;
        }
    } else {
        // No hogweed on the map, behave like a normal animal
        Animal::action();
    }
}

void CyberSheep::solveCollision(Organism *other) {
    if (dynamic_cast<SosnowskyHogweed*>(other)) {
        // Eats the hogweed
        world->deleteOrganism(other);
        // Move to its location
        x = other->getX();
        y = other->getY();
    } else {
        // Default animal collision for other species
        Animal::solveCollision(other);
    }
}

void CyberSheep::createChild(int x, int y) {
    CyberSheep* child = new CyberSheep(world, x, y, 0);
    world->addOrganism(child);
}
