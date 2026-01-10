//
// Created by Mateusz Bednarczyk on 03/01/2026.
//

#include "../abstract/Antelope.h"
#include "../abstract/World.h"

void Antelope::action() {
    int dx = 0;
    int dy = 0;

    do {
        dx = (rand() % 5) - 2;
        dy = (rand() % 5) - 2;
    } while (dx == 0 && dy == 0);


    int newX = x + dx;
    int newY = y + dy;

    if (newX >= 0 && newX < world->getWidth() && newY >= 0 && newY < world->getHeight()) {
        Organism* other = world->getOrganismOnPosition(newX, newY);
        if (other != nullptr && other != this) {
            solveCollision(other);
        } else {
            x = newX;
            y = newY;
        }
    }
}

void Antelope::solveCollision(Organism *other) {
    if (typeid(*this) != typeid(*other) && (rand() % 2 == 0)) {
        int newX, newY;
        if (world->findFreeAdjacentSpot(this->getX(), this->getY(), newX, newY)) {
            this->setX(newX);
            this->setY(newY);
            return;
        }
    }

    Animal::solveCollision(other);
}

bool Antelope::didReflectAttack(Organism *attacker) {
    if (rand() % 2 == 0) {
        int newX, newY;
        if (world->findFreeAdjacentSpot(x, y, newX, newY)) {
            this->setX(newX);
            this->setY(newY);
            return true;
        }
    }
    return false;
}

void Antelope::createChild(int x, int y) {
    Antelope* child = new Antelope(world, x, y, 0);
    world->addOrganism(child);
}
