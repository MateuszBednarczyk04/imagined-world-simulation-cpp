#include <iostream>

#include "World.h"
#include "organisms/plants/Grass.h"
#include "organisms/plants/Dandelion.h"
#include "organisms/plants/Guarana.h"
#include "organisms/plants/Belladonna.h"
#include "organisms/plants/SosnowskyHogweed.h"

#include "organisms/animals/Wolf.h"
#include "organisms/animals/Sheep.h"
#include "organisms/animals/Fox.h"
#include "organisms/animals/Turtle.h"
#include "organisms/animals/Antelope.h"
#include "organisms/animals/CyberSheep.h"
#include "organisms/animals/Human.h"


using namespace std;

char get_char() {
    char ch;
    cin >> ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return ch;
}

void initializeWorld(World *world, Human *player) {
    world->addOrganism(player);

    for (int i = 0; i < 10; ++i) {
        world->addOrganismRandomly(new CyberSheep(world, 0, 0));
        world->addOrganismRandomly(new CyberSheep(world, 0, 0));
        world->addOrganismRandomly(new SosnowskyHogweed(world, 0, 0));
        world->addOrganismRandomly(new SosnowskyHogweed(world, 0, 0));
        world->addOrganismRandomly(new Wolf(world, 0, 0));
        world->addOrganismRandomly(new Sheep(world, 0, 0));
        world->addOrganismRandomly(new Fox(world, 0, 0));
        world->addOrganismRandomly(new Turtle(world, 0, 0));
        world->addOrganismRandomly(new Antelope(world, 0, 0));
        world->addOrganismRandomly(new Grass(world, 0, 0));
        world->addOrganismRandomly(new Dandelion(world, 0, 0));
        world->addOrganismRandomly(new Guarana(world, 0, 0));
        world->addOrganismRandomly(new Belladonna(world, 0, 0));
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
        printf("Mateusz Bednarczyk, sXXXXXX\n");
        world.render();
        printf("Player alive: %s | ", world.isOrganismAlive(player) ? "true" : "false");
        printf("Player Strength: %d | Turn: %d\n", player->getStrength(), round);
        printf("%s\n", player->getAbilityStatus().c_str());
        printf("Move (w/a/s/d), activate ability (p), or quit (q): ");

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
