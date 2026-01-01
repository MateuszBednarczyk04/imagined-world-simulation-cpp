//
// Created by Mateusz Bednarczyk on 02/01/2026.
//

#ifndef UNTITLED_ORGANISM_H
#define UNTITLED_ORGANISM_H
#include <string>
#include <iostream>

using namespace std;

class Organism {
    int strength;
    string asciiRepresentation;

public:
    Organism(const int strength, const string &asciiRepresentation) {
        this->strength = strength;
        this->asciiRepresentation = asciiRepresentation;
    }

    void draw() const {
        printf("%s", asciiRepresentation.c_str());
    }
};

#endif //UNTITLED_ORGANISM_H
