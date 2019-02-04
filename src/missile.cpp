#include "missile.h"
#include "main.h"

Missile::Missile(float x, float y, float z, float speed, glm::vec3 dirn) {
    this->position = glm::vec3(x, y, z);
    this->speed=10.0f+speed;
    this->dirn=dirn;
    this->burst=0;
    this->time=0;
    

    GLfloat vertex_buffer_data[10004];
    double angle;
    for(int i=0;i<360;i++){
        angle=i*2.0*M_PI/360.0;
        vertex_buffer_data[18*i]=7.0*cos(angle);
        vertex_buffer_data[18*i+1]=7.0*sin(angle);
        vertex_buffer_data[18*i+2]=-5.0; 

        vertex_buffer_data[18*i+3]=7.0*cos(angle);
        vertex_buffer_data[18*i+4]=7.0*sin(angle);
        vertex_buffer_data[18*i+5]=10.0;
    
        angle=(i+1.0)*2.0*M_PI/360.0f; 
        vertex_buffer_data[18*i+6]=7.0*cos(angle);
        vertex_buffer_data[18*i+7]=7.0*sin(angle);                
        vertex_buffer_data[18*i+8]=-5.0;


        angle=i*2.0*M_PI/360.0f;
        vertex_buffer_data[18*i+9]=7.0*cos(angle);
        vertex_buffer_data[18*i+10]=7.0*sin(angle);
        vertex_buffer_data[18*i+11]=10.0;

        angle=(i+1.0)*2.0*M_PI/360.0f; 
        vertex_buffer_data[18*i+12]=7.0*cos(angle);
        vertex_buffer_data[18*i+13]=7.0*sin(angle);
        vertex_buffer_data[18*i+14]=-5.0;

        vertex_buffer_data[18*i+15]=7.0*cos(angle);
        vertex_buffer_data[18*i+16]=7.0*sin(angle);                
        vertex_buffer_data[18*i+17]=10.0;
    }
    this->object = create3DObject(GL_TRIANGLES, 720*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);

    for(int i=0;i<360;i++){
        vertex_buffer_data[9*i]=0.0;
        vertex_buffer_data[9*i+1]=0.0;
        vertex_buffer_data[9*i+2]=-10.0; 

        angle=i*2.0*M_PI/360.0;
        vertex_buffer_data[9*i+3]=7.0*cos(angle);
        vertex_buffer_data[9*i+4]=7.0*sin(angle);
        vertex_buffer_data[9*i+5]=-5.0;

        angle=(i+1.0)*2.0*M_PI/360.0; 

        vertex_buffer_data[9*i+6]=7.0*cos(angle);
        vertex_buffer_data[9*i+7]=7.0*sin(angle);                
        vertex_buffer_data[9*i+8]=-5.0;
    }

    vertex_buffer_data[360*9]=0.0;
    vertex_buffer_data[360*9+1]=7.0;
    vertex_buffer_data[360*9+2]=10.0;
    vertex_buffer_data[360*9+3]=0.0;
    vertex_buffer_data[360*9+4]=7.0;
    vertex_buffer_data[360*9+5]=0.0;
    vertex_buffer_data[360*9+6]=0.0;
    vertex_buffer_data[360*9+7]=15.0;
    vertex_buffer_data[360*9+8]=10.0;
    this->tip = create3DObject(GL_TRIANGLES, 361*3, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
    
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);  
    glm::mat4 rotate;
    if(this->dirn.z<=0){
        rotate*= glm::rotate((float) (atan(this->dirn.x/this->dirn.z)), glm::vec3(0, 1, 0));
    }
    else{
        rotate*= glm::rotate((float)(-M_PI+atan(this->dirn.x/this->dirn.z)), glm::vec3(0, 1, 0));
    }
    rotate*= glm::rotate((float)(atan(this->dirn.y/sqrt((this->dirn.z)*(this->dirn.z)+(this->dirn.x)*(this->dirn.x)))),\
            glm::vec3(1, 0, 0));
    
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->tip);
}

void Missile::tick() {
    this->time++;
    if(this->time>300.0f){
        this->burst=1;
    }
    this->position=(this->position+(speed*(this->dirn)));
}

