#include "can.h"
#include "main.h"

Can::Can(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->used=0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -20.0f,-20.0f,-20.0f, // triangle 1 : begin
        -20.0f,-20.0f, 20.0f,
        -20.0f, 20.0f, 20.0f, // triangle 1 : end
        20.0f, 20.0f,-20.0f, // triangle 2 : begin
        -20.0f,-20.0f,-20.0f,
        -20.0f, 20.0f,-20.0f, // triangle 2 : end
        20.0f,-20.0f, 20.0f,
        -20.0f,-20.0f,-20.0f,
        20.0f,-20.0f,-20.0f,
        20.0f, 20.0f,-20.0f,
        20.0f,-20.0f,-20.0f,
        -20.0f,-20.0f,-20.0f,
        -20.0f,-20.0f,-20.0f,
        -20.0f, 20.0f, 20.0f,
        -20.0f, 20.0f,-20.0f,
        20.0f,-20.0f, 20.0f,
        -20.0f,-20.0f, 20.0f,
        -20.0f,-20.0f,-20.0f,
        -20.0f, 20.0f, 20.0f,
        -20.0f,-20.0f, 20.0f,
        20.0f,-20.0f, 20.0f,
        20.0f, 20.0f, 20.0f,
        20.0f,-20.0f,-20.0f,
        20.0f, 20.0f,-20.0f,
        20.0f,-20.0f,-20.0f,
        20.0f, 20.0f, 20.0f,
        20.0f,-20.0f, 20.0f,
        20.0f, 20.0f, 20.0f,
        20.0f, 20.0f,-20.0f,
        -20.0f, 20.0f,-20.0f,
        20.0f, 20.0f, 20.0f,
        -20.0f, 20.0f,-20.0f,
        -20.0f, 20.0f, 20.0f,
        20.0f, 20.0f, 20.0f,
        -20.0f, 20.0f, 20.0f,
        20.0f,-20.0f, 20.0f
    };

    static const GLfloat colour_buffer_data[] = {
        -50.0f,-50.0f,-50.0f, // triangle 1 : begin
        -50.0f,-50.0f, 50.0f,
        -50.0f, 50.0f, 50.0f, // triangle 1 : end
        50.0f, 50.0f,-50.0f, // triangle 2 : begin
        -50.0f,-50.0f,-50.0f,
        -50.0f, 50.0f,-50.0f, // triangle 2 : end
        50.0f,-50.0f, 50.0f,
        -50.0f,-50.0f,-50.0f,
        50.0f,-50.0f,-50.0f,
        50.0f, 50.0f,-50.0f,
        50.0f,-50.0f,-50.0f,
        -50.0f,-50.0f,-50.0f,
        -50.0f,-50.0f,-50.0f,
        -50.0f, 50.0f, 50.0f,
        -50.0f, 50.0f,-50.0f,
        50.0f,-50.0f, 50.0f,
        -50.0f,-50.0f, 50.0f,
        -50.0f,-50.0f,-50.0f,
        -50.0f, 50.0f, 50.0f,
        -50.0f,-50.0f, 50.0f,
        50.0f,-50.0f, 50.0f,
        50.0f, 50.0f, 50.0f,
        50.0f,-50.0f,-50.0f,
        50.0f, 50.0f,-50.0f,
        50.0f,-50.0f,-50.0f,
        50.0f, 50.0f, 50.0f,
        50.0f,-50.0f, 50.0f,
        50.0f, 50.0f, 50.0f,
        50.0f, 50.0f,-50.0f,
        -50.0f, 50.0f,-50.0f,
        50.0f, 50.0f, 50.0f,
        -50.0f, 50.0f,-50.0f,
        -50.0f, 50.0f, 50.0f,
        50.0f, 50.0f, 50.0f,
        -50.0f, 50.0f, 50.0f,
        50.0f,-50.0f, 50.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, colour_buffer_data, GL_FILL);
}

void Can::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Can::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Can::tick() {
    this->rotation ++;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

