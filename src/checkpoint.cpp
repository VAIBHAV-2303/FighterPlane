#include "checkpoint.h"
#include "main.h"

Checkpoint::Checkpoint(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    GLfloat vertex_buffer_data[720*9*100];
    double angle;
    for(int j=0;j<100;j++){
        for(int i=0;i<360;i++){
            angle=i*2.0*M_PI/360.0;
            vertex_buffer_data[(360*9*j)+9*i]=0.0*cos(angle);
            vertex_buffer_data[(360*9*j)+9*i+1]=(float)j; 
            vertex_buffer_data[(360*9*j)+9*i+2]=0.0*sin(angle);

            vertex_buffer_data[(360*9*j)+9*i+3]=(400.0-3.0f*j)*cos(angle);
            vertex_buffer_data[(360*9*j)+9*i+4]=(float)j;
            vertex_buffer_data[(360*9*j)+9*i+5]=(400.0-3.0f*j)*sin(angle);
            
            angle=(i+1)*2.0*M_PI/360.0;
            vertex_buffer_data[(360*9*j)+9*i+6]=(400.0-3.0f*j)*cos(angle);
            vertex_buffer_data[(360*9*j)+9*i+7]=(float)j; 
            vertex_buffer_data[(360*9*j)+9*i+8]=(400.0-3.0f*j)*sin(angle);
        }
    }

    GLfloat color_buffer_data[360*9*100];
    for(int j=0;j<100;j++){
        for(int i=0;i<360;i++){
            color_buffer_data[(360*9*j)+9*i]=(-0.7f*j+231.0f)/255.0f;
            color_buffer_data[(360*9*j)+9*i+1]=(-0.7f*j+196.0f)/255.0f; 
            color_buffer_data[(360*9*j)+9*i+2]=(-0.7f*j+150.0f)/255.0f;

            color_buffer_data[(360*9*j)+9*i+3]=(-0.7f*j+231.0f)/255.0f;
            color_buffer_data[(360*9*j)+9*i+4]=(-0.7f*j+196.0f)/255.0f;
            color_buffer_data[(360*9*j)+9*i+5]=(-0.7f*j+150.0f)/255.0f;
            
            color_buffer_data[(360*9*j)+9*i+6]=(-0.7f*j+231.0f)/255.0f;
            color_buffer_data[(360*9*j)+9*i+7]=(-0.7f*j+196.0f)/255.0f; 
            color_buffer_data[(360*9*j)+9*i+8]=(-0.7f*j+150.0f)/255.0f;
        }
    }

    this->object = create3DObject(GL_TRIANGLES, 360*3*100, vertex_buffer_data, color_buffer_data, GL_FILL);

    for(int j=0;j<90;j++){
        for(int i=0;i<360;i++){
            angle=i*2.0*M_PI/360.0;
            vertex_buffer_data[(360*9*j)+9*i]=0.0;
            vertex_buffer_data[(360*9*j)+9*i+1]=150.0f+(5.0f/9.0f)*j; 
            vertex_buffer_data[(360*9*j)+9*i+2]=0.0;

            vertex_buffer_data[(360*9*j)+9*i+3]=cos((float)j*M_PI/180.0f)*50.0f*cos(angle);
            vertex_buffer_data[(360*9*j)+9*i+4]=150.0f+(5.0f/9.0f)*j;
            vertex_buffer_data[(360*9*j)+9*i+5]=(cos((float)j*M_PI/180.0f))*50.0f*sin(angle);
            
            angle=(i+1)*2.0*M_PI/360.0;
            vertex_buffer_data[(360*9*j)+9*i+6]=(cos((float)j*M_PI/180.0f))*50.0f*cos(angle);
            vertex_buffer_data[(360*9*j)+9*i+7]=150.0f+(5.0f/9.0f)*j; 
            vertex_buffer_data[(360*9*j)+9*i+8]=(cos((float)j*M_PI/180.0f))*50.0f*sin(angle);
        }
    }
    for(int j=0;j<90;j++){
        for(int i=0;i<360;i++){
            angle=i*2.0*M_PI/360.0;
            vertex_buffer_data[360*9*90+(360*9*j)+9*i]=0.0;
            vertex_buffer_data[360*9*90+(360*9*j)+9*i+1]=150.0f-(5.0f/9.0f)*j; 
            vertex_buffer_data[360*9*90+(360*9*j)+9*i+2]=0.0;

            vertex_buffer_data[360*9*90+(360*9*j)+9*i+3]=(cos((float)j*M_PI/180.0f))*50.0f*cos(angle);
            vertex_buffer_data[360*9*90+(360*9*j)+9*i+4]=150.0f-(5.0f/9.0f)*j;
            vertex_buffer_data[360*9*90+(360*9*j)+9*i+5]=(cos((float)j*M_PI/180.0f))*50.0f*sin(angle);
            
            angle=(i+1)*2.0*M_PI/360.0;
            vertex_buffer_data[360*9*90+(360*9*j)+9*i+6]=(cos((float)j*M_PI/180.0f))*50.0f*cos(angle);
            vertex_buffer_data[360*9*90+(360*9*j)+9*i+7]=150.0f-(5.0f/9.0f)*j; 
            vertex_buffer_data[360*9*90+(360*9*j)+9*i+8]=(cos((float)j*M_PI/180.0f))*50.0f*sin(angle);
        }
    }

    this->enemy = create3DObject(GL_TRIANGLES, 720*3*90, vertex_buffer_data, COLOR_DARK, GL_FILL);
}

void Checkpoint::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->enemy);  
}

void Checkpoint::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Checkpoint::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}