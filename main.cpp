#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdio>

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

void setRawMode(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

void initializeWorld(World *world, Human *player) {
    world->addOrganism(player);

    int initialOrganismCount = (world->getWidth() * world->getHeight()) / 5;
    if (initialOrganismCount < 10) initialOrganismCount = 10;

    for (int i = 0; i < initialOrganismCount; ++i) {
        int type = rand() % 13;
        switch (type) {
            case 0: world->addOrganismRandomly(new CyberSheep(world, 0, 0));
                break;
            case 1: world->addOrganismRandomly(new SosnowskyHogweed(world, 0, 0));
                break;
            case 2: world->addOrganismRandomly(new Wolf(world, 0, 0));
                break;
            case 3: world->addOrganismRandomly(new Sheep(world, 0, 0));
                break;
            case 4: world->addOrganismRandomly(new Fox(world, 0, 0));
                break;
            case 5: world->addOrganismRandomly(new Turtle(world, 0, 0));
                break;
            case 6: world->addOrganismRandomly(new Antelope(world, 0, 0));
                break;
            case 7: world->addOrganismRandomly(new Grass(world, 0, 0));
                break;
            case 8: world->addOrganismRandomly(new Dandelion(world, 0, 0));
                break;
            case 9: world->addOrganismRandomly(new Guarana(world, 0, 0));
                break;
            case 10: world->addOrganismRandomly(new Belladonna(world, 0, 0));
                break;
            default: break;
        }
    }
}

int main() {
    srand(time(nullptr));
    int width, height;
    cout << "Enter world width: ";
    cin >> width;
    cout << "Enter world height: ";
    cin >> height;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto world = World(width, height);
    int round = 0;

    auto player = new Human(&world, 0, 0);
    initializeWorld(&world, player);

    setRawMode(true);

    while (true) {
        printf("\033[2J\033[H");
        printf("Mateusz Bednarczyk, sXXXXXX\n");
        world.render();
        printf("Player alive: %s | ", world.isOrganismAlive(player) ? "true" : "false");
        printf("Player Strength: %d | Turn: %d\n", player->getStrength(), round);
        printf("%s\n", player->getAbilityStatus().c_str());
        printf("Move (Arrows), activate ability (p), next round (n), save (k), load (l) or quit (q): ");

        int c = getchar();
        auto move = PlayerMove::NONE;

        if (c == 27) {
            if (getchar() == 91) {
                // [
                switch (getchar()) {
                    case 65: move = PlayerMove::UP;
                        break;
                    case 66: move = PlayerMove::DOWN;
                        break;
                    case 68: move = PlayerMove::LEFT;
                        break;
                    case 67: move = PlayerMove::RIGHT;
                        break;
                }
            }
        } else {
            switch (c) {
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
                case 'n': move = PlayerMove::NEXT_ROUND;
                    break;
                case 'k':
                    setRawMode(false);
                    world.saveGame("savegame.txt");
                    setRawMode(true);
                    continue;
                case 'l':
                    setRawMode(false);
                    world.loadGame("savegame.txt");
                    setRawMode(true);
                    player = nullptr;
                    for (auto org: world.getOrganisms()) {
                        if (dynamic_cast<Human *>(org)) {
                            player = dynamic_cast<Human *>(org);
                            break;
                        }
                    }
                    continue;
                case 'q':
                    setRawMode(false);
                    return 0;
                default: break;
            }
        }

        world.setPlayerMove(move);
        world.executeRound();
        round++;
    }
}
