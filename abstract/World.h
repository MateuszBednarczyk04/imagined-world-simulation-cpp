//
// Created by Mateusz Bednarczyk on 01/01/2026.
//

#ifndef UNTITLED_WORLD_H
#define UNTITLED_WORLD_H

class World {
    int width, height;

public:
    World(int const width, int const height) {
        this->width = width;
        this->height = height;
    }

    virtual ~World() = default;

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    void draw();
};

#endif //UNTITLED_WORLD_H
