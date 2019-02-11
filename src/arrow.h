#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP, glm::vec3 eye, glm::vec3 target, glm::vec3 up, int camView, float zrotation, glm::vec3 dirn);
    void set_position(float x, float y, float z);
private:
    VAO *object;
};

#endif // ARROW_H
