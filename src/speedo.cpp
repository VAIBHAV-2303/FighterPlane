#include "speedo.h"
#include "main.h"

Speedo::Speedo(float x, float y, float z) {

    double angle;
    GLfloat ring_vertex_buffer_data[360*9];
    for(int i=0;i<180;i++){
        angle=i*2.0*M_PI/360.0;
        ring_vertex_buffer_data[18*i]=30.0*cos(angle);
        ring_vertex_buffer_data[18*i+1]=30.0*sin(angle);
        ring_vertex_buffer_data[18*i+2]=0.0; 

        ring_vertex_buffer_data[18*i+3]=32.0*cos(angle);
        ring_vertex_buffer_data[18*i+4]=32.0*sin(angle);
        ring_vertex_buffer_data[18*i+5]=0.0;
        
        angle=(i+1.0)*2.0*M_PI/360.0;        
        ring_vertex_buffer_data[18*i+6]=32.0*cos(angle);
        ring_vertex_buffer_data[18*i+7]=32.0*sin(angle);
        ring_vertex_buffer_data[18*i+8]=0.0; 
        

        angle=i*2.0*M_PI/360.0;
        ring_vertex_buffer_data[18*i+9]=30.0*cos(angle);
        ring_vertex_buffer_data[18*i+10]=30.0*sin(angle);
        ring_vertex_buffer_data[18*i+11]=0.0; 

        angle=(i+1.0)*2.0*M_PI/360.0;        
        ring_vertex_buffer_data[18*i+12]=32.0*cos(angle);
        ring_vertex_buffer_data[18*i+13]=32.0*sin(angle);
        ring_vertex_buffer_data[18*i+14]=0.0; 

        ring_vertex_buffer_data[18*i+15]=30.0*cos(angle);
        ring_vertex_buffer_data[18*i+16]=30.0*sin(angle);                
        ring_vertex_buffer_data[18*i+17]=0.0;
    }
    this->ring = create3DObject(GL_TRIANGLES, 360*3, ring_vertex_buffer_data, COLOR_BLACK, GL_FILL);

    static const GLfloat vertex_buffer_data[] = {
        -20.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f        
    };
    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Speedo::draw(glm::mat4 VP, float curSpeed, glm::vec3 eye, glm::vec3 target, glm::vec3 up, int camView, float zrotation){
    this->rotation = (-curSpeed/5.0f)*180.f;
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);
    
    glm::mat4 rotate;
    double theta;
    if(camView!=3){
        theta=acos(dot(glm::normalize(glm::vec3((target-eye).x, 0.0, (target-eye).z)),glm::normalize(glm::vec3(0, 0, -1))));
        
        if((target-eye).x < 0){
            rotate= glm::rotate((float) (theta), glm::vec3(0, 1, 0));
        }
        else{
            rotate= glm::rotate((float) (-theta), glm::vec3(0, 1, 0));
        }

        if(camView==2){
            rotate= glm::rotate((float) (-acos(dot(glm::normalize(up), glm::normalize(glm::vec3(0, 1, 0))))), glm::vec3(1, 0, 0));
        }
        else{
            rotate*= glm::rotate((float) (-acos(dot(glm::normalize(up), glm::normalize(glm::vec3(0, 1, 0))))), glm::vec3(1, 0, 0));
        }
    }
    else{
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
    }
    rotate*= glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);


    Matrices.model = glm::mat4(1.0f);
    if(camView!=3){
        theta=acos(dot(glm::normalize(glm::vec3((target-eye).x, 0.0, (target-eye).z)),glm::normalize(glm::vec3(0, 0, -1))));
        
        if((target-eye).x < 0){
            rotate= glm::rotate((float) (theta), glm::vec3(0, 1, 0));
        }
        else{
            rotate= glm::rotate((float) (-theta), glm::vec3(0, 1, 0));
        }

        if(camView==2){
            rotate= glm::rotate((float) (-acos(dot(glm::normalize(up), glm::normalize(glm::vec3(0, 1, 0))))), glm::vec3(1, 0, 0));
        }
        else{
            rotate*= glm::rotate((float) (-acos(dot(glm::normalize(up), glm::normalize(glm::vec3(0, 1, 0))))), glm::vec3(1, 0, 0));
        }
    }
    else{
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
    }
    Matrices.model *= (translate * rotate );
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ring);
}

void Speedo::set_position(float x, float y, float z){
    this->position=glm::vec3(x, y, z);
}