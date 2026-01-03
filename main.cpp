#include <iostream>

#include "abstract/Plant.h"
#include "abstract/World.h"

using namespace std;

int main() {
    auto world = World(40, 10);
    int i = 0;
    auto mockOrganism = Plant(1, "P", 2, 2, 2, 2);
    world.addOrganism(&mockOrganism);
    while (true) {
        printf("Round %d\n", i);
        // world.action();

        world.draw();

        printf("Enter for next game round.");
        cin.get(); // waits until user press enter
        printf("\033[2J\033[H");
        i++;
    }
    return 0;
}
