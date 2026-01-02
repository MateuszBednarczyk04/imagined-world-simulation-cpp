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
            printf(" ");
        }
        printf("|\n");
    }

    for (int i = 0; i < this->width + 2; i++) std::cout << "-";
    printf("\n");
}
