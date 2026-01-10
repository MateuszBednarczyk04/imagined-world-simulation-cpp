//
// Created by Mateusz Bednarczyk on 02/01/2026.
//

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "../abstract/World.h"
#include "../abstract/Human.h"

using namespace std;

void World::render() {
    for (int i = 0; i < this->width + 2; i++) std::cout << "-";
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

    for (int i = 0; i < this->width + 2; i++) std::cout << "-";
    printf("\n");
}

void World::executeRound() {
    this->sortOrganisms();
    for (int i = 0; i < organisms.size(); i++) {
        if (i < organisms.size() && organisms[i] != nullptr) {
            organisms[i]->action();
        }
    }

    // After all actions, advance human's turn for cooldowns
    for (auto org : organisms) {
        if (auto human = dynamic_cast<Human*>(org)) {
            human->advanceTurn();
            break; // There is only one human
        }
    }
}

bool World::findFreeAdjacentSpot(int x, int y, int& outX, int& outY) const {
    vector<pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    random_device rd;
    mt19937 g(rd());
    shuffle(directions.begin(), directions.end(), g);

    for (const auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;

        if (newX >= 0 && newX < width && newY >= 0 && newY < height && getOrganismOnPosition(newX, newY) == nullptr) {
            outX = newX;
            outY = newY;
            return true;
        }
    }
    return false; // No free spot found
}

bool World::isOrganismAlive(Organism* organism) const {
    for (const auto o : organisms) {
        if (o == organism) {
            return true;
        }
    }
    return false;
}
