#include "main.h"

#ifndef SPEEDO_H
#define SPEEDO_H


class Speedo {
public:
    Speedo() {}
    Speedo(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, float curSpeed, glm::vec3 eye, glm::vec3 target, glm::vec3 up, int camView, float zrotation);
    void set_position(float x, float y, float z);
private:
    VAO *object;
    VAO* ring;
};

#endif // SPEEDO_H
