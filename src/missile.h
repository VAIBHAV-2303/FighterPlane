#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z, float speed, glm::vec3 dirn);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void tick();
    float speed;
    int burst;
    glm::vec3 dirn;
    float time;
private:
    VAO *object;
    VAO *tip;
};

#endif // MISSILE_H
