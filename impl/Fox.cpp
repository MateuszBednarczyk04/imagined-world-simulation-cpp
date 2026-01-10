//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "../abstract/Fox.h"
#include "../abstract/World.h"

void Fox::action() {
    // Good Smell: Moves to a random adjacent tile ONLY if it is not occupied by an organism stronger than the Fox.
    int dx = 0;
    int dy = 0;
    int direction = rand() % 4;

    switch(direction) {
        case 0: dy = -1; break; // Up
        case 1: dy = 1; break;  // Down
        case 2: dx = -1; break; // Left
        case 3: dx = 1; break;  // Right
    }

    int newX = x + dx;
    int newY = y + dy;

    if (newX >= 0 && newX < world->getWidth() && newY >= 0 && newY < world->getHeight()) {
        Organism* other = world->getOrganismOnPosition(newX, newY);
        if (other != nullptr) {
            if (other->getStrength() > this->getStrength()) {
                // The other organism is stronger, Fox stays put.
                return;
            }
            // If not stronger, standard collision.
            solveCollision(other);
        } else {
            // No collision, just move
            x = newX;
            y = newY;
        }
    }
}

void Fox::createChild(int x, int y) {
    Fox* child = new Fox(world, x, y, 0);
    world->addOrganism(child);
}
