#include "plane.h"
#include "main.h"

Plane::Plane(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->xrotation=0;
    this->yrotation=0;
    this->zrotation=0;
    this->speedxz=0;
    this->speedy=0;
    this->fuel=100.0;
    GLfloat vertex_buffer_data[10004];
    double angle;
    for(int i=0;i<360;i++){
        vertex_buffer_data[9*i]=0.0;
        vertex_buffer_data[9*i+1]=0.0;
        vertex_buffer_data[9*i+2]=-50.0; 

        angle=i*2.0*M_PI/360.0;
        vertex_buffer_data[9*i+3]=15.0*cos(angle);
        vertex_buffer_data[9*i+4]=15.0*sin(angle);
        vertex_buffer_data[9*i+5]=-30.0;
        // printf("%f %f\n", vertex_buffer_data[9*i+3], vertex_buffer_data[9*i+4]);

        angle=(i+1.0)*2.0*M_PI/360.0; 

        vertex_buffer_data[9*i+6]=15.0*cos(angle);
        vertex_buffer_data[9*i+7]=15.0*sin(angle);                
        vertex_buffer_data[9*i+8]=-30.0;
    }

    for(int i=0;i<360;i++){
        angle=i*2.0*M_PI/360.0;
        vertex_buffer_data[18*i+360*9]=15.0*cos(angle);
        vertex_buffer_data[18*i+1+360*9]=15.0*sin(angle);
        vertex_buffer_data[18*i+2+360*9]=-30.0; 

        vertex_buffer_data[18*i+3+360*9]=15.0*cos(angle);
        vertex_buffer_data[18*i+4+360*9]=15.0*sin(angle);
        vertex_buffer_data[18*i+5+360*9]=30.0;
    
        angle=(i+1.0)*2.0*M_PI/360.0; 
        vertex_buffer_data[18*i+6+360*9]=15.0*cos(angle);
        vertex_buffer_data[18*i+7+360*9]=15.0*sin(angle);                
        vertex_buffer_data[18*i+8+360*9]=30.0;


        angle=i*2.0*M_PI/360.0;
        vertex_buffer_data[18*i+9+360*9]=15.0*cos(angle);
        vertex_buffer_data[18*i+10+360*9]=15.0*sin(angle);
        vertex_buffer_data[18*i+11+360*9]=-30.0;

        angle=(i+1.0)*2.0*M_PI/360.0; 
        vertex_buffer_data[18*i+12+360*9]=15.0*cos(angle);
        vertex_buffer_data[18*i+13+360*9]=15.0*sin(angle);
        vertex_buffer_data[18*i+14+360*9]=-30.0;

        vertex_buffer_data[18*i+15+360*9]=15.0*cos(angle);
        vertex_buffer_data[18*i+16+360*9]=15.0*sin(angle);                
        vertex_buffer_data[18*i+17+360*9]=30.0;
    }

    vertex_buffer_data[360*9*3]=15.0;
    vertex_buffer_data[360*9*3+1]=0.0;
    vertex_buffer_data[360*9*3+2]=-10.0;
    vertex_buffer_data[360*9*3+3]=15.0;
    vertex_buffer_data[360*9*3+4]=0.0;
    vertex_buffer_data[360*9*3+5]=10.0;
    vertex_buffer_data[360*9*3+6]=55.0;
    vertex_buffer_data[360*9*3+7]=0.0;
    vertex_buffer_data[360*9*3+8]=10.0;

    vertex_buffer_data[360*9*3+9]=-15.0;
    vertex_buffer_data[360*9*3+10]=0.0;
    vertex_buffer_data[360*9*3+11]=-10.0;
    vertex_buffer_data[360*9*3+12]=-15.0;
    vertex_buffer_data[360*9*3+13]=0.0;
    vertex_buffer_data[360*9*3+14]=10.0;
    vertex_buffer_data[360*9*3+15]=-55.0;
    vertex_buffer_data[360*9*3+16]=0.0;
    vertex_buffer_data[360*9*3+17]=10.0;

    vertex_buffer_data[360*9*3+18]=0.0;
    vertex_buffer_data[360*9*3+19]=15.0;
    vertex_buffer_data[360*9*3+20]=30.0;
    vertex_buffer_data[360*9*3+21]=0.0;
    vertex_buffer_data[360*9*3+22]=15.0;
    vertex_buffer_data[360*9*3+23]=20.0;
    vertex_buffer_data[360*9*3+24]=0.0;
    vertex_buffer_data[360*9*3+25]=35.0;
    vertex_buffer_data[360*9*3+26]=30.0;

    this->object = create3DObject(GL_TRIANGLES, 360*9+3*3, vertex_buffer_data, COLOR_PLANE, GL_FILL);
}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->yrotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate*= glm::rotate((float) (this->zrotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // rotate*= glm::rotate((float) (this->yrotation * M_PI / 180.0f), glm::vec3(0, -1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Plane::accelerate(){
    this->speedxz+=0.02;
    this->speedxz=std::min(5.0, this->speedxz);
    this->fuel-=0.01;
}
void Plane::decelerate(){
    this->speedxz-=0.005;
    this->speedxz=std::max(0.0, this->speedxz);
}

void Plane::turn_left(){
    this->yrotation++;
}
void Plane::turn_right(){
    this->yrotation--;
}

void Plane::tilt_left(){
    this->zrotation--;
}
void Plane::tilt_right(){
    this->zrotation++;
}

void Plane::move_up(){
    if(this->position.y<500.0){
        this->speedy=0; 
        this->position.y+=5;
    }
    this->fuel-=0.01;
}

void Plane::tick() {
    this->position.x+=-speedxz*sin(this->yrotation*M_PI/180.0f);
    this->position.z+=-speedxz*cos(this->yrotation*M_PI/180.0f);
    this->speedy-=(3.0/200.0);
    this->position.y+=speedy;
    this->yrotation+=(zrotation/80.0f);
    zrotation-=(zrotation/80.0f);
}

