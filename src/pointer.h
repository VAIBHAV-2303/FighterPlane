#include "main.h"

#ifndef POINTER_H
#define POINTER_H


class Pointer {
public:
    Pointer() {}
    Pointer(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, glm::vec3 eye, glm::vec3 target, glm::vec3 up, int camView, float zrotation);
    void tick();
    void set_position(float x, float y, float z);
private:
    VAO *object;
};

#endif // POINTER_H