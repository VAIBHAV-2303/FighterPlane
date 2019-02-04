#include "main.h"

#ifndef FUEL_H
#define FUEL_H


class Fuel {
public:
    Fuel() {}
    Fuel(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, float h, glm::vec3 eye, glm::vec3 target, glm::vec3 up, int camView, float zrotation);
    void set_position(float x, float y, float z);
private:
    VAO *object;
    VAO *ring;
};

#endif // FUEL_H
