#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    const static GLfloat vertex_buffer_data[]={
    	0.0f, 20.0f, -10.0f,
    	0.0f, -20.0f, -10.0f,
    	0.0f, 0.0f, -20.0f,
    	0.0f, 10.0f, -10.0f,
    	0.0f, -10.0f, -10.0f,
    	0.0f, 10.0f, 20.0f,
    	0.0f, 10.0f, 20.0f,
    	0.0f, -10.0f, -10.0f,
    	0.0f, -10.0f, 20.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Arrow::draw(glm::mat4 VP, glm::vec3 eye, glm::vec3 target, glm::vec3 up, int camView, float zrotation, glm::vec3 dirn){
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
    glm::vec3 temp=glm::normalize(glm::vec3((target-eye).x, 0.0, (target-eye).z));

    theta=std::min(M_PI/2.0f, acos(dot(temp, glm::normalize(glm::vec3(dirn.x, 0.0, dirn.z)))));
    double newtheta=acos(std::min(dot(glm::normalize(glm::vec3(cos(theta)*temp.x-sin(theta)*temp.z, 0.0f, sin(theta)*temp.x+cos(theta)*temp.z)), \
    	glm::normalize(glm::vec3(dirn.x, 0.0, dirn.z))), 1.0f));

    if(newtheta<=0.1){
    	rotate*= glm::rotate((float)-theta, glm::vec3(0, 1, 0));
    }
    else{
    	rotate*= glm::rotate((float)theta, glm::vec3(0, 1, 0));
	}

    Matrices.model *= (translate * rotate );
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
void Arrow::set_position(float x, float y, float z){
    this->position=glm::vec3(x, y, z);
}

