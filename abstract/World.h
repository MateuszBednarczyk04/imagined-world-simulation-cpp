//
// Created by Mateusz Bednarczyk on 01/01/2026.
//

#ifndef UNTITLED_WORLD_H
#define UNTITLED_WORLD_H

#include <vector>
#include <algorithm>
#include <random>
#include <array>
#include <utility>
#include "organisms/Organism.h"

using namespace std;

enum class PlayerMove { NONE, UP, DOWN, LEFT, RIGHT, ABILITY };

class World {
    int width, height;
    vector<Organism *> organisms;
    vector<vector<Organism *> > grid; // Optimization: Grid for O(1) access
    PlayerMove playerMove;

public:
    // --- NEW, IMPROVED STATIC CONSTANTS using std::array ---
    static const std::array<std::pair<int, int>, 4> CARDINAL_DIRECTIONS;
    static const std::array<std::pair<int, int>, 8> ALL_DIRECTIONS;

    World(int const width, int const height) {
        this->width = width;
        this->height = height;
        this->organisms = {};
        this->playerMove = PlayerMove::NONE;
        // Initialize grid
        grid.resize(height, vector<Organism *>(width, nullptr));
    }

    virtual ~World() = default;

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    const vector<Organism *> &getOrganisms() const {
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

    void render() const;

    void executeRound();

    void sortOrganisms() {
        sort(organisms.begin(), organisms.end(), [](Organism *a, Organism *b) {
            if (a->getInitiative() != b->getInitiative()) {
                return a->getInitiative() > b->getInitiative();
            }
            return a->getAge() > b->getAge();
        });
    }

    // O(1) implementation
    Organism *getOrganismOnPosition(const int x, const int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return nullptr;
        }
        return grid[y][x];
    }

    bool isCollision(const int x, const int y) const {
        return getOrganismOnPosition(x, y) != nullptr;
    }

    bool findFreeAdjacentSpot(int x, int y, int &outX, int &outY) const;

    bool isOrganismAlive(const Organism *organism) const;

    void addOrganism(Organism *organism) {
        this->organisms.push_back(organism);
        grid[organism->getY()][organism->getX()] = organism;
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
        if (organism == nullptr) return;
        grid[organism->getY()][organism->getX()] = nullptr;
        auto it = std::remove(this->organisms.begin(), this->organisms.end(), organism);
        this->organisms.erase(it, this->organisms.end());
    }

    void moveOrganism(Organism *organism, int newX, int newY) {
        grid[organism->getY()][organism->getX()] = nullptr;
        grid[newY][newX] = organism;
        organism->setX(newX);
        organism->setY(newY);
    }
};

#endif //UNTITLED_WORLD_H
