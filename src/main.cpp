#include "main.h"
#include "timer.h"
#include "bg.h"
#include "plane.h"
#include "ball.h"
#include "alti.h"
#include "fuel.h"
#include "speedo.h"
#include "missile.h"
#include "bomb.h"
#include "ring.h"
#include "pointer.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

double mousexpos, mouseypos, pointerxpos=0.0f, pointerypos=0.0f;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, sphereRadius;
float camera_rotation_angle = 0;
int camView, ticks_since_camChange=10, score=0, ticks_since_missile=10, ticks_since_bomb=10;
glm::vec3 heliCam, heliDirn, eye, target, up, sphereDirn;
ostringstream str1;
string metainfo;
Bg bg;
Plane plane;
Fuel fuel;
Alti alti;
Speedo speedo;
Pointer pointer;
Ball ballarr[1000];
Missile missilearr[100];
Bomb bombarr[100];
Ring ringarr[100];

Timer t60(1.0 / 60);

void draw() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (programID);

    if(camView==0){
        eye=glm::vec3 (plane.position.x+60.0*sin(plane.yrotation*M_PI/180.0f), plane.position.y+60, plane.position.z+60.0*cos(plane.yrotation*M_PI/180.0f));
        target=glm::vec3 (plane.position.x, plane.position.y, plane.position.z);
        up=glm::vec3 (-sin(plane.yrotation*M_PI/180.0f), 1, -cos(plane.yrotation*M_PI/180.0f));
        
    }
    else if(camView==1){
        eye=glm::vec3 (100.0, 600.0, -100.0);
        target=glm::vec3 (plane.position.x, plane.position.y, plane.position.z);
        double theta=atan((600.0-plane.position.y)/sqrt((plane.position.x-100.0)*(plane.position.x-100.0)+(plane.position.z+100.0)*(plane.position.z+100.0)));
        theta=(M_PI/2.0f)-theta;
        up=glm::vec3 (glm::normalize(glm::vec3((target-eye).x, 0, (target-eye).z)).x, abs(tan(theta)), \
        	glm::normalize(glm::vec3((target-eye).x, 0, (target-eye).z)).z);
    }
    else if(camView==2){
        eye=glm::vec3 (plane.position.x, plane.position.y+200.0, plane.position.z);
        target=glm::vec3 (plane.position.x, plane.position.y, plane.position.z);
        up=glm::vec3 (0, 0, -1);
    }
    else if(camView==3){
        eye=glm::vec3 (plane.position.x-50.0*sin(plane.yrotation*M_PI/180.0f), plane.position.y, plane.position.z-50.0*cos(plane.yrotation*M_PI/180.0f));
        target=glm::vec3 (plane.position.x-60.0*sin(plane.yrotation*M_PI/180.0f), plane.position.y, plane.position.z-60.0*cos(plane.yrotation*M_PI/180.0f));
        up=glm::vec3 (-sin(plane.zrotation*M_PI/180.0f)*sin(-(plane.yrotation-90.0f)*M_PI/180.0f),\
         				cos(plane.zrotation*M_PI/180.0f),
         				sin(plane.zrotation*M_PI/180.0f)*cos(-(plane.yrotation-90.0f)*M_PI/180.0f));		
    }
    else if(camView==4){
        eye=heliCam;
        target=heliCam+heliDirn;   
    	double theta=atan((heliDirn.y)/sqrt((heliDirn.x)*(heliDirn.x)+(heliDirn.z)*(heliDirn.z)));
        theta=(M_PI/2.0f)-theta;
        up=glm::vec3 (-(glm::normalize(glm::vec3(heliDirn.x, 0, heliDirn.z))).x, abs(tan(theta)),\
        	-(glm::normalize(glm::vec3(heliDirn.x, 0, heliDirn.z))).z);
    }
    else{
    	eye=plane.position+sphereRadius*sphereDirn;
    	target=plane.position;
    	double theta=atan((-sphereDirn.y)/sqrt((sphereDirn.x)*(sphereDirn.x)+(sphereDirn.z)*(sphereDirn.z)));
        theta=(M_PI/2.0f)-theta;
        up=glm::vec3 (-(glm::normalize(glm::vec3(-sphereDirn.x, 0, -sphereDirn.z))).x, abs(tan(theta)),\
        	-(glm::normalize(glm::vec3(-sphereDirn.x, 0, -sphereDirn.z))).z);
    }
    
    glm::vec3 temp=(eye+(130.0f*glm::normalize(glm::cross(up, target-eye)))+(130.0f*glm::normalize(up))+100.0f*glm::normalize(target-eye));
    alti.set_position(temp.x, temp.y, temp.z);
        
    temp=(eye+(110.0f*glm::normalize(glm::cross(up, target-eye)))+(90.0f*glm::normalize(up))+100.0f*glm::normalize(target-eye));
    fuel.set_position(temp.x, temp.y, temp.z);

    temp=(eye+(60.0f*glm::normalize(glm::cross(up, target-eye)))+(130.0f*glm::normalize(up))+100.0f*glm::normalize(target-eye));
    speedo.set_position(temp.x, temp.y, temp.z);
    
    temp=(eye+(((float)pointerxpos/-3.0f)*glm::normalize(glm::cross(up, target-eye)))+(((float)-pointerypos/3.0f)*glm::normalize(up))+400.0f*glm::normalize(target-eye));
    pointer.set_position(temp.x, temp.y, temp.z);

    Matrices.view = glm::lookAt(eye, target, up );
    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 MVP; 
    bg.draw(VP);
    plane.draw(VP);
    if(camView<4){
    	alti.draw(VP, plane.position.y+2000.0f, eye, target, up, camView, plane.zrotation);	
	    fuel.draw(VP, plane.fuel, eye, target, up, camView, plane.zrotation);
    	speedo.draw(VP, plane.speedxz, eye, target, up, camView, plane.zrotation);
    }
	if(camView==3){
	   	pointer.draw(VP, eye, target, up, camView, plane.zrotation);
	}

    for(int i=0;i<1000;i++){
        ballarr[i].draw(VP);
    }


    for(int i=0;i<100;i++){
    	if(missilearr[i].burst==0){
        	missilearr[i].draw(VP);
    	}
    	if(bombarr[i].burst==0){
        	bombarr[i].draw(VP);
    	}
    	ringarr[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int c = glfwGetKey(window, GLFW_KEY_C);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int q = glfwGetKey(window, GLFW_KEY_Q);
    int e = glfwGetKey(window, GLFW_KEY_E);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int m = glfwGetKey(window, GLFW_KEY_M);
    int b = glfwGetKey(window, GLFW_KEY_B);

    if(camView==3){
    	glfwGetCursorPos(window, &mousexpos, &mouseypos);
    	pointerxpos+=(mousexpos-(1024/2));
    	pointerypos+=(mouseypos-(768/2));
    	pointerxpos=min(1000.0, pointerxpos);
    	pointerxpos=max(-1000.0, pointerxpos);
    	pointerypos=max(-1000.0, pointerypos);
    	pointerypos=min(1000.0, pointerypos);  	
    	glfwSetCursorPos(window, 1024/2, 768/2);
    }

    if(camView==4){
    	glfwGetCursorPos(window, &mousexpos, &mouseypos);
    	glm::vec3 temp=glm::vec3(heliDirn.x, 0, heliDirn.z);
    	glm::mat4 rotate = glm::rotate((float)(M_PI/2), glm::vec3(0, 1, 0));
    	temp=glm::vec3(rotate*glm::vec4(temp, 1));	

    	rotate = glm::rotate((float)((-mousexpos+(1024/2))/400.0f), glm::vec3(0, 1, 0));
      	rotate*= glm::rotate((float)((mouseypos-(768/2))/400.0f), temp);
    	heliDirn=glm::vec3(rotate*glm::vec4(heliDirn, 1));	
    	glfwSetCursorPos(window, 1024/2, 768/2);
    }

    if(camView==5){
    	glfwGetCursorPos(window, &mousexpos, &mouseypos);
    	glm::vec3 temp=glm::vec3(-sphereDirn.x, 0, -sphereDirn.z);
    	glm::mat4 rotate = glm::rotate((float)(M_PI/2), glm::vec3(0, 1, 0));
    	temp=glm::vec3(rotate*glm::vec4(temp, 1));	

    	rotate = glm::rotate((float)((-mousexpos+(1024/2))/400.0f), glm::vec3(0, 1, 0));
      	rotate*= glm::rotate((float)((mouseypos-(768/2))/400.0f), temp);
    	sphereDirn=-glm::vec3(rotate*glm::vec4(-sphereDirn, 1));	
    	glfwSetCursorPos(window, 1024/2, 768/2);
    }

    if(space && plane.fuel>=0.0f){
        plane.move_up();
    }

    if(m && ticks_since_missile>10){
    	ticks_since_missile=0;
    	for(int i=0;i<100;i++){
            if(missilearr[i].burst==1){
            	if(camView!=3){
                	missilearr[i]=Missile(plane.position.x, plane.position.y, plane.position.z, plane.speedxz, \
                		glm::vec3 (-sin(plane.yrotation*M_PI/180.0f), 0.0f, -cos(plane.yrotation*M_PI/180.0f)));
            	}
            	else{
            		missilearr[i]=Missile(eye.x, eye.y, eye.z, plane.speedxz, \
            			glm::normalize (pointer.position-eye));
            	}
                break;
            }
        }
    }

    if(b && ticks_since_bomb>10){
    	ticks_since_bomb=0;
    	for(int i=0;i<100;i++){
            if(bombarr[i].burst==1){
                bombarr[i]=Bomb(plane.position.x, plane.position.y, plane.position.z, plane.yrotation, plane.speedxz);
                break;
            }
        }
    }

    if(d){
        plane.tilt_left();
    }
    if(a){
        plane.tilt_right();
    }

    if(w && plane.fuel>0.0f){
        plane.accelerate();
    }
    else{
        plane.decelerate();
    }

    if(q){
        plane.turn_left();
    }
    if(e){
        plane.turn_right();
    }

    if(c && ticks_since_camChange>=10){
        camView=(camView+1)%6;
        ticks_since_camChange=0;
    }
}

void tick_elements() {
    ticks_since_camChange++;
    ticks_since_missile++;
    ticks_since_bomb++;
    plane.tick();

    for(int i=0;i<100;i++){
    	if(missilearr[i].burst==0){
        	missilearr[i].tick();
    	}
    	if(bombarr[i].burst==0){
    		bombarr[i].tick();
    	}

    	if(ringarr[i].used==0){
    		if(glm::length(ringarr[i].position-plane.position)<75.0f){
    			ringarr[i].used=1;
    			score++;
    		}
    	}

    }

}

void initGL(GLFWwindow *window, int width, int height) {
    
    bg=Bg(0.0f, 0.0f);
    plane=Plane(0.0f, 0.0f);
    alti=Alti(0.0f, 0.0f, 0.0f);
    fuel=Fuel(0.0f, 0.0f, 0.0f);
    speedo=Speedo(0.0f, 0.0f, 0.0f);
    camView=0;
    
    sphereDirn=glm::vec3(1.0f, 0.0f, 0.0f);
    sphereRadius=85.0f;
    heliCam=glm::vec3(100.0f, 100.0f, 100.0f);
    heliDirn=glm::vec3(1.0f, 0.0f, 0.0f);
    pointer=Pointer(0.0f, 0.0f, -20.0f);
    for(int i=0;i<1000;i++){
        ballarr[i]=Ball((float)(rand()%10000-5000), -2000.0f, (float)(rand()%10000-5000));
    }

    for(int i=0;i<100;i++){
        missilearr[i]=Missile(0.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
        missilearr[i].burst=1;
        
        bombarr[i]=Bomb(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        bombarr[i].burst=1;
    
        ringarr[i]=Ring((float)(rand()%10000-5000), (float)(rand()%2000-1500), (float)(rand()%10000-5000), rand()%180);
    }

    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 700;
    int height = 700;

    window = initGLFW(width, height);

    initGL (window, width, height);

    while (!glfwWindowShouldClose(window)) {

        if (t60.processTick()) {
            draw();
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);

            metainfo.clear();
            metainfo="Score: ";
            str1.str("");
            str1.clear();
            str1 << score;
            metainfo+=str1.str();
            glfwSetWindowTitle(window, metainfo.c_str());

            if(plane.position.y<=-2000.0+15.0){
                printf("------------------You Crashed----------------------\n");
                quit(window);
            }
        }
        glfwPollEvents();
    }
    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 350 / screen_zoom;
    float bottom = screen_center_y - 350 / screen_zoom;
    float left   = screen_center_x - 350 / screen_zoom;
    float right  = screen_center_x + 350 / screen_zoom;
    Matrices.projection = glm::perspective(3.14f/1.5f, 1.0f, 1.0f, 10000.0f);
}
