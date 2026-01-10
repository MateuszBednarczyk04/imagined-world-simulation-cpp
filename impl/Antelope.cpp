//
// Created by Mateusz Bednarczyk on 03/01/2026.
//

#include "../abstract/Antelope.h"
#include "../abstract/World.h"

const int chanceOfAttackReflection = 2; // 50%

void Antelope::action() {
    int dx = 0;
    int dy = 0;

    switch (rand() % 4) {
        case 0: dy = -2;
            break;
        case 1: dy = 2;
            break;
        case 2: dx = -2;
            break;
        case 3: dx = 2;
            break;
    }

    const int newX = x + dx;
    const int newY = y + dy;

    if (newX >= 0 && newX < world->getWidth() && newY >= 0 && newY < world->getHeight()) {
        if (Organism *other = world->getOrganismOnPosition(newX, newY); other != nullptr) {
            solveCollision(other);
        } else {
            world->moveOrganism(this, newX, newY);
        }
    }
}

void Antelope::solveCollision(Organism *other) {
    Animal::solveCollision(other);
}

bool Antelope::didReflectAttack(Organism *attacker) {
    if (rand() % chanceOfAttackReflection == 0) {
        if (int newX, newY; world->findFreeAdjacentSpot(x, y, newX, newY)) {
            world->moveOrganism(this, newX, newY);
            return true;
        }
    }
    return false;
}

void Antelope::createChild(const int x, const int y) {
    world->addOrganism(new Antelope(world, x, y, 0));
}
