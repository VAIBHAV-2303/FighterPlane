#include "main.h"

#ifndef CAN_H
#define CAn_H


class Can {
public:
    Can() {}
    Can(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int used;
private:
    VAO *object;
};

#endif // CAN_H
