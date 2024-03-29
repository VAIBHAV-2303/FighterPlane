#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z, int rotn);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    int used;
private:
    VAO *object;
};

#endif // RING_H