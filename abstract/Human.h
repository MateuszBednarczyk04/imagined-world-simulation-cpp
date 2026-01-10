//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#ifndef UNTITLED_HUMAN_H
#define UNTITLED_HUMAN_H

#include "Animal.h"
#include <string>

class Human : public Animal {
private:
    int abilityCooldown;
    int abilityDuration;

public:
    Human(World* world, int x, int y)
        : Animal(world, 5, "@", x, y, 4, 0), abilityCooldown(0), abilityDuration(0) {
    }

    void action() override;
    void solveCollision(Organism *other) override;
    bool didReflectAttack(Organism *attacker) override;
    void createChild(int x, int y) override;

    void activateAbility();
    std::string getAbilityStatus() const;
    void advanceTurn();
};

#endif //UNTITLED_HUMAN_H
