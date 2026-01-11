//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "organisms/animals/Human.h"
#include <sstream>
#include "World.h"

using namespace std;

void Human::action() {
    const PlayerMove move = world->getPlayerMove();
    int dx = 0, dy = 0;

    switch (move) {
        case PlayerMove::UP: dy = -1;
            break;
        case PlayerMove::DOWN: dy = 1;
            break;
        case PlayerMove::LEFT: dx = -1;
            break;
        case PlayerMove::RIGHT: dx = 1;
            break;
        case PlayerMove::ABILITY:
            activateAbility();
            return;
        case PlayerMove::NONE:
        default:
            return;
    }

    const int newX = x + dx;
    const int newY = y + dy;

    if (newX >= 0 && newX < world->getWidth() && newY >= 0 && newY < world->getHeight()) {
        if (Organism *other = world->getOrganismOnPosition(newX, newY); other != nullptr && other != this) {
            solveCollision(other);
        } else {
            world->moveOrganism(this, newX, newY);
        }
    }
}

void Human::solveCollision(Organism *other) {
    if (abilityDuration > 0 && other->getStrength() > this->getStrength()) {
        if (int newX, newY; world->findFreeAdjacentSpot(this->getX(), this->getY(), newX, newY)) {
            world->moveOrganism(this, newX, newY);
        }
        return;
    }
    Animal::solveCollision(other);
}

bool Human::didReflectAttack(Organism *attacker) {
    if (abilityDuration > 0 && attacker->getStrength() > this->getStrength()) {
        if (int newX, newY; world->findFreeAdjacentSpot(this->getX(), this->getY(), newX, newY)) {
            world->moveOrganism(this, newX, newY);
        }
        return true;
    }
    return false;
}

void Human::createChild(int x, int y) {
    // Human does not reproduce
}

void Human::activateAbility() {
    if (abilityCooldown == 0) {
        abilityDuration = 5;
        abilityCooldown = 10; // 5 turns duration + 5 turns cooldown
    }
}

string Human::getAbilityStatus() const {
    stringstream ss;
    ss << "Ability (Immortality): ";
    if (abilityDuration > 0) {
        ss << "ACTIVE for " << abilityDuration << " more turns.";
    } else if (abilityCooldown > 0) {
        ss << "on COOLDOWN for " << abilityCooldown << " more turns.";
    } else {
        ss << "READY (Press 'p')";
    }
    return ss.str();
}

void Human::advanceTurn() {
    if (abilityDuration > 0) {
        abilityDuration--;
    }
    if (abilityCooldown > 0) {
        abilityCooldown--;
    }
}
