#include "bg.h"
#include "main.h"

Bg::Bg(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    static const GLfloat ground_vertex_buffer_data[] = {
        50000.0, -2000.0, -50000.0,
        -50000.0, -2000.0, -50000.0,
        50000.0, -2000.0, 50000.0,
        50000.0, -2000.0, 50000.0,
        -50000.0, -2000.0, -50000.0,
        -50000.0, -2000.0, 50000.0
    };
    this->ground = create3DObject(GL_TRIANGLES, 2*3, ground_vertex_buffer_data, COLOR_OCEAN, GL_FILL);
}

void Bg::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ground);
}