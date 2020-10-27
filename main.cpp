#define GLUT_DISABLE_ATEXIT_HACK
#include<cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include<iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <time.h>
#include "heart.c"
#include "background.c"
#include "menu.c"
#include "youdied.c"
#include "cloud.c"
#include <Windows.h>
#include <MMSystem.h>
#include <random>
using namespace std;
////UI VARIABLES
//----------------
//BOSS HEALTH BAR
GLfloat bossHealthValue;
//start menu
bool start = false;
//pause menu
bool pause = false;
//pause count
int pauseCount = 0;
//death flag
bool death = false;
//protagonist health
int protHealth = 5;
//timer count
time_t startTimer, endTimer;
//play time
char playTimer[100];
//play score
char playScore[100];
//timer flag
bool timeFlag = false;
//retry flag
bool retryFlag = false;
//victory flag
bool victoryFlag = false;


////BOSS VARIABLES
//-----------------
//boss variables
GLfloat bossPosX, bossPosY, bossRadius, bossSpeed;

////Boss Attack Variables
//---------------------
//random attack pattern
float random;
//boss Attack 1 variables
GLfloat bossAtt1X, bossAtt1Y, bossAtt1Radius, bossAtt1Speed;
//boss Attack 2 variables
GLfloat bossAtt2X, bossAtt2Y, bossAtt2Radius, bossAtt2Speed;
//boss Attack 3 variables
GLfloat bossAtt3X, bossAtt3Y, bossAtt3Radius, bossAtt3Speed;
//temp speed;
GLfloat tempSpeed1, tempSpeed2;
//boss Shock wave Attack variables
GLfloat bossAtt4X, bossAtt4Y, bossAtt4Radius, bossAtt4Speed, bossAttRadius;
//boss laser beam Attack variables
GLfloat bossAttX, bossAttY, bossAttLen, bossAttSpeed;

////PROTAGONIST VARIABLES
//------------------------
//protagonist variables
GLfloat protPosX, protPosY, protRadius, protSpeed, protAlpha;

////Protagonist Attack
//---------------------
//protagonist Attack figure circle radius
GLfloat protAttRadius;
//protagonist Attack 1
GLfloat protAtt1X, protAtt1Y, protAtt1Speed, protAlpha1;
//protagonist Attack 2
GLfloat protAtt2X, protAtt2Y, protAtt2Speed, protAlpha2;
//protagonist Attack 3
GLfloat protAtt3X, protAtt3Y, protAtt3Speed, protAlpha3;
//protagonist Attack 4
GLfloat protAtt4X, protAtt4Y, protAtt4Speed, protAlpha4;

//defense mechanism variables
//----------------------------
//protagonist movement variables
GLfloat protMovementX, protMovementY;
//transparent flags
bool itrans, iflag;
//able flags
bool canJump, canAttack;
//defense mechanism counters
int iframe, icount, jCount;
//jump flags
bool jumpUp, jumpDown;
//jump counters
int jCountUp, jCountDown;

//cloud variables
GLfloat cloudPosX, cloudPosY, cloudSpeed;
int cloudframe;
bool cloudflag = false;

void setInitialMovement(){
    ////UI VARIABLES
    //----------------
    //BOSS HEALTH BAR
    bossHealthValue = 0.496f;
    //start menu
    start = false;
    //pause menu
    pause = false;
    //pause count
    pauseCount = 0;

    ////BOSS VARIABLES
    //-----------------
    //boss X axis position
    bossPosX = 0.7f;
    //boss Y axis position
    bossPosY = -0.35f;
    //boss figure circle radius
    bossRadius = 0.2f;
    //boss Y axis speed
    bossSpeed=0.0f;

    //boss Attack X axis position
    bossAtt1X = 0.7f;
    //boss Attack Y axis position
    bossAtt1Y = -0.35f;
    //boss Attack figure circle radius
    bossAtt1Radius = 0.025f;
    //boss Attack X axis speed
    bossAtt1Speed=0.0f;
    //boss Attack X axis position
    bossAtt2X = 0.7f;
    //boss Attack Y axis position
    bossAtt2Y = -0.35f;
    //boss Attack figure circle radius
    bossAtt2Radius = 0.025f;
    //boss Attack X axis speed
    bossAtt2Speed=0.0f;
    //boss Attack X axis position
    bossAtt3X = 0.7f;
    //boss Attack Y axis position
    bossAtt3Y = -0.35f;
    //boss Attack figure circle radius
    bossAtt3Radius = 0.025f;
    //boss Attack X axis speed
    bossAtt3Speed=0.0f;
    //temporary speed
    tempSpeed1 = 0.0f;
    //temporary speed
    tempSpeed2 = 0.0f;
    //boss Attack Shock wave X axis position
    bossAtt4X = 0.7f;
    //boss Attack Shock wave Y axis position
    bossAtt4Y = -.35f;
    //boss attack radius
    bossAtt4Radius = 0.05f;
    //boss Attack Speed
    bossAtt4Speed = 0.0f;
    //boss default attack radius
    bossAttRadius = 0.05f;
    //boss Attack laser beam X axis position
    bossAttX = 0.0f;
    //boss Attack laser beam Y axis position
    bossAttY = 1.2f;
    //boss Attack laser beam length
    bossAttLen = 0.02f;
    //boss Attack laser beam length
    bossAttSpeed = 0.00f;


    ////PROTAGONIST VARIABLES
    //------------------------
    //protagonist at position X
    protPosX = -0.9f;
    //protagonist at position Y
    protPosY = -0.45f;
    //protagonist figure circle radius
    protRadius = 0.1f;
    //protagonist Y axis speed
    protSpeed = 0.0f;
    //alpha value of protagonist
    protAlpha = 1.0f;
    //defense mechanism transparent flag
    itrans = false;
    //defense mechanism flag
    iflag = true;
    //defense mechanism frame
    iframe = 30;
    //defense attackable
    canAttack = true;
    //defense frame counter
    icount = 0;
    //protagonist movement value on the X axis
    protMovementX = 0.03f;
    //Jump frame counter
    jCount = 20;
    //protagonist movement value on the Y axis
    protMovementY = 0.03f;
    //jump up flag
    jumpUp = false;
    //jump down flag
    jumpDown = false;
    //jump up counter
    jCountUp = 0;
    //jump down counter
    jCountDown = 0;
    //can jump flag
    canJump = true;

    ////Protagonist Attack
    //---------------------
    //protagonist Attack figure circle radius
    protAttRadius = 0.025f;
    //protagonist Attack X axis position
    protAtt1X = -0.9f;
    //protagonist Attack Y axis position
    protAtt1Y = -0.45f;
    //protagonist Attack X axis speed
    protAtt1Speed=0.0f;
    //alpha value of attack1
    protAlpha1 = 1.0f;
    //protagonist Attack X axis position
    protAtt2X = -0.9f;
    //protagonist Attack Y axis position
    protAtt2Y = -0.45f;
    //protagonist Attack X axis speed
    protAtt2Speed=0.0f;
    //alpha value of attack2
    protAlpha2 = 1.0f;
    //protagonist Attack X axis position
    protAtt3X = -0.9f;
    //protagonist Attack Y axis position
    protAtt3Y = -0.45f;
    //protagonist Attack X axis speed
    protAtt3Speed=0.0f;
    //alpha value of attack3
    protAlpha3 = 1.0f;
    //protagonist Attack X axis position
    protAtt4X = -0.9f;
    //protagonist Attack Y axis position
    protAtt4Y = -0.45f;
    //protagonist Attack X axis speed
    protAtt4Speed=0.0f;
    //alpha value of attack4
    protAlpha4 = 1.0f;

    //cloud variables
    cloudPosX = 0.0f;
    cloudSpeed = 0.0f;
    cloudPosY = 0.0f;
    cloudframe = 0;
}

void drawBitmapText(char *strings,float x,float y,float z){
    char *c;
    glRasterPos3f(x, y, z);

    for (c=strings; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

void update(int value){
	if(start){
        if(!pause){
            if(!death){ //when boss death true

                random = rand()%50 + 10;
                random = random/1000;

                //Boss stuffs
                //boss bounce in y axis condition
                if(bossPosY >= 0.73f)            //upper limit condition
                        bossSpeed = -random;     //set speed to negative direction
                else if(bossPosY <= -0.28f){     //lower limit condition
                        bossSpeed = random;      //set speed to positive direction
                }
                bossPosY += bossSpeed;          //update boss speed


                //first diagonal attack
                if(bossAtt1Speed>0.0f){
                    //set the bomb attack to core of the boss
                    if(bossAtt1X<=-1.2f){
                        bossAtt1X = 0.7f;
                        bossAtt1Y = bossPosY;
                        bossAtt1Speed = 0.0f;
                    }
                    //change the position of the attack
                    else
                        bossAtt1X -= bossAtt1Speed;
                        bossAtt1Y -= tempSpeed1;
                }
                else{
                    //shoot attack when in range of Y axis
                    if(bossAtt1Y>=-0.3f && bossAtt1Y<-0.2f && bossHealthValue<=0.4f){
                        bossAtt1Speed = 0.02f;
                        tempSpeed1 = 0.0025f;
                    }
                    //shoot attack when in range of Y axis
                    else if(bossAtt1Y>=0.6f && bossAtt1Y<1.0f && bossHealthValue<=0.2f){
                        bossAtt1Speed = 0.02f;
                        tempSpeed1 = 0.01f;
                    }
                    //move along with the boss
                    else{
                        bossAtt1Y = bossPosY;
                    }
                }

                //second diagonal attack
                if(bossAtt2Speed>0.0f){
                    //set the bomb attack to core of the boss
                    if(bossAtt2X<=-1.2f){
                        bossAtt2X = 0.7f;
                        bossAtt2Y = bossPosY;
                        bossAtt2Speed = 0.0f;
                    }
                    //change the position of the attack
                    else
                        bossAtt2X -= bossAtt2Speed;
                        bossAtt2Y -= tempSpeed2;
                }
                else{
                    //shoot attack when in range of Y axis
                    if(bossAtt2Y>=0.0f && bossAtt2Y<0.1f && bossHealthValue<=0.3f){
                        bossAtt2Speed = 0.03f;
                        tempSpeed2 = 0.0075f;
                    }
                    //shoot attack when in range of Y axis
                    else if(bossAtt2Y>=0.3f && bossAtt2Y<0.6f && bossHealthValue<=0.1f){
                        bossAtt2Speed = 0.03f;
                        tempSpeed2 = 0.013f;
                    }
                    //move along with the boss
                    else{
                        bossAtt2Y = bossPosY;
                    }
                }

                //third diagonal attack
                if(bossAtt3Speed>0.0f){
                    //set the bomb attack to core of the boss
                    if(bossAtt3X<=-1.2f){
                        bossAtt3X = 0.7f;
                        bossAtt3Y = bossPosY;
                        bossAtt3Speed = 0.0f;
                    }
                    //change the position of the attack
                    else
                        bossAtt3X -= bossAtt3Speed;
                        bossAtt3Y -= 0.0075f;
                }
                else{
                    //shoot attack when in range of Y axis
                    if(bossAtt3Y>=0.2f && bossAtt3Y<0.3f){
                        bossAtt3Speed = 0.02f;
                    }
                    //move along with the boss
                    else{
                        bossAtt3Y = bossPosY;
                    }
                }

                //heat wave attack when boss touched the ground
                if(bossAtt4Speed > 0.0f){
                    //set the bomb attack to core of the boss
                    if(bossAtt4X<=-1.2f){
                        bossAtt4X = bossPosX;
                        bossAtt4Y = bossPosY;
                        bossAtt4Radius = 0.05f;
                        bossAtt4Speed = 0.0f;
                    }
                    //change the position of the attack
                    else{
                        if(bossAtt4Radius<=0.11)   bossAtt4Radius += 0.0015f;
                        bossAtt4X -= bossAtt4Speed;
                    }
                }
                else{
                    if(bossAtt4Y>=-0.3f && bossAtt4Y<=-0.28f){
                        bossAtt4Speed = 0.015f;
                    }
                    else{
                        bossAtt4Y = bossPosY;
                    }
                }


                //boss final stage
                if(bossHealthValue<0.0f){
                    //heat laser attack when boss touched the ceiling
                    if(bossAttSpeed > 0.0f){
                        //set the laser attack to initial place
                        if(bossAttLen>=1.715f){
                            bossAttLen = 0.02f;
                            bossAttSpeed = 0.0f;
                        }
                        //change the length of the attack across Y axis
                        else{
                            bossAttLen += bossAttSpeed;
                        }
                    }
                    else{
                        if(bossPosY>=0.6f){
                            if(bossAttX>=0.4f){
                                bossAttX = -0.2f;
                            }
                            else{
                                bossAttX += 0.1f;
                            }
                            bossAttSpeed = 0.05f;
                        }
                        else{
                            bossAttLen = 0.02f;
                        }
                    }
                }

                //Boss collision
                if((protAtt1X+protAttRadius)<=(bossPosX+bossRadius-.02f) && (protAtt1X-protAttRadius)>=(bossPosX-bossRadius+.02f)){
                    if((protAtt1Y+protAttRadius)<=(bossPosY+bossRadius-.02f) && (protAtt1Y-protAttRadius)>=(bossPosY-bossRadius+.02f)){
                            protAtt1X = protPosX;
                            protAtt1Y = protPosY;
                            protAtt1Speed = 0.0f;
                            bossHealthValue-=0.02f;
                    }
                }

                if((protAtt2X+protAttRadius)<=(bossPosX+bossRadius-.02f) && (protAtt2X-protAttRadius)>=(bossPosX-bossRadius+.02f)){
                    if((protAtt2Y+protAttRadius)<=(bossPosY+bossRadius-.02f) && (protAtt2Y-protAttRadius)>=(bossPosY-bossRadius+.02f)){
                            protAtt2X = protPosX;
                            protAtt2Y = protPosY;
                            protAtt2Speed = 0.0f;
                            bossHealthValue-=0.02f;
                    }
                }

                if((protAtt3X+protAttRadius)<=(bossPosX+bossRadius-.02f) && (protAtt3X-protAttRadius)>=(bossPosX-bossRadius+.02f)){
                    if((protAtt3Y+protAttRadius)<=(bossPosY+bossRadius-.02f) && (protAtt3Y-protAttRadius)>=(bossPosY-bossRadius+.02f)){
                            protAtt3X = protPosX;
                            protAtt3Y = protPosY;
                            protAtt3Speed = 0.0f;
                            bossHealthValue-=0.02f;
                    }
                }


                //protagonist collision
                //first attack collision
                if((bossAtt1X+bossAtt1Radius-0.025f)<=(protPosX+protRadius) && (bossAtt1X-bossAtt1Radius+0.025f)>=(protPosX-protRadius)){
                    if((bossAtt1Y+bossAtt1Radius-0.025f)<=(protPosY+protRadius) && (bossAtt1Y-bossAtt1Radius+0.025f)>=(protPosY-protRadius)){
                        if(!itrans){
                            bossAtt1X = 0.7f;
                            bossAtt1Y = bossPosY;
                            bossAtt1Speed = 0.0f;
                            protHealth--;
                        }
                    }
                }

                //second attack collision
                if((bossAtt2X+bossAtt2Radius-0.025f)<=(protPosX+protRadius) && (bossAtt2X-bossAtt2Radius+0.025f)>=(protPosX-protRadius)){
                    if((bossAtt2Y+bossAtt2Radius-0.025f)<=(protPosY+protRadius) && (bossAtt2Y-bossAtt2Radius+0.025f)>=(protPosY-protRadius)){
                        if(!itrans){
                            bossAtt2X = 0.7f;
                            bossAtt2Y = bossPosY;
                            bossAtt2Speed = 0.0f;
                            protHealth--;
                        }
                    }
                }

                //third attack collision
                if((bossAtt3X+bossAtt3Radius-0.025f)<=(protPosX+protRadius) && (bossAtt3X-bossAtt3Radius+0.025f)>=(protPosX-protRadius)){
                    if((bossAtt3Y+bossAtt3Radius-0.025f)<=(protPosY+protRadius) && (bossAtt3Y-bossAtt3Radius+0.025f)>=(protPosY-protRadius)){
                        if(!itrans){
                            bossAtt3X = 0.7f;
                            bossAtt3Y = bossPosY;
                            bossAtt3Speed = 0.0f;
                            protHealth--;
                        }
                    }
                }

                //heat wave attack collision
                if((bossAtt4X+bossAtt4Radius-.12f)<=(protPosX+protRadius) && (bossAtt4X-bossAtt4Radius+.12f)>=(protPosX-protRadius)){
                    if((bossAtt4Y+bossAtt4Radius-.18f)<=(protPosY+protRadius) && (bossAtt4Y-bossAtt4Radius+.18f)>=(protPosY-protRadius)){
                        if(!itrans){
                            bossAtt4X = bossPosX;
                            bossAtt4Y = bossPosY;
                            bossAtt4Radius = 0.05f;
                            bossAtt4Speed = 0.0f;
                            protHealth--;
                        }
                    }
                }

                //laser attack collision
                if(bossAttX<=(protPosX+protRadius) && bossAttX>=(protPosX-protRadius) || (bossAttX-0.4f)<=(protPosX+protRadius) && (bossAttX-0.4f)>=(protPosX-protRadius) || (bossAttX-0.8f)<=(protPosX+protRadius) && (bossAttX-0.8f)>=(protPosX-protRadius)){
                    if((bossAttY-bossAttLen)<=(protPosY+protRadius)){
                        if(!itrans){
                            bossAttLen = 0.02f;
                            bossAttSpeed = 0.0f;
                            protHealth--;
                        }
                    }
                }

                //cloud variables
                if(!cloudflag){
                    cloudSpeed = 0.0005f;       //set speed to positive direction
                    if(cloudframe<=100)
                        cloudframe++;
                    else
                        cloudflag = true;
                }
                else{
                    cloudSpeed = -0.0005f;       //set speed to negative direction
                    if(cloudframe>=0)
                        cloudframe--;
                    else
                        cloudflag = false;
                }
                cloudPosX += cloudSpeed;

            }
            else if(!timeFlag){
                endTimer = time(NULL);
                int diffTime = (int)difftime(endTimer, startTimer);
                string score = to_string(1000*protHealth-(diffTime*10));
                string time = to_string(diffTime);
                for(int i=0; i<=time.length(); i++){
                        playTimer[i] = time[i];
                }
                for(int i=0; i<=score.length(); i++){
                        playScore[i] = score[i];
                }
                timeFlag = false;
            }

            //PROTAGOINIST STUFF

            //protagonist jump

            if(jumpUp == true){
                canJump = false;
                protPosY += protMovementY;
                jCountUp++;
                if(jCountUp == jCount){
                    jumpUp = false;
                    jCountUp = 0;
                    jumpDown = true;
                }
            }
            if(jumpDown == true){
                protPosY -= protMovementY;
                jCountDown++;
                if(jCountDown == jCount){
                    jumpUp = false;
                    jCountDown = 0;
                    jumpDown = false;
                    canJump = true;
                }
            }

            //defense transparent mechanism for protagonist
            if(itrans==true){
                if(icount != iframe){
                    iflag = false;
                    icount ++;
                    protAlpha = 0.3f;
                    canAttack = false;
                }
                else {
                    canAttack = true;
                    protAlpha = 1;
                    iflag = true;
                    itrans = false;
                    icount = 0;
                }
            }

            //protagonist first straight attack
            if(protAtt1Speed>0.0f){
                protAlpha1 = 1;     //bullet visible
                if(protAtt1X>=1.0f){
                    protAtt1X = protPosX;
                    protAtt1Y = protPosY;
                    protAtt1Speed = 0.0f;
                }
                //change the position of the attack
                else
                    protAtt1X += protAtt1Speed;
            }
            else{
                //move along with the boss
                protAtt1X = protPosX;
                protAtt1Y = protPosY;
                protAlpha1 = 0;     //bullet transparent
            }

            //protagonist first diagonal attack
            if(protAtt2Speed>0.0f){
                protAlpha2 = 1;     //bullet visible
                if(protAtt2X>=1.0f){
                    protAtt2X = protPosX;
                    protAtt2Y = protPosY;
                    protAtt2Speed = 0.0f;
                }
                //change the position of the attack
                else
                    protAtt2X += protAtt2Speed;
                    protAtt2Y += protAtt2Speed;
            }
            else{
                //move along with the boss
                protAtt2X = protPosX;
                protAtt2Y = protPosY;
                protAlpha2 = 0;     //bullet transparent
            }

            //protagonist second diagonal attack
            if(protAtt3Speed>0.0f){
                protAlpha3 = 1;     //bullet visible
                if(protAtt3X>=1.0f){
                    protAtt3X = protPosX;
                    protAtt3Y = protPosY;
                    protAtt3Speed = 0.0f;
                }
                //change the position of the attack
                else
                    protAtt3X += protAtt3Speed;
                    protAtt3Y += protAtt3Speed/2;
            }
            else{
                //move along with the boss
                protAtt3X = protPosX;
                protAtt3Y = protPosY;
                protAlpha3 = 0;     //bullet transparent
            }



            //boss death
            if(bossHealthValue<=-0.499){
                death = true;
                bossAttLen = 0.0f;
                cloudPosY += 0.003f;
                if(bossAtt1Radius>=0.0f)    bossAtt1Radius -= 0.001f;
                if(bossAtt2Radius>=0.0f)    bossAtt2Radius -= 0.001f;
                if(bossAtt3Radius>=0.0f)    bossAtt3Radius -= 0.001f;
                if(bossAtt4Radius>=0.0f)    bossAtt4Radius -= 0.001f;
                if(bossAttRadius>=0.0f)     bossAttRadius  -= 0.001f;
                if(bossRadius>0.0f)
                    bossRadius -= 0.001;
                else{
                    //start = false;
                    victoryFlag = true;
                    timeFlag = true;
                }
            }

            glutPostRedisplay();

            glutTimerFunc(1000/60, update, 0);
        }

        else{
            glutPostRedisplay();
            glutTimerFunc(1000/60, update, 0);
        }
	}
	else{
        if(timeFlag){
            endTimer = time(NULL);
            int diffTime = (int)difftime(endTimer, startTimer);
            string score = to_string(diffTime*100);
            string time = to_string(diffTime);
            for(int i=0; i<=time.length(); i++){
                    playTimer[i] = time[i];
            }
            for(int i=0; i<=score.length(); i++){
                    playScore[i] = score[i];
            }
            timeFlag = false;
        }
        glutPostRedisplay();
        glutTimerFunc(1000/60, update, 0);
	}
}

void init(){
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void handleMouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON){
		if (state == GLUT_DOWN){
		}
	}
	glutPostRedisplay();
}

void handleKeypress(unsigned char key, int x, int y){

	switch (key) {
    case 'x':
        if(pause) break;
        else if(!itrans)
            protAtt3Speed = 0.05f;
        break;
    case 'c':
        if(pause) break;
        else if(!itrans)
            protAtt1Speed = 0.05f;
        break;
    case 'z':
        if(pause) break;
        else if(!itrans)
            protAtt2Speed = 0.05f;
        break;
    case 32:
        if(pause) break;
        bossAtt1Speed = 0.1f;
        break;
    case 13: //entet
        setInitialMovement();
        death = false;
        bossHealthValue = 0.496f;
        startTimer = time(NULL);
        if(!start && !retryFlag && !victoryFlag){
            start = true;
        }
        else if(retryFlag){
            retryFlag = false;
        }
        else if(victoryFlag){
            victoryFlag = false;
        }
        break;
    case 'p':
        if(pauseCount==0){
            pause = true;
            pauseCount = 1;
        }
        else{
            pause = false;
            pauseCount = 0;
        }
        break;

    glutPostRedisplay();
	}
}

void specialKey(int key, int x, int y){
    switch (key) {
    case GLUT_KEY_LEFT:
        if(pause) break;
        else if(protPosX>=-0.88f){
            protPosX -= protMovementX;
        }
        break;
    case GLUT_KEY_RIGHT:
        if(pause) break;
        else if(protPosX<=0.28f){
            protPosX += protMovementX;
        }
        break;
    case GLUT_KEY_UP:
        if(pause) break;
        else if(canJump){
            jumpUp = true;
            jumpDown = false;
        }
        break;
    case GLUT_KEY_DOWN:
        if(pause) break;
        else if(iflag==true)
            itrans = true;
        break;
    default:
        break;
    }
}

void displayMenu(){
    glColor4f(0.0f,0.0f,0.0f, 1);
    gluBuild2DMipmaps(GL_TEXTURE_2D, menu.bytes_per_pixel, menu.width, menu.height, GL_RGBA, GL_UNSIGNED_BYTE, menu.pixel_data);
    glEnable(GL_TEXTURE_2D);
    glColor4f(1.0, 1.0, 1.0,1.0);
    glPushMatrix();
    glScalef(1,-1,1);
    glTranslatef(0,0,0);
    glBegin(GL_QUADS);
    glTexCoord2d(1.0, 0.0); glVertex2d(1.0, -1.0);
    glTexCoord2d(1.0, 1.0); glVertex2d(1.0, 1.0);
    glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, 1.0);
    glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor4f(1.0f,0.0f,0.0f, 1.0f);
    drawBitmapText("Press 'Enter'", -0.12f, 0.15f, 0.0f);

    glColor3f(1.0f,0.0f,0.0f);
    drawBitmapText("Play", -0.04f, 0.25f, 0.0f);
    drawBitmapText("Instruction", -0.1f, -0.0f, 0.0f);
    drawBitmapText("Key 'z': Top Attack", -0.18f, -0.1f, 0.0f);
    drawBitmapText("Key 'x': Mid Attack", -0.18f, -0.2f, 0.0f);
    drawBitmapText("Key 'c': Straight Attack", -0.18f, -0.3f, 0.0f);
    drawBitmapText("Key 'Up': Jump", -0.18f, -0.4f, 0.0f);
    drawBitmapText("Key 'Down': Defense", -0.18f, -0.5f, 0.0f);
    drawBitmapText("Key 'Left': Move Left", -0.18f, -0.6f, 0.0f);
    drawBitmapText("Key 'Right': Move Right", -0.18f, -0.7f, 0.0f);
    drawBitmapText("Key 'P': Pause Menu", -0.18f, -0.8f, 0.0f);
}

void displayRetryScreen(){
    glColor4f(0.0f,0.0f,0.0f, 1);
    gluBuild2DMipmaps(GL_TEXTURE_2D, youdied.bytes_per_pixel, youdied.width, youdied.height, GL_RGBA, GL_UNSIGNED_BYTE, youdied.pixel_data);
    glEnable(GL_TEXTURE_2D);
    glColor4f(1.0, 1.0, 1.0,1.0);
    glPushMatrix();
    glScalef(1,-1,1);
    glTranslatef(0,0,0);
    glBegin(GL_QUADS);
    glTexCoord2d(1.0, 0.0); glVertex2d(1.0, -1.0);
    glTexCoord2d(1.0, 1.0); glVertex2d(1.0, 1.0);
    glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, 1.0);
    glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor4f(1.0f,0.0f,0.0f, 1.0);
    drawBitmapText("Press 'Enter' to Continue", -0.24f, -0.3f, 0.0f);
    glColor4f(1.0f,0.0f,0.0f, 1);
    drawBitmapText("Time Lasted: ", -0.2f, 0.4f, 0.0f);
    drawBitmapText(playTimer, 0.1f, 0.4f, 0.0f);
    drawBitmapText("Score: ", -0.12f, 0.3f, 0.0f);
    drawBitmapText(playScore, 0.0f, 0.3f, 0.0f);
}

void displayVictoryScreen(){
    glColor4f(1.0f,0.0f,0.0f, 1.0f);
    drawBitmapText("Press 'Enter' to Continue", -0.25f, -0.15f, 0.0f);
    glColor4f(1.0f,0.0f,0.0f, 1.0f);
    drawBitmapText("Good For You", -0.15f, 0.08f, 0.0f);
    drawBitmapText("Time Taken: ", -0.2f, 0.4f, 0.0f);
    drawBitmapText(playTimer, 0.1f, 0.4f, 0.0f);
    drawBitmapText("Score: ", -0.12f, 0.3f, 0.0f);
    drawBitmapText(playScore, 0.0f, 0.3f, 0.0f);
}

void displayCloud(float x, float y, float scale){
    glColor4f(0.0f,0.0f,0.0f, 1);
    gluBuild2DMipmaps(GL_TEXTURE_2D, cloud.bytes_per_pixel, cloud.width, cloud.height, GL_RGBA, GL_UNSIGNED_BYTE, cloud.pixel_data);
    glEnable(GL_TEXTURE_2D);
    glColor4f(1.0, 1.0, 1.0,1.0);
    glPushMatrix();
    glScalef(1*scale,1*scale,1);
    glTranslatef(cloudPosX,cloudPosY,0);
    glBegin(GL_QUADS);
    glTexCoord2d(1.0, 0.0); glVertex2d(x+.35f, y-.25f);
    glTexCoord2d(1.0, 1.0); glVertex2d(x+.35f, y+.25f);
    glTexCoord2d(0.0, 1.0); glVertex2d(x-.35f, y+.25f);
    glTexCoord2d(0.0, 0.0); glVertex2d(x-.35f, y-.25f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);

    if(!start && !retryFlag && !victoryFlag){
        displayMenu();
    }
    else if(retryFlag){
        displayRetryScreen();
    }
    else if(victoryFlag){
        displayVictoryScreen();
    }
    else{
//    //FRAMEWORK
//        //GROUND
//        glBegin(GL_LINES);
//        glColor3f(1.0f, 0.0f, 0.0f);
//        glVertex2f(-1.0f,-0.55f);
//        glVertex2f(1.0f,-0.55f);
//        glEnd();
//        //END GROUND
//        //menu
//        glBegin(GL_LINES);
//        glColor3f(1.0f, 0.0f, 0.0f);
//        glVertex2f(-1.0f, 0.82f);
//        glVertex2f(1.0f, 0.82f);
//        glEnd();
//        //end menu
//        //BACKGROUND WITH SKY
//        glBegin(GL_LINES);
//        glColor3f(1.0f, 0.0f, 0.0f);
//        glVertex2f(-1.0f,-0.55f);
//        glVertex2f(1.0f,-0.55f);
//        glEnd();
//        //END BACKGROUND WITH SKY
//        //BOSS AREA
//        glBegin(GL_LINES);
//        glColor3f(1.0f, 0.0f, 0.0f);
//        glVertex2f(0.4f,1.0f);
//        glVertex2f(0.4f,-0.55f);
//        glEnd();
//        //END BOSS AREA
//    //END FRAMEWORK


    //BACKGROUND
        gluBuild2DMipmaps(GL_TEXTURE_2D, background.bytes_per_pixel, background.width, background.height, GL_RGBA, GL_UNSIGNED_BYTE, background.pixel_data);
        glEnable(GL_TEXTURE_2D);
        glColor4f(1.0, 1.0, 1.0,1.0);
        glPushMatrix();
        glScalef(1,-1,1);
        glTranslatef(0,0,0);
        glBegin(GL_QUADS);
        glTexCoord2d(1.0, 0.0); glVertex2d(1.0, -1.0);
        glTexCoord2d(1.0, 1.0); glVertex2d(1.0, 1.0);
        glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, 1.0);
        glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    //END BACKGROUND


    //Health Bar of Boss
        glLineWidth(3.0);
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f,0.5f,0.0f);
        glVertex2f(-0.5f,-0.9f);
        glVertex2f(-0.5f,-0.8f);
        glVertex2f(0.5f,-0.8f);
        glVertex2f(0.5f,-0.9f);
        glEnd();
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex2f(-0.499f,-0.895f);
        glVertex2f(-0.499f,-0.805f);
        glVertex2f(bossHealthValue,-0.805f);
        glVertex2f(bossHealthValue,-0.895f);
        glEnd();
        glLineWidth(1.0);

    //cloud
        displayCloud(0.8f, 0.85f, 1.09f);
        displayCloud(0.5f, 0.85f, 1.07f);
        displayCloud(0.3f, 0.85f, 1.09f);
        displayCloud(0.1f, 0.85f, 1.05f);
        displayCloud(-0.2f, 0.85f, 1.13f);
        displayCloud(-0.4f, 0.85f, 1.1f);
        displayCloud(-0.7f, 0.85f, 1.05f);
        displayCloud(-0.9f, 0.85f, 1.1f);

    //PROTAGONIST HEALTH BAR
        gluBuild2DMipmaps(GL_TEXTURE_2D, heart.bytes_per_pixel, heart.width, heart.height, GL_RGBA, GL_UNSIGNED_BYTE, heart.pixel_data);
        glEnable(GL_TEXTURE_2D);
        glColor4f(1.0, 1.0, 1.0,1.0);
        if(protHealth>0){
            if(protHealth>1){
                if(protHealth>2){
                    if(protHealth>3){
                        if(protHealth>4){
                            glBegin(GL_QUADS);
                            glTexCoord2d(0.0, 1.0); glVertex2d(-0.65, 0.85);
                            glTexCoord2d(0.0, 0.0); glVertex2d(-0.65, 0.95);
                            glTexCoord2d(1.0, 0.0); glVertex2d(-0.75, 0.95);
                            glTexCoord2d(1.0, 1.0); glVertex2d(-0.75, 0.85);
                            glEnd();
                        }
                        glBegin(GL_QUADS);
                        glTexCoord2d(0.0, 1.0); glVertex2d(-0.7, 0.85);
                        glTexCoord2d(0.0, 0.0); glVertex2d(-0.7, 0.95);
                        glTexCoord2d(1.0, 0.0); glVertex2d(-0.8, 0.95);
                        glTexCoord2d(1.0, 1.0); glVertex2d(-0.8, 0.85);
                        glEnd();
                    }
                    glBegin(GL_QUADS);
                    glTexCoord2d(0.0, 1.0); glVertex2d(-0.75, 0.85);
                    glTexCoord2d(0.0, 0.0); glVertex2d(-0.75, 0.95);
                    glTexCoord2d(1.0, 0.0); glVertex2d(-0.85, 0.95);
                    glTexCoord2d(1.0, 1.0); glVertex2d(-0.85, 0.85);
                    glEnd();
                }
                glBegin(GL_QUADS);
                glTexCoord2d(0.0, 1.0); glVertex2d(-0.8, 0.85);
                glTexCoord2d(0.0, 0.0); glVertex2d(-0.8, 0.95);
                glTexCoord2d(1.0, 0.0); glVertex2d(-0.9, 0.95);
                glTexCoord2d(1.0, 1.0); glVertex2d(-0.9, 0.85);
                glEnd();
            }
            glBegin(GL_QUADS);
            glTexCoord2d(0.0, 1.0); glVertex2d(-0.85, 0.85);
            glTexCoord2d(0.0, 0.0); glVertex2d(-0.85, 0.95);
            glTexCoord2d(1.0, 0.0); glVertex2d(-0.95, 0.95);
            glTexCoord2d(1.0, 1.0); glVertex2d(-0.95, 0.85);
            glEnd();
            //glDisable(GL_TEXTURE_2D);
        }
        else{
            protHealth = 5;
            timeFlag = true;
            start = false;
            retryFlag = true;
        }
        glDisable(GL_TEXTURE_2D);
    //end protagonist health bar

    //PROTAGONIST
        //protagonist attack 1
        glPushMatrix();
        glTranslatef(protAtt1X, protAtt1Y, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
                glColor4f(1.0f, 1.0f, 1.0f,protAlpha1);
                    glVertex2f(0.0f, 0.0f);
                    int numSegmentsOfProtAtt1 = 75;
                    GLfloat angleOfProtAtt1;
                    for(int i=0; i<=numSegmentsOfProtAtt1; i++){
                        angleOfProtAtt1 = i*2.0f*3.14159265358979323846/numSegmentsOfProtAtt1;
                        glColor4f(0.0f, 0.0f, 1.0f,protAlpha1);
                        glVertex2f(cos(angleOfProtAtt1)*protAttRadius,sin(angleOfProtAtt1)*protAttRadius);
                    }
            glEnd();
        glPopMatrix();

        //protagonist attack 2
        glPushMatrix();
        glTranslatef(protAtt2X, protAtt2Y, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
                glColor4f(1.0f, 1.0f, 1.0f,protAlpha2);
                    glVertex2f(0.0f, 0.0f);
                    int numSegmentsOfProtAtt2 = 75;
                    GLfloat angleOfProtAtt2;
                    for(int i=0; i<=numSegmentsOfProtAtt2; i++){
                        angleOfProtAtt2 = i*2.0f*3.14159265358979323846/numSegmentsOfProtAtt2;
                        glColor4f(0.0f, 0.0f, 1.0f,protAlpha2);
                        glVertex2f(cos(angleOfProtAtt2)*protAttRadius,sin(angleOfProtAtt2)*protAttRadius);
                    }
            glEnd();
        glPopMatrix();

        //protagonist attack 3
        glPushMatrix();
        glTranslatef(protAtt3X, protAtt3Y, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
                glColor4f(1.0f, 1.0f, 1.0f,protAlpha3);
                    glVertex2f(0.0f, 0.0f);
                    int numSegmentsOfProtAtt3 = 75;
                    GLfloat angleOfProtAtt3;
                    for(int i=0; i<=numSegmentsOfProtAtt3; i++){
                        angleOfProtAtt3 = i*2.0f*3.14159265358979323846/numSegmentsOfProtAtt3;
                        glColor4f(0.0f, 0.0f, 1.0f,protAlpha3);
                        glVertex2f(cos(angleOfProtAtt3)*protAttRadius,sin(angleOfProtAtt3)*protAttRadius);
                    }
            glEnd();
        glPopMatrix();

        //protagonist body
        glPushMatrix();
        glTranslatef(protPosX, protPosY, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
                glColor4f(1.0f, 1.0f, 1.0f,protAlpha);
                glVertex2f(0.0f, 0.0f);
                int numSegmentsOfProt = 75;
                GLfloat angleOfProt;
                for(int i=0; i<=numSegmentsOfProt; i++){
                    angleOfProt = i*2.0f*3.14159265358979323846/numSegmentsOfProt;
                    glColor4f(0.0f, 0.0f, 1.0f,protAlpha);
                    glVertex2f(cos(angleOfProt)*protRadius,sin(angleOfProt)*protRadius);
                }
            glEnd();
        glPopMatrix();

    //END PROTAGONIST CODE

    //BOSS
        //boss wave attack
        glPushMatrix();
        glTranslatef(bossAtt4X, bossAtt4Y, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0.0f, 0.0f);
                int num4Segments = 50;
                GLfloat angle4;
                for(int i=0; i<=num4Segments; i++){
                    angle4 = i*2.0f*3.41/num4Segments;
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex2f(cos(angle4)*bossAtt4Radius,sin(angle4)*bossAtt4Radius);
                    glColor3f(1.0f, 1.0f, 0.0f);
                    glVertex2f(cos(angle4)*(bossAtt4Radius+0.02f),sin(angle4)*(bossAtt4Radius+0.02f));
                }
            glEnd();
        glPopMatrix();

        //boss attack
        glPushMatrix();
        glTranslatef(bossAtt1X, bossAtt1Y, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0.0f, 0.0f);
                int num1Segments = 50;
                GLfloat angle1;
                for(int i=0; i<=num1Segments; i++){
                    angle1 = i*2.0f*3.41/num1Segments;
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex2f(cos(angle1)*bossAtt1Radius,sin(angle1)*bossAtt1Radius);
                    glColor3f(1.0f, 1.0f, 0.0f);
                    glVertex2f(cos(angle1)*(bossAtt1Radius+0.02f),sin(angle1)*(bossAtt1Radius+0.02f));
                }
            glEnd();
        glPopMatrix();

        //boss attack
        glPushMatrix();
        glTranslatef(bossAtt2X, bossAtt2Y, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0.0f, 0.0f);
                int num2Segments = 50;
                GLfloat angle2;
                for(int i=0; i<=num2Segments; i++){
                    angle2 = i*2.0f*3.41/num2Segments;
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex2f(cos(angle2)*bossAtt2Radius,sin(angle2)*bossAtt2Radius);
                    glColor3f(1.0f, 1.0f, 0.0f);
                    glVertex2f(cos(angle2)*(bossAtt2Radius+0.02f),sin(angle2)*(bossAtt2Radius+0.02f));
                }
            glEnd();
        glPopMatrix();

        //boss attack
        glPushMatrix();
        glTranslatef(bossAtt3X, bossAtt3Y, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0.0f, 0.0f);
                int num3Segments = 50;
                GLfloat angle3;
                for(int i=0; i<=num3Segments; i++){
                    angle3 = i*2.0f*3.41/num3Segments;
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex2f(cos(angle3)*bossAtt3Radius,sin(angle3)*bossAtt3Radius);
                    glColor3f(1.0f, 1.0f, 0.0f);
                    glVertex2f(cos(angle3)*(bossAtt3Radius+0.02f),sin(angle3)*(bossAtt3Radius+0.02f));
                }
            glEnd();
        glPopMatrix();

        //boss laser attack
        glPushMatrix();
        glTranslatef(bossAttX, bossAttY, 0.0f);
            glBegin(GL_QUADS);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(-0.02f, 0.02f);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(-0.02f, -bossAttLen);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, -bossAttLen);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, 0.02f);

                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, 0.02f);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, -bossAttLen);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(0.02f, -bossAttLen);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(0.02f, 0.02f);
            glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(bossAttX-0.4f, bossAttY, 0.0f);
            glBegin(GL_QUADS);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(-0.02f, 0.02f);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(-0.02f, -bossAttLen);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, -bossAttLen);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, 0.02f);

                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, 0.02f);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, -bossAttLen);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(0.02f, -bossAttLen);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(0.02f, 0.02f);
            glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(bossAttX-0.8f, bossAttY, 0.0f);
            glBegin(GL_QUADS);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(-0.02f, 0.02f);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(-0.02f, -bossAttLen);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, -bossAttLen);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, 0.02f);

                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, 0.02f);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0, -bossAttLen);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(0.02f, -bossAttLen);
                glColor3f(1.0f, 1.0f, 0.0f);
                glVertex2f(0.02f, 0.02f);
            glEnd();
        glPopMatrix();

        //boss body
        glPushMatrix();
        glTranslatef(bossPosX, bossPosY, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0.0f, 0.0f);
                int numSegments = 75;
                GLfloat angle;
                for(int i=0; i<=numSegments; i++){
                    angle = i*2.0f*3.41/numSegments;
                    glColor3f(1.0f, 0.0f, 0.0f);
                    glVertex2f(cos(angle)*bossRadius,sin(angle)*bossRadius);
                    glColor3f(0.0f, 1.0f, 0.0f);
                    glVertex2f(cos(angle)*(bossRadius+0.07f),sin(angle)*(bossRadius+0.07f));
                }
            glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(bossPosX, bossPosY, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
                glColor3f(1.0f, 0.0f, 0.0f);
                glVertex2f(0.0f, 0.0f);
                int num0Segments = 50;
                GLfloat angle0;
                for(int i=0; i<=num0Segments; i++){
                    angle0 = i*2.0f*3.41/num0Segments;
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex2f(cos(angle0)*bossAttRadius,sin(angle0)*bossAttRadius);
                    glColor3f(1.0f, 1.0f, 1.0f);
                    glVertex2f(cos(angle0)*(bossAttRadius+0.02f),sin(angle0)*(bossAttRadius+0.02f));
                }
            glEnd();
        glPopMatrix();
        //end boss

        //pause screen
        if(pause){
            glColor4f(1.0f, 1.0f, 1.0f, 0.3);
            glBegin(GL_QUADS);
                glVertex2f(-1.0f,1.0f);
                glVertex2f(-1.0f,-1.0f);
                glVertex2f(1.0f,-1.0f);
                glVertex2f(1.0f,1.0f);
            glEnd();
            glColor4f(1.0f,0.0f,0.0f, 1);
            drawBitmapText("Press 'P' to Resume", -0.18f, 0.0f, 0.0f);
        }
        //end pause screen
    }
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    srand(time(0));
    glutInit(&argc, argv);                              //initialize library glut function
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);        //display mode
    glutInitWindowSize(1024, 768);                      //window size
    glutInitWindowPosition(100, 100);                   //window position
    glutCreateWindow("Boss Fight");                     //create window
    glutDisplayFunc(display);                           //callback function
    init();
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(specialKey);
    glutMouseFunc(handleMouse);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    update(10);
    sndPlaySound("music.wav",SND_ASYNC|SND_LOOP);
    glutMainLoop();                                     //
    return 0;
}
