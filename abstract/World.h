//
// Created by Mateusz Bednarczyk on 01/01/2026.
//

#ifndef UNTITLED_WORLD_H
#define UNTITLED_WORLD_H

#include <vector>
#include <algorithm>
#include <random>
#include "Organism.h"

using namespace std;

enum class PlayerMove { NONE, UP, DOWN, LEFT, RIGHT, ABILITY };

class World {
    int width, height;
    vector<Organism *> organisms;
    PlayerMove playerMove;

public:
    World(int const width, int const height) {
        this->width = width;
        this->height = height;
        this->organisms = {};
        this->playerMove = PlayerMove::NONE;
    }

    virtual ~World() = default;

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    const vector<Organism *>& getOrganisms() const {
        return organisms;
    }

    void setPlayerMove(PlayerMove move) {
        this->playerMove = move;
    }

    PlayerMove getPlayerMove() {
        PlayerMove move = this->playerMove;
        this->playerMove = PlayerMove::NONE; // Reset after getting the move
        return move;
    }

    void render();

    void executeRound();

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

    bool findFreeAdjacentSpot(int x, int y, int& outX, int& outY) const;

    bool isOrganismAlive(Organism* organism) const;

    void addOrganism(Organism *organism) {
        this->organisms.push_back(organism);
    }

    void addOrganismRandomly(Organism *organism) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distribX(0, this->width - 1);
        uniform_int_distribution<> distribY(0, this->height - 1);

        int x, y;
        do {
            x = distribX(gen);
            y = distribY(gen);
        } while (isCollision(x, y));

        organism->setX(x);
        organism->setY(y);
        this->addOrganism(organism);
    }

    void deleteOrganism(Organism *organism) {
        auto it = std::remove(this->organisms.begin(), this->organisms.end(), organism);
        this->organisms.erase(it, this->organisms.end());
    }
};

#endif //UNTITLED_WORLD_H
