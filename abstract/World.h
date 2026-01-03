//
// Created by Mateusz Bednarczyk on 01/01/2026.
//

#ifndef UNTITLED_WORLD_H
#define UNTITLED_WORLD_H
#include "Organism.h"
#include "algorithm"

using namespace std;

class World {
    int width, height;
    vector<Organism *> organisms;

public:
    World(int const width, int const height) {
        this->width = width;
        this->height = height;

        this->organisms = {};
    }

    virtual ~World() = default;

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    void draw();

    void action();

    void sortOrganisms() {
        sort(organisms.begin(), organisms.end(), [](Organism *a, Organism *b) {
            if (a->getInitiative() != b->getInitiative()) {
                return a->getInitiative() > b->getInitiative();
            }
            return a->getAge() > b->getAge();
        });
    }

    bool isCollision(const int x, const int y) const {
        return this->getOrganismOnPosition(x, y) != nullptr;
    }

    Organism *getOrganismOnPosition(const int x, const int y) const {
        for (const auto organism: this->organisms) {
            if (organism->getX() == x && organism->getY() == y) {
                return organism;
            }
        }
        return nullptr;
    }

    void addOrganism(Organism *organism) {
        this->organisms.push_back(organism);
    }
};

#endif //UNTITLED_WORLD_H
