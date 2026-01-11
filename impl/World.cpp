//
// Created by Mateusz Bednarczyk on 02/01/2026.
//

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "../abstract/World.h"
#include "organisms/animals/Human.h"

using namespace std;

const array<pair<int, int>, 4> World::CARDINAL_DIRECTIONS = {{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}};
const array<pair<int, int>, 8> World::ALL_DIRECTIONS = {
    {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}
};

void World::render() const {
    for (int i = 0; i < this->width + 2; i++) printf("-");
    printf("\n");

    for (int y = 0; y < this->height; y++) {
        printf("|");
        for (int x = 0; x < this->width; x++) {
            auto organism = this->getOrganismOnPosition(x, y);
            if (organism != nullptr) {
                organism->draw();
            } else {
                printf(" ");
            }
        }
        printf("|\n");
    }

    for (int i = 0; i < this->width + 2; i++) printf("-");
    printf("\n");
}

void World::executeRound() {
    this->sortOrganisms();

    vector<Organism *> organismsSnapshot = organisms;

    for (Organism *org: organismsSnapshot) {
        if (isOrganismAlive(org)) {
            org->action();
        }
    }

    for (auto org: organisms) {
        if (auto human = dynamic_cast<Human *>(org)) {
            human->advanceTurn();
            break;
        }
    }

    for (Organism *org: organisms) {
        org->incrementAge();
    }
}

bool World::findFreeAdjacentSpot(int x, int y, int &outX, int &outY) const {
    auto directions = World::ALL_DIRECTIONS;

    random_device rd;
    mt19937 g(rd());
    shuffle(directions.begin(), directions.end(), g);

    for (const auto &dir: directions) {
        const int newX = x + dir.first;
        const int newY = y + dir.second;

        if (newX >= 0 && newX < width && newY >= 0 && newY < height && getOrganismOnPosition(newX, newY) == nullptr) {
            outX = newX;
            outY = newY;
            return true;
        }
    }
    return false;
}

bool World::isOrganismAlive(const Organism *organism) const {
    for (const auto o: organisms) {
        if (o == organism) {
            return true;
        }
    }
    return false;
}
