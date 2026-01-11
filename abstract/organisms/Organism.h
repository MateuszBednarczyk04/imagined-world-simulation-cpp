//
// Created by Mateusz Bednarczyk on 02/01/2026.
//

#ifndef UNTITLED_ORGANISM_H
#define UNTITLED_ORGANISM_H
#include <string>
#include <iostream>

using namespace std;

class World;

class Organism {
protected:
    int strength;
    string asciiRepresentation;
    int x;
    int y;
    int initiative;
    int age;
    World *world;

public:
    virtual ~Organism() = default;

    Organism(World *world, const int strength, const string &asciiRepresentation, const int x, const int y,
             const int initiative,
             const int age) {
        this->world = world;
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

    virtual void solveCollision(Organism *other) = 0;

    virtual void createChild(int x, int y) = 0;

    virtual bool didReflectAttack(Organism *attacker) {
        return false;
    }

    int getX() const {
        return this->x;
    }

    int getY() const {
        return this->y;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

    int getInitiative() const {
        return this->initiative;
    }

    int getStrength() const {
        return this->strength;
    }

    void addStrength(const int amount) {
        this->strength += amount;
    }

    int getAge() const {
        return this->age;
    }

    void incrementAge() {
        this->age++;
    }
};

#endif //UNTITLED_ORGANISM_H
