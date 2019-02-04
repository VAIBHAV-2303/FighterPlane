#include "pointer.h"
#include "main.h"
#include<math.h>

Pointer::Pointer(float x, float y, float z){
    this->position = glm::vec3(x, y, z);
    double angle;
    GLfloat vertex_buffer_data[720*9];
    for(int i=0;i<360;i++){
        angle=i*2.0*M_PI/360.0;
        vertex_buffer_data[18*i]=32.0*cos(angle);
        vertex_buffer_data[18*i+1]=32.0*sin(angle);
        vertex_buffer_data[18*i+2]=0.0; 

        vertex_buffer_data[18*i+3]=37.0*cos(angle);
        vertex_buffer_data[18*i+4]=37.0*sin(angle);
        vertex_buffer_data[18*i+5]=0.0;
        
        angle=(i+1.0)*2.0*M_PI/360.0;        
        vertex_buffer_data[18*i+6]=37.0*cos(angle);
        vertex_buffer_data[18*i+7]=37.0*sin(angle);
        vertex_buffer_data[18*i+8]=0.0; 
        

        angle=i*2.0*M_PI/360.0;
        vertex_buffer_data[18*i+9]=32.0*cos(angle);
        vertex_buffer_data[18*i+10]=32.0*sin(angle);
        vertex_buffer_data[18*i+11]=0.0; 

        angle=(i+1.0)*2.0*M_PI/360.0;        
        vertex_buffer_data[18*i+12]=37.0*cos(angle);
        vertex_buffer_data[18*i+13]=37.0*sin(angle);
        vertex_buffer_data[18*i+14]=0.0; 

        vertex_buffer_data[18*i+15]=32.0*cos(angle);
        vertex_buffer_data[18*i+16]=32.0*sin(angle);                
        vertex_buffer_data[18*i+17]=0.0;
    }
    this->object = create3DObject(GL_TRIANGLES, 720*3, vertex_buffer_data, COLOR_DIRT, GL_FILL);
}
void Pointer::draw(glm::mat4 VP, glm::vec3 eye, glm::vec3 target, glm::vec3 up, int camView, float zrotation){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position);
    
    glm::mat4 rotate;
    double theta;
    
    theta=acos(dot(glm::normalize(glm::vec3((target-eye).x, 0.0, (target-eye).z)),glm::normalize(glm::vec3(0, 0, -1))));
        
    if((target-eye).x < 0){
        rotate= glm::rotate((float) (theta), glm::vec3(0, 1, 0));
    }
    else{
        rotate= glm::rotate((float) (-theta), glm::vec3(0, 1, 0));
    }

    theta=acos(dot(glm::normalize(glm::vec3(up)),glm::normalize(glm::vec3(0, 1, 0))));
    if(zrotation>0){
        rotate*= glm::rotate((float) (theta), glm::vec3(0, 0, 1));
    }
    else{
        rotate*= glm::rotate((float) (-theta), glm::vec3(0, 0, 1));
    }
    Matrices.model *= (translate * rotate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
void Pointer::tick() {
    
}

void Pointer::set_position(float x, float y, float z){
    this->position=glm::vec3(x, y, z);
}