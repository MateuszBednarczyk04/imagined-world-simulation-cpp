#include <iostream>

#include "abstract/World.h"

using namespace std;

int main() {
    auto world = World(40, 10);
    int i = 0;
    while (true) {
        printf("Round %d\n", i);
        world.draw();

        printf("Enter for next game round.");
        cin.get(); // waits until user press enter
        printf("\033[2J\033[H");
        i++;
    }
    return 0;
}
