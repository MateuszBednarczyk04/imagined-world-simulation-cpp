//
// Created by Mateusz Bednarczyk on 02/01/2026.
//

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include "../abstract/World.h"
#include "organisms/animals/Human.h"
#include "organisms/animals/Wolf.h"
#include "organisms/animals/Sheep.h"
#include "organisms/animals/Fox.h"
#include "organisms/animals/Turtle.h"
#include "organisms/animals/Antelope.h"
#include "organisms/animals/CyberSheep.h"
#include "organisms/plants/Grass.h"
#include "organisms/plants/Dandelion.h"
#include "organisms/plants/Guarana.h"
#include "organisms/plants/Belladonna.h"
#include "organisms/plants/SosnowskyHogweed.h"

using namespace std;

const array<pair<int, int>, 4> World::CARDINAL_DIRECTIONS = {{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}};
const array<pair<int, int>, 8> World::ALL_DIRECTIONS = {
    {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}
};

void World::render() const {
    int maxLogs = height;
    int startLogIndex = 0;
    if (logs.size() > maxLogs) {
        startLogIndex = logs.size() - maxLogs;
    }

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
        printf("|");

        if (startLogIndex + y < logs.size()) {
            printf(" %s", logs[startLogIndex + y].c_str());
        }
        printf("\n");
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

void World::saveGame(const string &filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for saving." << endl;
        return;
    }

    file << width << " " << height << endl;
    file << organisms.size() << endl;

    for (const auto *org: organisms) {
        file << org->getType() << " "
                << org->getX() << " "
                << org->getY() << " "
                << org->getStrength() << " "
                << org->getAge() << endl;
    }

    file.close();
    cout << "Game saved to " << filename << endl;
}

void World::clearWorld() {
    for (auto *org: organisms) {
        delete org;
    }
    organisms.clear();
    for (auto &row: grid) {
        fill(row.begin(), row.end(), nullptr);
    }
    clearLogs();
}

void World::loadGame(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for loading." << endl;
        return;
    }

    clearWorld();

    int newWidth, newHeight, organismCount;
    file >> newWidth >> newHeight;
    file >> organismCount;

    this->width = newWidth;
    this->height = newHeight;
    grid.assign(height, vector<Organism *>(width, nullptr));

    string type;
    int x, y, strength, age;

    for (int i = 0; i < organismCount; ++i) {
        file >> type >> x >> y >> strength >> age;
        Organism *newOrg = nullptr;

        if (type == "Human") newOrg = new Human(this, x, y);
        else if (type == "Wolf") newOrg = new Wolf(this, x, y, age);
        else if (type == "Sheep") newOrg = new Sheep(this, x, y, age);
        else if (type == "Fox") newOrg = new Fox(this, x, y, age);
        else if (type == "Turtle") newOrg = new Turtle(this, x, y, age);
        else if (type == "Antelope") newOrg = new Antelope(this, x, y, age);
        else if (type == "CyberSheep") newOrg = new CyberSheep(this, x, y, age);
        else if (type == "Grass") newOrg = new Grass(this, x, y, age);
        else if (type == "Dandelion") newOrg = new Dandelion(this, x, y, age);
        else if (type == "Guarana") newOrg = new Guarana(this, x, y, age);
        else if (type == "Belladonna") newOrg = new Belladonna(this, x, y, age);
        else if (type == "SosnowskyHogweed") newOrg = new SosnowskyHogweed(this, x, y, age);

        if (newOrg) {
            addOrganism(newOrg);
            int currentStrength = newOrg->getStrength();
            newOrg->addStrength(strength - currentStrength);
        }
    }

    file.close();
    cout << "Game loaded from " << filename << endl;
}
