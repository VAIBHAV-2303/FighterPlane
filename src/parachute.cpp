#include "parachute.h"
#include "main.h"

Parachute::Parachute(float x, float y, float z, int rotn){
    this->position = glm::vec3(x, y, z);
    this->rotation = (float)rotn;
    this->speedy=0;
    this->burst=0;
    double angle;
    GLfloat vertex_buffer_data[200*180*9];
    for(int j=0;j<200;j++){
        for(int i=0;i<90;i++){
            angle=i*2.0*M_PI/360.0 + M_PI/4.0f;
            vertex_buffer_data[(180*9*j)+18*i]=72.0*cos(angle);
            vertex_buffer_data[(180*9*j)+18*i+1]=72.0*sin(angle);
            vertex_buffer_data[(180*9*j)+18*i+2]=((float)j/10.0f)-10.0f; 

            vertex_buffer_data[(180*9*j)+18*i+3]=75.0*cos(angle);
            vertex_buffer_data[(180*9*j)+18*i+4]=75.0*sin(angle);
            vertex_buffer_data[(180*9*j)+18*i+5]=((float)j/10.0f)-10.0f;
            
            angle=(i+1.0)*2.0*M_PI/360.0 + M_PI/4.0f;        
            vertex_buffer_data[(180*9*j)+18*i+6]=75.0*cos(angle);
            vertex_buffer_data[(180*9*j)+18*i+7]=75.0*sin(angle);
            vertex_buffer_data[(180*9*j)+18*i+8]=((float)j/10.0f)-10.0f; 
            

            angle=i*2.0*M_PI/360.0 + M_PI/4.0f;
            vertex_buffer_data[(180*9*j)+18*i+9]=72.0*cos(angle);
            vertex_buffer_data[(180*9*j)+18*i+10]=72.0*sin(angle);
            vertex_buffer_data[(180*9*j)+18*i+11]=((float)j/10.0f)-10.0f; 

            angle=(i+1.0)*2.0*M_PI/360.0 + M_PI/4.0f;        
            vertex_buffer_data[(180*9*j)+18*i+12]=75.0*cos(angle);
            vertex_buffer_data[(180*9*j)+18*i+13]=75.0*sin(angle);
            vertex_buffer_data[(180*9*j)+18*i+14]=((float)j/10.0f)-10.0f; 

            vertex_buffer_data[(180*9*j)+18*i+15]=72.0*cos(angle);
            vertex_buffer_data[(180*9*j)+18*i+16]=72.0*sin(angle);                
            vertex_buffer_data[(180*9*j)+18*i+17]=((float)j/10.0f)-10.0f;
        }
    }    
    this->object = create3DObject(GL_TRIANGLES, 200*180*3, vertex_buffer_data, COLOR_RED, GL_FILL);
    
    GLfloat vertex_buffer_data1[720*9];
    for(int i=0;i<360;i++){
        angle=i*2.0*M_PI/360.0;
        vertex_buffer_data1[18*i]=1.0*cos(angle);
        vertex_buffer_data1[18*i+1]=72.0; 
        vertex_buffer_data1[18*i+2]=1.0*sin(angle);

        vertex_buffer_data1[18*i+3]=1.0*cos(angle);
        vertex_buffer_data1[18*i+4]=0.0;
        vertex_buffer_data1[18*i+5]=1.0*sin(angle);
    
        angle=(i+1.0)*2.0*M_PI/360.0; 
        vertex_buffer_data1[18*i+6]=1.0*cos(angle);
        vertex_buffer_data1[18*i+7]=0.0;
        vertex_buffer_data1[18*i+8]=1.0*sin(angle);                


        angle=i*2.0*M_PI/360.0;
        vertex_buffer_data1[18*i+9]=1.0*cos(angle);
        vertex_buffer_data1[18*i+10]=72.0;
        vertex_buffer_data1[18*i+11]=1.0*sin(angle);

        angle=(i+1.0)*2.0*M_PI/360.0; 
        vertex_buffer_data1[18*i+12]=1.0*cos(angle);
        vertex_buffer_data1[18*i+13]=72.0;
        vertex_buffer_data1[18*i+14]=1.0*sin(angle);

        vertex_buffer_data1[18*i+15]=1.0*cos(angle);
        vertex_buffer_data1[18*i+16]=0.0;
        vertex_buffer_data1[18*i+17]=1.0*sin(angle);                
    }    

    this->rope = create3DObject(GL_TRIANGLES, 720*3, vertex_buffer_data1, COLOR_DARK, GL_FILL);

    GLfloat vertex_buffer_data2[]={
        -15.0f,-15.0f,-15.0f, // triangle 1 : begin
        -15.0f,-15.0f, 15.0f,
        -15.0f, 15.0f, 15.0f, // triangle 1 : end
        15.0f, 15.0f,-15.0f, // triangle 2 : begin
        -15.0f,-15.0f,-15.0f,
        -15.0f, 15.0f,-15.0f, // triangle 2 : end
        15.0f,-15.0f, 15.0f,
        -15.0f,-15.0f,-15.0f,
        15.0f,-15.0f,-15.0f,
        15.0f, 15.0f,-15.0f,
        15.0f,-15.0f,-15.0f,
        -15.0f,-15.0f,-15.0f,
        -15.0f,-15.0f,-15.0f,
        -15.0f, 15.0f, 15.0f,
        -15.0f, 15.0f,-15.0f,
        15.0f,-15.0f, 15.0f,
        -15.0f,-15.0f, 15.0f,
        -15.0f,-15.0f,-15.0f,
        -15.0f, 15.0f, 15.0f,
        -15.0f,-15.0f, 15.0f,
        15.0f,-15.0f, 15.0f,
        15.0f, 15.0f, 15.0f,
        15.0f,-15.0f,-15.0f,
        15.0f, 15.0f,-15.0f,
        15.0f,-15.0f,-15.0f,
        15.0f, 15.0f, 15.0f,
        15.0f,-15.0f, 15.0f,
        15.0f, 15.0f, 15.0f,
        15.0f, 15.0f,-15.0f,
        -15.0f, 15.0f,-15.0f,
        15.0f, 15.0f, 15.0f,
        -15.0f, 15.0f,-15.0f,
        -15.0f, 15.0f, 15.0f,
        15.0f, 15.0f, 15.0f,
        -15.0f, 15.0f, 15.0f,
        15.0f,-15.0f, 15.0f
    };
    this->human = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data2, COLOR_CRATE, GL_FILL);
}
void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->human);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate*= glm::rotate((float) (45.0f * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->rope);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate*= glm::rotate((float) (-45.0f * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->rope);
}

void Parachute::tick(){
    this->rotation+=0.3;
    this->speedy-=(1.0f/100.0f);
    this->position.y+=this->speedy;
    if(this->position.y<=-2000){
        this->burst=1;
    }
}