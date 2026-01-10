//
// Created by Mateusz Bednarczyk on 05/01/2026.
//

#include "../abstract/Fox.h"
#include "../abstract/World.h"
#include <vector>
#include <random>

void Fox::action() {
    // Good Smell: Fox finds all adjacent safe spots and moves to a random one.
    // A spot is "safe" if it's empty or occupied by an organism with strength <= fox's strength.

    std::vector<pair<int, int>> possibleMoves;
    int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}}; // Up, Down, Left, Right

    for (auto& dir : directions) {
        int newX = x + dir[0];
        int newY = y + dir[1];

        // Check if the new position is within the world bounds
        if (newX >= 0 && newX < world->getWidth() && newY >= 0 && newY < world->getHeight()) {
            Organism* other = world->getOrganismOnPosition(newX, newY);
            // The spot is safe if it's empty or the organism there is not stronger than the fox
            if (other == nullptr || other->getStrength() <= this->getStrength()) {
                possibleMoves.push_back({newX, newY});
            }
        }
    }

    // If there are no safe moves, the fox stays put
    if (possibleMoves.empty()) {
        return;
    }

    // Pick a random move from the safe ones
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, possibleMoves.size() - 1);
    pair<int, int> chosenMove = possibleMoves[distrib(gen)];

    int finalX = chosenMove.first;
    int finalY = chosenMove.second;

    Organism* target = world->getOrganismOnPosition(finalX, finalY);

    if (target != nullptr) {
        // If there's an organism, it must be weaker or equal, so we collide (fight/reproduce)
        solveCollision(target);
    } else {
        // If the spot is empty, just move there
        world->moveOrganism(this, finalX, finalY);
    }
}

void Fox::createChild(int x, int y) {
    Fox *child = new Fox(world, x, y, 0);
    world->addOrganism(child);
}
