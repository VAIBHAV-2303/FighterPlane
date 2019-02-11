#include "main.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z, int rotn);
    glm::vec3 position;
    float rotation;
    float speedy;
    int burst;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
    VAO *rope;
    VAO *human;
};

#endif // PARACHUTE_H