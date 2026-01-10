//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "../abstract/Human.h"
#include "../abstract/World.h"
#include <sstream>

void Human::action() {
    const PlayerMove move = world->getPlayerMove();
    int dx = 0, dy = 0;

    switch (move) {
        case PlayerMove::UP:    dy = -1; break;
        case PlayerMove::DOWN:  dy = 1;  break;
        case PlayerMove::LEFT:  dx = -1; break;
        case PlayerMove::RIGHT: dx = 1;  break;
        case PlayerMove::ABILITY:
            activateAbility();
            return; // Activating ability costs a turn's move
        case PlayerMove::NONE:
        default:
            return; // No move, do nothing
    }

    int newX = x + dx;
    int newY = y + dy;

    if (newX >= 0 && newX < world->getWidth() && newY >= 0 && newY < world->getHeight()) {
        Organism* other = world->getOrganismOnPosition(newX, newY);
        if (other != nullptr && other != this) {
            solveCollision(other);
        } else {
            world->moveOrganism(this, newX, newY);
        }
    }
}

void Human::solveCollision(Organism *other) {
    // If ability is active and opponent is stronger, escape instead of fighting.
    if (abilityDuration > 0 && other->getStrength() > this->getStrength()) {
        int newX, newY;
        if (world->findFreeAdjacentSpot(this->getX(), this->getY(), newX, newY)) {
            world->moveOrganism(this, newX, newY);
        }
        return; // Attack is cancelled by escaping.
    }

    // Otherwise, standard fight/eat logic.
    Animal::solveCollision(other);
}

bool Human::didReflectAttack(Organism *attacker) {
    // If ability is active and attacker is stronger, escape.
    if (abilityDuration > 0 && attacker->getStrength() > this->getStrength()) {
        int newX, newY;
        if (world->findFreeAdjacentSpot(this->getX(), this->getY(), newX, newY)) {
            world->moveOrganism(this, newX, newY);
        }
        return true; // "Reflect" the attack by escaping.
    }
    // Otherwise, standard fight.
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

std::string Human::getAbilityStatus() const {
    std::stringstream ss;
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
