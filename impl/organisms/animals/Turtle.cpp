//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "organisms/animals/Turtle.h"

#include "../../../abstract/World.h"
#include "organisms/animals/Animal.h"

void Turtle::action() {
    if ((rand() % 4) < 3) {
        return;
    }
    Animal::action();
}

bool Turtle::didReflectAttack(Organism *attacker) {
    if (attacker->getStrength() < 5) {
        return true;
    }
    return false;
}

void Turtle::createChild(const int x, const int y) {
    world->addOrganism(new Turtle(world, x, y, 0));
}
