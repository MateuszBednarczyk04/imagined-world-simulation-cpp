//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "../abstract/Turtle.h"
#include "../abstract/World.h"

void Turtle::action() {
    // Lazy: In 75% of cases, it does not change position.
    if ((rand() % 4) < 3) { // 75% chance (0, 1, 2 out of 0,1,2,3)
        return; // Do nothing
    }
    // If it moves (25% chance), it's a standard animal move.
    Animal::action();
}

bool Turtle::didReflectAttack(Organism *attacker) {
    // Shell: Repels attacks from animals with Strength < 5.
    if (attacker->getStrength() < 5) {
        // Attack is repelled. Attacker must return to previous tile.
        // The logic for returning to the previous tile needs to be handled by the attacker's flow.
        // By returning true, we signal that the attack was deflected. The Animal::solveCollision will stop the attack.
        return true;
    }
    // If attacker strength is >= 5, the attack is not repelled.
    return false;
}

void Turtle::createChild(int x, int y) {
    Turtle* child = new Turtle(world, x, y, 0);
    world->addOrganism(child);
}
