#include "main.h"

#ifndef BG_H
#define BG_H


class Bg {
public:
    Bg() {}
    Bg(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
private:
    VAO *ground;
};

#endif // BG_H
