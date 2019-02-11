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
#include "can.h"
#include "volcano.h"
#include "checkpoint.h"
#include "arrow.h"
#include "parachute.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

double mousexpos, mouseypos, pointerxpos=0.0f, pointerypos=0.0f;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, sphereRadius;
float camera_rotation_angle = 0;
int camView, ticks_since_camChange=10, score=0, ticks_since_missile=10, ticks_since_bomb=10, curCheck=1, ticks_since_enemy_missile=100;
const int numOfBalls=300, numOfCans=10, numOfVolcanoes=10, numOfRings=50, numOfParachutes=15;
glm::vec3 heliCam, heliDirn, eye, target, up, sphereDirn;
ostringstream str1;
string metainfo;
Bg bg;
Plane plane;
Fuel fuel;
Alti alti;
Speedo speedo;
Pointer pointer;
Checkpoint checkpoint;
Arrow arrow;
Ball ballarr[numOfBalls];
Missile missilearr[100];
Missile enemymissilearr[100];
Bomb bombarr[100];
Parachute parachutearr[numOfParachutes];
Ring ringarr[numOfRings];
Can canarr[numOfCans];
Volcano volcanoarr[numOfVolcanoes];

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

    temp=(eye+(100.0f*glm::normalize(up))+100.0f*glm::normalize(target-eye));
    arrow.set_position(temp.x, temp.y, temp.z);
    
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
        if(camView!=2 && glm::length(checkpoint.position-plane.position)>1000.0f){
            arrow.draw(VP, eye, target, up, camView, plane.zrotation, glm::normalize(glm::vec3(checkpoint.position-eye)));
        }
    }
	if(camView==3){
	   	pointer.draw(VP, eye, target, up, camView, plane.zrotation);
	}

    for(int i=0;i<numOfBalls;i++){
        ballarr[i].draw(VP);
    }
    for(int i=0;i<numOfRings;i++){
    	ringarr[i].draw(VP);
    }
    for(int i=0;i<numOfCans;i++){
    	if(canarr[i].used==0){
    		canarr[i].draw(VP);
    	}
    }
    for(int i=0;i<numOfVolcanoes;i++){
    	volcanoarr[i].draw(VP);
    }

    for(int i=0;i<100;i++){
        if(missilearr[i].burst==0){
            missilearr[i].draw(VP);
        }
        if(enemymissilearr[i].burst==0){
            enemymissilearr[i].draw(VP);
        }
        if(bombarr[i].burst==0){
            bombarr[i].draw(VP);
        }
    }
    checkpoint.draw(VP);
    
    for(int i=0;i<numOfParachutes;i++){
    	if(parachutearr[i].burst==0){
    		parachutearr[i].draw(VP);
    	}
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
    int h = glfwGetKey(window, GLFW_KEY_H);

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

    if(h){
        plane.hover=1;
    }
    else{
        plane.hover=0;
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

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if(action == GLFW_PRESS){
            ticks_since_missile=0;
            for(int i=0;i<100;i++){
                if(missilearr[i].burst==1){
    				system("aplay ../Sounds/shoot.wav&");
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
        else if(action==GLFW_RELEASE){
            return;
        }
        break;
    case GLFW_MOUSE_BUTTON_RIGHT:
        if(action==GLFW_PRESS) {
            ticks_since_bomb=0;
            for(int i=0;i<100;i++){
                if(bombarr[i].burst==1){
                    bombarr[i]=Bomb(plane.position.x, plane.position.y, plane.position.z, plane.yrotation, plane.speedxz);
                    break;
                }
            }
        }
        break;
    default:
        break;
    }
}

void tick_elements() {
    ticks_since_camChange++;
    ticks_since_missile++;
    ticks_since_bomb++;
    ticks_since_enemy_missile++;
    plane.tick();

    if(rand()%100 == 0){
    	for(int i=0;i<numOfParachutes;i++){
    		if(parachutearr[i].burst==1){
    			parachutearr[i]=Parachute(plane.position.x+(float)(rand()%5000 - 2500), 400.0f,\
    			 plane.position.z+(float)(rand()%5000 - 2500), rand()%180);
    			break;
    		}
    	}
    }

    if(ticks_since_enemy_missile>100-10*curCheck){
        ticks_since_enemy_missile=0;
        for(int i=0;i<100;i++){
            if(enemymissilearr[i].burst==1){
    			system("aplay ../Sounds/shoot.wav&");
                enemymissilearr[i]=Missile(checkpoint.position.x, checkpoint.position.y+150.0f, checkpoint.position.z, 0, \
                    glm::normalize(plane.position-glm::vec3(checkpoint.position.x, checkpoint.position.y+150.0f, checkpoint.position.z)));
       			break;
            }
        }
    }

    for(int i=0;i<numOfParachutes;i++){
    	if(parachutearr[i].burst==0){
    		parachutearr[i].tick();
    	    for(int j=0;j<100;j++){
    	    	if(missilearr[j].burst==0){
    	    		if(glm::length(missilearr[i].position-parachutearr[i].position)<=100.0f){
    	    			parachutearr[i].burst=1;
    	    			score+=5;
    	    			missilearr[j].burst=1;
    	    			break;
    	    		}
    	    	}
    	    	if(bombarr[j].burst==0){
    	    		if(glm::length(bombarr[i].position-parachutearr[i].position)<=100.0f){
    	    			parachutearr[i].burst=1;
    	    			score+=5;
    	    			bombarr[j].burst=1;
    	    			break;
    	    		}
    	    	}
    	    }
    	}
    }

    for(int i=0;i<100;i++){
    	if(missilearr[i].burst==0){
        	missilearr[i].tick();
    	}
        if(enemymissilearr[i].burst==0){
            enemymissilearr[i].tick();
        }
    	if(bombarr[i].burst==0){
    		bombarr[i].tick();
    	}
    }

    for(int i=0;i<numOfRings;i++){
        if(ringarr[i].used==0){
            if(glm::length(ringarr[i].position-plane.position)<75.0f){
                ringarr[i].used=1;
                score++;
    			system("aplay ../Sounds/collectcoin.wav&");
            }
        }
    }
    for(int i=0;i<numOfCans;i++){
    	if(canarr[i].used==0){
	    	canarr[i].tick();
	        if(glm::length(canarr[i].position-plane.position)<55.0f){
	    		system("aplay ../Sounds/Diamond.wav&");
	            plane.fuel+=30;
	            plane.fuel=min(plane.fuel, 100.0f);
	            canarr[i].used=1;
	            break;
	        }
    	}
    }

    for(int i=0;i<numOfVolcanoes;i++){
        if(abs(plane.position.x-volcanoarr[i].position.x)<=200.0f && abs(plane.position.z-volcanoarr[i].position.z)<=200.0f){
            system("pkill sh");
    		system("pkill aplay");
            printf("------------------You flew over a volcano----------------------\n");
            quit(window);
        }
    }

    for(int i=0;i<100;i++){
        if(enemymissilearr[i].burst==0){
            if(glm::length(enemymissilearr[i].position-plane.position)<35.0f){
                system("pkill sh");
    			system("pkill aplay");
                printf("------------------Enemy Got you----------------------\n");
                quit(window);       
            }
        }
    }

    for(int i=0;i<100;i++){
        if(missilearr[i].burst==0){
            if(abs(missilearr[i].position.y-checkpoint.position.y)<200.0f && abs(missilearr[i].position.x-checkpoint.position.x)<50.0f\
                && abs(missilearr[i].position.z-checkpoint.position.z)<50.0f){
                score+=10;
    			system("aplay ../Sounds/Diamond.wav&");
                curCheck++;
                checkpoint=Checkpoint((float)(rand()%30000-15000), -2000.0f, (float)(rand()%30000-15000));
                if(curCheck==5){
                	system("pkill sh");
    				system("pkill aplay");
                    printf("------------------You Won----------------------\n");
                    quit(window);     
                }
            }
        }
        if(bombarr[i].burst==0){
            if(abs(bombarr[i].position.y-checkpoint.position.y)<200.0f && abs(bombarr[i].position.x-checkpoint.position.x)<50.0f\
                && abs(bombarr[i].position.z-checkpoint.position.z)<50.0f){
                score+=10;
    			system("aplay ../Sounds/Diamond.wav&");
                curCheck++;
                checkpoint=Checkpoint((float)(rand()%30000-15000), -2000.0f, (float)(rand()%30000-15000));
                if(curCheck==5){
                	system("pkill sh");
    				system("pkill aplay");
                    printf("------------------You Won----------------------\n");
                    quit(window);     
                }
            }
        }
    }    
}

void initGL(GLFWwindow *window, int width, int height) {
    
	system("`while true; do aplay ./../Sounds/bg.wav; done;`&");

    bg=Bg(0.0f, 0.0f);
    plane=Plane(0.0f, 0.0f);
    alti=Alti(0.0f, 0.0f, 0.0f);
    fuel=Fuel(0.0f, 0.0f, 0.0f);
    speedo=Speedo(0.0f, 0.0f, 0.0f);
    arrow=Arrow(0.0f, 0.0f, 0.0f);

    camView=0;
    
    sphereDirn=glm::vec3(1.0f, 0.0f, 0.0f);
    sphereRadius=85.0f;
    heliCam=glm::vec3(100.0f, 100.0f, 100.0f);
    heliDirn=glm::vec3(1.0f, 0.0f, 0.0f);
    pointer=Pointer(0.0f, 0.0f, -20.0f);
    checkpoint=Checkpoint((float)(rand()%3000-1500), -2000.0f, (float)(rand()%3000-1500));

    for(int i=0;i<numOfBalls;i++){
        ballarr[i]=Ball((float)(rand()%30000-15000), -2000.0f, (float)(rand()%30000-15000));
    }

    for(int i=0;i<100;i++){
        missilearr[i]=Missile(0.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
        missilearr[i].burst=1;

        enemymissilearr[i]=Missile(0.0f, 0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f));
        enemymissilearr[i].burst=1;
        
        bombarr[i]=Bomb(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
        bombarr[i].burst=1;
    }

    for(int i=0;i<numOfRings;i++){
        ringarr[i]=Ring((float)(rand()%30000-15000), (float)(rand()%2000-1500), (float)(rand()%30000-15000), rand()%180);
    }

    for(int i=0;i<numOfParachutes;i++){
        parachutearr[i]=Parachute((float)(rand()%30000-15000), (float)(rand()%2000-1500), (float)(rand()%30000-15000), rand()%180);
    	parachutearr[i].burst=1;
    }

    for(int i=0;i<numOfVolcanoes;i++){
        volcanoarr[i]=Volcano((float)(rand()%30000-15000), -2001.0f, (float)(rand()%30000-15000));
    }

    for(int i=0;i<numOfCans;i++){
        canarr[i]=Can((float)(rand()%30000-15000), (float)(rand()%2000-1500), (float)(rand()%30000-15000));
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
            	system("pkill sh");
    			system("pkill aplay");
                printf("------------------You Crashed----------------------\n");
                quit(window);
            }
        }
        glfwPollEvents();
    }
    system("pkill sh");
    system("pkill aplay");
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
