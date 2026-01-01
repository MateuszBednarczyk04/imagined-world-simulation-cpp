#include <iostream>

#include "abstract/World.h"

using namespace std;

int main() {
    auto world = World(40, 10);
    world.draw();
    return 0;
}
