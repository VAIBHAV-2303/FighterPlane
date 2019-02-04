#include "main.h"

#ifndef BOMB_H
#define BOMB_H


class Bomb {
public:
    Bomb() {}
    Bomb(float x, float y, float z, float yrotation, float speed);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
    float speedxz, speedy;
    int burst;
    glm::vec3 dirn;
    float time;
private:
    VAO *object;
    VAO *tip;
};

#endif // BOMB_H
