#include "main.h"

#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y);
    glm::vec3 position;
    float xrotation, yrotation, zrotation, fuel;
    void accelerate();
    void decelerate();
    void turn_left();
    void turn_right();
    void draw(glm::mat4 VP);
    void tick();
    void move_up();
    void tilt_left();
    void tilt_right();
    double speedxz, speedy;
    int hover;
private:
    VAO *object;
};

#endif // PLANE_H
