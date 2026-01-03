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
    int x;
    int y;
    int initiative;
    int age;

public:
    virtual ~Organism() = default;

    Organism(const int strength, const string &asciiRepresentation, const int x, const int y, const int initiative,
             const int age) {
        this->strength = strength;
        this->asciiRepresentation = asciiRepresentation;
        this->x = x;
        this->y = y;
        this->initiative = initiative;
        this->age = age;
    }

    void draw() const {
        printf("%s", asciiRepresentation.c_str());
    }

    virtual void action() = 0;

    virtual void solveCollision(const Organism *other) = 0;

    int getX() const {
        return this->x;
    }

    int getY() const {
        return this->y;
    }

    int getInitiative() const {
        return this->initiative;
    }

    int getAge() const {
        return this->age;
    }
};

#endif //UNTITLED_ORGANISM_H
