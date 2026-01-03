//
// Created by Mateusz Bednarczyk on 02/01/2026.
//

#include <iostream>
#include "../abstract/World.h"

using namespace std;

void World::draw() {
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

void World::action() {
    this->sortOrganisms();
    for (const auto organism: this->organisms) {
        organism->action();
        if (this->isCollision(organism->getX(), organism->getY())) {
            organism->solveCollision(this->getOrganismOnPosition(organism->getX(), organism->getY()));
        }
    }
}
