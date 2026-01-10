#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <limits>

#include "abstract/World.h"
#include "abstract/Grass.h"
#include "abstract/Dandelion.h"
#include "abstract/Guarana.h"
#include "abstract/Belladonna.h"
#include "abstract/SosnowskyHogweed.h"

#include "abstract/Wolf.h"
#include "abstract/Sheep.h"
#include "abstract/Fox.h"
#include "abstract/Turtle.h"
#include "abstract/Antelope.h"
#include "abstract/CyberSheep.h"
#include "abstract/Human.h"


using namespace std;

char get_char() {
    char ch;
    cin >> ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return ch;
}

void initializeWorld(World *world, Human *player) {
    world->addOrganismRandomly(player);
    world->addOrganismRandomly(new CyberSheep(world, 0, 0));

    for (int i = 0; i < 10; ++i) {
        world->addOrganismRandomly(new Wolf(world, 0, 0));
        world->addOrganismRandomly(new Sheep(world, 0, 0));
        world->addOrganismRandomly(new Fox(world, 0, 0));
        world->addOrganismRandomly(new Turtle(world, 0, 0));
        world->addOrganismRandomly(new Antelope(world, 0, 0));
        world->addOrganismRandomly(new Grass(world, 0, 0));
        world->addOrganismRandomly(new Dandelion(world, 0, 0));
        world->addOrganismRandomly(new Guarana(world, 0, 0));
        world->addOrganismRandomly(new Belladonna(world, 0, 0));
        world->addOrganismRandomly(new SosnowskyHogweed(world, 0, 0));
    }
}


int main() {
    srand(time(nullptr));
    auto world = World(60, 40);
    int round = 0;

    auto player = new Human(&world, 0, 0);
    initializeWorld(&world, player);

    while (true) {
        printf("\033[2J\033[H"); // Clear screen
        cout << "Mateusz Bednarczyk, sXXXXXX" << endl;
        world.render();
        cout << "Player Strength: " << player->getStrength() << " | Turn: " << round << endl;
        cout << player->getAbilityStatus() << endl;
        cout << "Move (w/a/s/d), activate ability (p), or quit (q): ";

        const char input = get_char();
        auto move = PlayerMove::NONE;

        switch (input) {
            case 'w': move = PlayerMove::UP;
                break;
            case 's': move = PlayerMove::DOWN;
                break;
            case 'a': move = PlayerMove::LEFT;
                break;
            case 'd': move = PlayerMove::RIGHT;
                break;
            case 'p': move = PlayerMove::ABILITY;
                break;
            case 'q': return 0;
            default: break;
        }

        world.setPlayerMove(move);
        world.executeRound();
        round++;
    }
}
