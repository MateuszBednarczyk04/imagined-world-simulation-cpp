#ifndef UNTITLED_PLANT_H
#define UNTITLED_PLANT_H

#include "../Organism.h"

class Organism; // Forward declaration

class Plant : public Organism {
protected:
    static constexpr double SPREAD_PROBABILITY = 0.05;

public:
    using Organism::Organism;

    void action() override;

    void solveCollision(Organism *attacker) override;
};

#endif //UNTITLED_PLANT_H
