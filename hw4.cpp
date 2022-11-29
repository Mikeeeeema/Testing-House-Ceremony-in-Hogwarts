/******************************************
*
* Official Name:  Runzhi Ma
*
* Call me:  Runzhi
*
* E-mail:  rma115@syr.edu
*
* Assignment:  Assignment 4
*
* Environment/Compiler:  Xcode Version 13.2.1 (13C100)
*
* Date submitted:  April 11, 2022
*
* References: None
*
* Interactions:
*                 Press esc to quit.
*                 Press 0 to view from the top.
*                 Press 1 to view from the north
*                 Press 2 to view from the south
*                 Press 3 to view from the west
*                 Press 4 to view from the east
*                 Press 5 to view from the first person view
*                 Press l or click the black botton on the right side of the wall  to open or close the spot light
*                 Press d or click the door to open or close the door
*                 Press f to open the flash light
*                 Press s to pick up or drop the flash light
*                 Press w or click the wand to make the wand fly and start the ceremony
*                 Press g to choose Gryffindor
*                 Press h to choose Hufflepuff
*                 Press r to choose Ravenclaw
*                 Press n to choose Slytherin
*                 Press + to choose look up
*                 Press - to choose look down
*                 Press GLUT_KEY_UP  to move forward
*                 Press GLUT_KEY_DOWN to move backward
*                 Press GLUT_KEY_RIGHT to turn right
*                 Press GLUT_KEY_LEFT to turn left
*                 Right button to activate the menu; In the menu, you can either quit or activate the light effect of the moon
*******************************************/
#include <cmath>
#include <iostream>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#define PI 3.14159265
#include <math.h>
#define ONE_BY_ROOT_THREE 0.57735
static float meX=15, meY=3,meZ=0;
//meZ = -8
static float lookUp = 0;
static float angle=180;  //angle facing
static float stepsize=1.0;  //step size
static float turnsize=5.0;
float doorX = 0.75;
using namespace std;
static int scene;
static long font = (long)GLUT_BITMAP_8_BY_13;
bool scenex11WorkAround = true;  //***X11Fix
static int view = 5;
static int width = 500;
static int height = 500;
static int quidditichBallAnl = 0;
static int quidditichWingAnl = 0;
static bool wingsUp = true;
static bool moonAppear = false;
static bool openSpotLight = false;
static bool openFlashLight = false;
static bool pickFlashLight = false;
static bool wandFly = false;
static bool generateSchool = false;
static bool hatTop = false;
bool selecting = false;
int xClick,yClick;
float wandAng = 0;
static int choose = 0;
int openDoor = true;
float black[3] = {0,0,0};
float white[3] = {1, 1, 1};
static float t = 0.0; // Quadratic attenuation factor.
static float flashLightX = 15, flashLightY = 2, flashLightZ = -3;

// Main house vertex co-ordinate vectors.
static float MainHouseVertices[] =
{
    4.0, -4.0, 4.0,  //0
    4.0, 4.0, 4.0,   //1
    4.0, 4.0, -6.0, //2
    4.0, -4.0, -6.0,//3
    -4.0, -4.0, 4.0,//4
    -4.0, 4.0, 4.0,//5
    -4.0, 4.0, -6.0,//6
    -4.0, -4.0, -6.0,//7
    0.0, 6.0, 4.0,//8
    0.0, 6.0, -6.0,//9
    -1.5,-4,4,//10
    -1.5,1,4,//11
    1.5,1,4,//12
    1.5,-4,4,//13
    -4,1,4,//14
    4,1,4//15
    
};

//static unsigned char MainHouseIndices[] =
//{
//    3, 2, 1, 0,
//    7, 6, 2, 3,
//    4, 5, 6, 7,
////    4, 7, 3, 0,
////    8, 9, 5, 6,  ？这两行家在哪里 可以单独画么
////    8, 9, 1, 2,
//    0, 1, 5, 4 //Front wall
//};

void writeBitmapString(void *font, const char *string)
{
   const char *c;
   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void setProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-10.0, 10.0, -10.0, 10.0, 1.0, 21.0);
    
    glFrustum(-2,2,-2,2,1,25);
    //glOrtho(0, 50, 0, 50, 1, 120);
    
    //gluPerspective(80, 1, 1, 21);
    
    glMatrixMode(GL_MODELVIEW);
   
}

void drawGround(void){
//    glColor3f(157.0/255, 110.0/255, 94.0/255);
    glPushMatrix();
    glTranslated(15,-.5,-10);
    glScaled(30, 1, 20);
    glutSolidCube(1);
    glPopMatrix();
}

void drawTable(float height, float length, float depth, float width) {
    float matAmbAndDif1[] = {191.0/255, 177.0/255, 150.0/255, 1.0};
 
    float matSpec[] = {1.0, 1.0, 1.0, 1.0};
    float matShine[] = {50.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glColor3f(0.5, 0.4, 0.2);

    glPushMatrix();
        glTranslatef(0, height, 0);
        glScalef(length, width, depth);
        glutSolidCube(1);
    glPopMatrix();

    float leg_x = length / 2.0 - width / 2.;
    float leg_z = depth / 2.0 - width / 2.;
    
    glPushMatrix();
    glTranslatef(-leg_x, height / 2.0, leg_z);
    glScalef(width, height, width);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(leg_x, height / 2.0, -leg_z);
    glScalef(width, height, width);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-leg_x, height / 2.0, -leg_z);
    glScalef(width, height, width);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(leg_x, height / 2.0, leg_z);
    glScalef(width, height, width);
    glutSolidCube(1);
    glPopMatrix();
}

void setup(void){
    //dark blue background
    glClearColor(0, 0, 139.0/255, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightDifAndSpec1[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightPos[] = { 15, 1.5, -10.0, 1.0 };
    float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };
    
    // Light properties.
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    glEnable(GL_LIGHT0); // Enable particular light source.
    glDisable(GL_LIGHT1);
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);
    
    glDisable(GL_LIGHT2);
    
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDifAndSpec1);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightDifAndSpec1);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Enable two-sided lighting.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.
    glEnable(GL_NORMALIZE);

}


void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)w/(float)h,1,20);
    glMatrixMode(GL_MODELVIEW);
    
}

void drawDoor(){
//    glColor4f(0.6, 0.6, 0.6, 1.0);
    float matAmbAndDif1[] = {191.0/255, 177.0/255, 150.0/255, 1.0};
    float matAmbAndDif2[] = {182.0/255, 141.0/255, 82.0/255, 1.0};
    float matSpec[] = {1.0, 1.0, 1.0, 1.0};
    float matShine[] = {50.0};
    
    
    glPushMatrix();
    glTranslatef(15+doorX, 2.5, -6);
    glScalef(1.5,5.0,0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glutSolidCube(1.0);
    glColor3f(1, 0, 0);
    
    glPushMatrix();
    glRotatef(0, 0, 1, 0);
    glTranslatef(-0.2, 0, 0.5);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
    glutSolidTorus(0.1, 0.5, 20, 20);
    glPopMatrix();
    
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15-doorX, 2.5, -6);
    glScalef(1.5,5,0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glutSolidCube(1);
    
    glPushMatrix();
    glRotatef(0, 0, 1, 0);
    glTranslatef(0.2, 0, 0.5);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
    glutSolidTorus(0.1, 0.5, 20, 20);
    glPopMatrix();
    glPopMatrix();
}

void writeStrokeString(void *font, const char *string)
{
    const char *c;
    for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}

void getID(int x, int y)
{
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    //printed only for demonstration
    cout << "R: " << (int)pixel[0] << endl;
    cout << "G: " << (int)pixel[1] << endl;
    cout << "B: " << (int)pixel[2] << endl;
    cout << endl;
    
    if((int)pixel[0]>=65.0&&(int)pixel[0]<=75&&(int)pixel[1]>=45&&(int)pixel[1]<=55
       &&(int)pixel[2]>=40&&(int)pixel[2]<=50)
    {
        wandFly=true;
        generateSchool = true;//one for green, cube
    }
    else if ((int)pixel[0]==38&&(int)pixel[1]==35&&(int)pixel[2]==30)
    {
        openDoor = !openDoor;  //two for blue, cone
    }
    else if ((int)pixel[0]==(int)pixel[1] && (int)pixel[1]==(int)pixel[2])
    {
        openSpotLight = !openSpotLight;  //two for blue, cone
    }
    
    selecting=false;
    glutPostRedisplay();
}


void drawQuidditchBall(void){

    

    float ballColor[] = {241.0/255, 167.0/255, 69.0/255, 1.0};
    float wingColor[] = {1,0,0, 1.0};
    float matSpec[] = {1.0, 1.0, 1.0, 1.0};
    float matShine[] = {50.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ballColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glPushMatrix();
    //to the point where I want it to
    glTranslatef(13, 4, -13);
    
    glRotatef(quidditichBallAnl, 0, 1, 0);
    glTranslatef(0, 0, 1);
    //Main body
    glPushMatrix();
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
    //Left wing
    glPushMatrix();
    glRotatef(quidditichWingAnl, 1, 0, 0);
    glTranslatef(0, 0, 0.2);
    glScaled(0.6, 0, 1),
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();
    //Right Wind
    glPushMatrix();
    glRotatef(-quidditichWingAnl, 1, 0, 0);
    glTranslatef(0, 0, -0.2);
    glScaled(0.6, 0, 1),
    glutSolidSphere(0.1, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

void mouseControl(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN && button == GLUT_LEFT)
    {   selecting=true;
        xClick=x;
        yClick=height-y; //for screen vs mouse coordinates
        glutPostRedisplay();
       
    }
}

void drawHouse(){
    float matAmbAndDif1[] = {191.0/255, 177.0/255, 150.0/255, 1.0};
    float matAmbAndDif2[] = {0/255, 0/255, 0/255, 1.0};
    float matAmbAndDifTop[] = {100.0/255, 111.0/255, 118.0/255, 1.0};
    float matAmbAndDifMain[] = {200.0/255, 177.0/255, 143.0/255, 1.0};
    
    
 
    float matSpec[] = {1.0, 1.0, 1.0, 1.0};
    float matShine[] = {50.0};
    
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    
//    glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif1);
//    glMaterialfv(GL_BACK, GL_SPECULAR, matSpec);
//    glMaterialfv(GL_BACK, GL_SHININESS, matShine);
    glPushMatrix();
    glTranslatef(15, 4, -10);
    //Right Side 3210 -> 0123  n rows and n columns of triangles
    glBegin(GL_QUADS);
    for(int i = -4; i < 4; i++)
    {
        for(int j = -6;  j < 4; j++)
        {
            glNormal3f(-1, 0, 0.0);
           glVertex3f(4,i+1, j+1);
           glVertex3f(4,i+1, j);
           glVertex3f(4,i, j);
           glVertex3f(4,i, j+1);
        }
    }
    glEnd();
    
    //Back Side 67328
    glBegin(GL_QUADS);
    for(int i = -4; i < 4; i++)
    {
        for(int j = -4;  j < 4; j++)
        {
            glNormal3f(0, 0, 1);
           glVertex3f(i, j+1,-6);
           glVertex3f(i, j,-6);
           glVertex3f(i+1, j,-6);
           glVertex3f(i+1, j+1,-6);
        }
    }
    glEnd();
    
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1);
    glVertex3f(0.0, 6.0, -6.0);
    glVertex3f(-4.0, 4.0, -6.0);
    glVertex3f(4.0, 4.0, -6.0);
    glEnd();
    
    //Left Side 5476
    glBegin(GL_QUADS);
    for(int i = -4; i < 4; i++)
    {
        for(int j = -6;  j < 4; j++)
        {
            glNormal3f(1, 0, 0);
           glVertex3f(-4,i, j+1);
           glVertex3f(-4,i, j);
           glVertex3f(-4,i+1, j);
           glVertex3f(-4,i+1, j+1);
        }
    }
    glEnd();
    
    //left top side 9658 8569
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);   //need to be calculated
    glVertex3f(0.0, 6.0, 4.0);
    glVertex3f(-4.0, 4.0, 4.0);
    glVertex3f(-4.0, 4.0, -6.0);
    glVertex3f(0.0, 6.0, -6.0);
    glEnd();
    
    
    
    //right top side 9812 -> 2189
    glBegin(GL_POLYGON);
    glNormal3f(-1,0,0);  //need to be calculated
    glVertex3f(4.0, 4.0, -6.0);
    glVertex3f(4.0, 4.0, 4.0);
    glVertex3f(0.0, 6.0, 4.0);
    glVertex3f(0.0, 6.0, -6.0);
    glEnd();
    
    //front side 8 5 4 10 11 12 13 0 1
    //8 1 5
    glBegin(GL_POLYGON);
    glNormal3f(0,0,-1);  //need to be calculated
    glVertex3f(0.0, 6.0, 4.0);
    glVertex3f(4.0, 4.0, 4.0);
    glVertex3f(-4.0, 4.0, 4.0);
    glEnd();
    
    
    //1 15 14 5
    glBegin(GL_QUADS);
    for(int i = -4; i < 4; i++)
    {
        for(int j = 1;  j < 4; j++)
        {
            glNormal3f(0, 0, -1);
           glVertex3f(i+1, j+1,4);
           glVertex3f(i+1, j,4);
           glVertex3f(i, j,4);
           glVertex3f(i, j+1,4);
        }
    }
    glEnd();
    //11 10 4 14
    glBegin(GL_POLYGON);
    glNormal3f(0,0,-1);  //need to be calculated
    glVertex3f(-1.5,1,4);
    glVertex3f(-1.5,-4,4);
    glVertex3f(-4.0, -4.0, 4.0);
    glVertex3f(  -4,1,4);
    glEnd();
    //15 0 13 12
    glBegin(GL_POLYGON);
    glNormal3f(0,0,-1);  //need to be calculated
    glVertex3f(4,1,4);
    glVertex3f(4.0, -4.0, 4.0);
    glVertex3f(1.5,-4,4);
    glVertex3f(1.5,1,4);
    glEnd();
    
    //Bottom 4037
    glBegin(GL_QUADS);
    for(int i = -4; i < 4; i++)
    {
        for(int j = -6;  j < 4; j++)
        {
            glNormal3f(0.0, 1.0, 0.0);
           glVertex3f(i, -3.9, j);
           glVertex3f(i, -3.9, j+1);
           glVertex3f(i+1, -3.9, j+1);
           glVertex3f(i+1, -3.9, j);
        }
    }
    glEnd();
    
    //button
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glPushMatrix();
    glTranslatef(-4,0,0);
    glScaled(0.2, 0.2, 0.2);
    glColor3f(1,1,1);
    glutSolidCube(1);
    glPopMatrix();
    
    glPopMatrix();
}

void lookAt(){
    if(view == 0){
        //From top
        gluLookAt(15, 15, -10,
                  15,5,-10,
                  0,0,1);
    }
    else if(view == 1){
        //view from the north
        gluLookAt(15, 5, -28,
                  15,5,-10,
                  0,1,0);
    }
    else if(view == 2){
        //view from the south
        gluLookAt(15, 5, 8,
                  15,5,-10,
                  0,1,0);
    }
    else if(view == 3){
        //view from the west
        gluLookAt(-6, 5, -10,
                  15,5,-10,
                  0,1,0);
    }
    else if(view == 4){
        //view from the east
        gluLookAt(36, 5, -10,
                  15,5,-10,
                  0,1,0);
    }
    else{
        gluLookAt(meX, meY, meZ, meX + sin(angle * PI / 180) , meY + lookUp, meZ + cos(angle * PI / 180), 0, 1, 0);
    }
}

void drawTree(float x, float z){
    float matAmbAndDif1[] = {134.0/255, 68.0/255, 57.0/255, 1.0};
    float matAmbAndDif2[] = {100.0/255, 230.0/255, 150.0/255, 1.0};
    float matSpec[] = {1.0, 1.0, 1.0, 1.0};
    float matShine[] = {50.0};
    
    
    
    glPushMatrix();
    glTranslatef(x, 0, z);
    //root
    glPushMatrix();
    glTranslatef(0,1.5,0);
    glScalef(.5, 3, .5);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glutSolidCube(1);
    glPopMatrix();
    
    //Leaves
    glPushMatrix();
    glTranslatef(0,3,0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(2.5, 1, 20, 20);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,4,0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(2, 1, 20, 20);
    glPopMatrix();
    
    glPopMatrix();
}

void drawScene(void){
    // *********  x11Fix begin chunk
    if(scenex11WorkAround)
    {
        glutReshapeWindow(width-1,height-1);// Has to be different dimensions than in glutInitWindowSize();
        scenex11WorkAround = false;
    }
    //*********** x11Fix end chunk
    
    // Material property vectors.
    float lightPos0[] = { 0,0,0, 1.0 };
//    float lightPos1[] = { meX , meY - 1, meZ - 1, 1.0 };
    float matAmbAndDif1[] = {191.0/255, 177.0/255, 150.0/255, 1.0};
    float matAmbAndDif2[] = {157.0/255, 110.0/255, 94.0/255, 1.0};
    float matAmbAndDif3[] = {1, 1, 1, 1.0};
    float matAmbAndDif4[] = {38.0/255, 37.0/255, 39.0/255, 1.0};
    float matAmbAndDif5[] = {102.0/255, 51.0/255, 153.0/255, 1.0};
    //G
    float matAmbAndDif6[] = {92.0/255, 22.0/255, 116.0/255, 1.0};
    //H
    float matAmbAndDif7[] = {161.0/255, 150.0/255, 51.0/255, 1.0};
    //R
    float matAmbAndDif8[] = {27.0/255, 27.0/255, 86.0/255, 1.0};
    //S
    float matAmbAndDif9[] = {49.0/255, 78.0/255, 41.0/255, 1.0};
    float matAmbAndDif10[] = {1,0,0, 1.0};
    float matAmbAndDif11[] = {0.5,0.5, 1.0};
    
    float matSpec[] = {1.0, 1.0, 1.0, 1.0};
    float matShine[] = {50.0};
    float matShine1[] = {1.0};
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
//    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, t);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, t);
    
    //Set Projection
    setProjection();
    
    //Clear Modeview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    lookAt();
    glDisable(GL_LIGHTING);

    // Light0 and its sphere positioned.
//    glLightfv(GL_LIGHT0, GL_AMBIENT, matAmbAndDif1);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, matAmbAndDif1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, matSpec);
    glLightfv(GL_LIGHT0, GL_SHININESS, matShine1);
    
    
    //moon
    if(moonAppear){
        glEnable(GL_LIGHT2);
        glLightfv(GL_LIGHT2, GL_SPECULAR, matSpec);
        glLightfv(GL_LIGHT2, GL_SHININESS, matShine1);
        
        
    }
    else glDisable(GL_LIGHT2);
    
    glPushMatrix();
    glTranslatef(27, 11, -15);
    glColor3f(1.0, 1.0, 1.0);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos0);
    glutSolidSphere(2, 8, 8);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    

    
    if(!openSpotLight){
        glDisable(GL_LIGHT0);
    }else{
        //printf("%f-%f\n",camX,camZ);
        glEnable(GL_LIGHT0);
    }
    glPushMatrix();
    glTranslatef(15, 6, -11);
    glColor3f(1.0, 1.0, 1.0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glutSolidSphere(0.05, 8, 8);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    
    
    // Material properties of the house.
    
   
    
    drawHouse();
    drawDoor();
    
    glPushMatrix();
    glTranslatef(13,0,-13);
    drawTable(1, 1.5, 1.5, 0.1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(17,0,-13);
    drawTable(1, 1.5, 1.5, 0.1);
    glPopMatrix();

    
   
    
    //Draw the ground
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matAmbAndDif2);
    drawGround();
    
    
    drawTree(7,-1);
    drawTree(7,-5);
    drawTree(7,-10.5);
    drawTree(7,-16);
    drawTree(4.5,-1);
    drawTree(4.5,-5);
    drawTree(4.5,-10.5);
    drawTree(4.5,-16);
    drawTree(22,-1);
    drawTree(22,-5);
    drawTree(22,-10.5);
    drawTree(22,-16);
    drawTree(27.5,-1);
    drawTree(27.5,-5);
    drawTree(27.5,-10.5);
    drawTree(27.5,-16);
    
    
    
    drawQuidditchBall();
    
    float spot_dir1[3] = {0, 0, -1};
    
    //手电筒
    
    if(openFlashLight) glEnable(GL_LIGHT1);
    else glDisable(GL_LIGHT1);
    
    glPushMatrix();

    if(pickFlashLight){
        glTranslatef(meX  , meY - 1, meZ - 2);
        glTranslatef(0,0,2);
        glRotatef(angle -180, 0 , 1, 0);
        glTranslatef(0,0,-2);
    }
    else{
        glTranslatef(13  , 1.2, -13);
    }
//    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
    float lightPos1[] = {0,0,0,1};
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, matSpec);
//    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidSphere(0.1, 20, 20);
    glTranslatef(0, 0, 0.15);
    glScaled(0.1, 0.1, 0.3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif4);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif4);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);//??手把颜色不对
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine1);
    glutSolidCube(1);
    glPopMatrix();
    
    
   
    
    
    
    //Sorting hat
    glPushMatrix();
    glTranslatef(17, 1,-13);
     //Base of the sorting hat
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glColor3f(0.0, 0.4, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif5);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    glutSolidCone(0.5, 1, 50, 10);
    glPopMatrix();
     
     //Top of the sorting hat
    glPushMatrix();
    glTranslatef(0, 1, 0);
    if(hatTop){
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif11);
         glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
         glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    }
    else{
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matSpec);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
        glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    }
    glutSolidSphere(0.1, 40, 40);
    glPopMatrix();
    
    glPushMatrix();
    
        if(wandFly){
            glRotatef(wandAng, 0, 1, 0);
            wandAng += 1;
    //            printf("%d\n",wandAng);
            glTranslatef(0, 2, 0);
            glRotatef(90, 1, 0, 0);
        }
        
        
        //wand
        glPushMatrix();
        glTranslatef(0, 0.4, 0.6);
        glScalef(0.1, 0.8, 0.1);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif2);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
        glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
        glutSolidCube(1);
        glPopMatrix();
        //wandEnd
        glPushMatrix();
        glTranslatef(0, 0.81, 0.6);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif10);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
        glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
        glutSolidSphere(0.1, 20, 20);
        glPopMatrix();

        glPopMatrix();
    glPopMatrix();
    
    
    if(generateSchool){
        int n = rand() % 4;
        if(n == 0) printf("The correct answer is Gryffindor!\n");
        else if(n == 1) printf("The correct answer is Hufflepuff!\n");
        else if(n == 2) printf("The correct answer is Ravenclaw!\n");
        else printf("The correct answer is Slytherin!\n");
        generateSchool = false;
    }
    
    
    if(wandFly && choose == 0 && wandAng > 720){
        glPushMatrix();
        glTranslatef(11.5, 4, -14);
        char divide[] = "Gryffindor Hufflepuff Ravenclaw or Slytherin?";
        glScalef(0.0025, 0.004, 0.004);
        writeStrokeString(GLUT_STROKE_ROMAN, divide);
        
        
        
        glPopMatrix();
        
        
        
    }
    
   
    //怎么变字体颜色。怎么先转再显示字体
    if(choose == 1){
        glPushMatrix();
        glTranslatef(13, 4, -14);
        char words[] = "Welcome to Gryffindor!";
        glScalef(0.0025, 0.004, 0.004);
//        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif6);
//        glMaterialfv(GL_FRONT, GL_SPECULAR, matAmbAndDif6);
//        glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
        writeStrokeString(GLUT_STROKE_ROMAN, words);
        glPopMatrix();
    }
    else if(choose == 2){
        glPushMatrix();
        glTranslatef(14, 4, -14);
        char words[] = "Good Choice!";
        glScalef(0.0025, 0.004, 0.004);
        writeStrokeString(GLUT_STROKE_ROMAN, words);
        glPopMatrix();
    }
    else if(choose == 3){
        glPushMatrix();
        glTranslatef(12, 4, -14);
        char words[] = "Seems like it is a good choice!";
        glScalef(0.0025, 0.004, 0.004);
        writeStrokeString(GLUT_STROKE_ROMAN, words);
        glPopMatrix();
    }
    else if(choose == 4){
        glPushMatrix();
        glTranslatef(12, 4, -14);
        char words[] = "You are a talented wizard!";
        glScalef(0.003, 0.004, 0.004);
        writeStrokeString(GLUT_STROKE_ROMAN, words);
        glPopMatrix();
    }
    
    
    
    if(selecting) getID(xClick, yClick);
    
    
    

    
    
    glutSwapBuffers();
    
    
}



void animate(int f){
    if(openSpotLight){
        hatTop = !hatTop;
        quidditichBallAnl += 1;
        quidditichWingAnl += 15;

    }
    if(!openDoor){
        if(doorX < 2.2) {
            doorX+=0.05;
        }
    }
    else{
        if(doorX > 0.75) {
            doorX-=0.05;
        }
    }
    if(wandFly) wandAng+=1;
//    printf("%d\n", wandAng);
    glutPostRedisplay();
    glutTimerFunc(20, animate, 0);
}


void keyInput(unsigned char key, int x, int y)
{
   switch(key)
   {
       case 27:
           exit(0);
           break;
       case '0':
           view = 0;
           glutPostRedisplay();
           break;
       case'1':
           view = 1;
           glutPostRedisplay();
           break;
       case'2':
           view = 2;
           glutPostRedisplay();
           break;
       case'3':
           view = 3;
           glutPostRedisplay();
           break;
       case'4':
           view = 4;
           glutPostRedisplay();
           break;
       case'5':
           view = 5;
           glutPostRedisplay();
           break;
       case 'l':
           openSpotLight=!openSpotLight;
           glutPostRedisplay();
           break;
       case 'd':
           openDoor=!openDoor;
           glutPostRedisplay();
           break;
       case 'f':
           openFlashLight=!openFlashLight;
           glutPostRedisplay();
           break;
       case 's':
           pickFlashLight=!pickFlashLight;
           glutPostRedisplay();
           break;
       case 'w':
           wandFly=!wandFly;
           generateSchool = true;
           glutPostRedisplay();
           break;
       case 'g':
           choose=1;
           glutPostRedisplay();
           break;
       case 'h':
           choose=2;
           glutPostRedisplay();
           break;
       case 'r':
           choose=3;
           glutPostRedisplay();
           break;
       case 'n':
           choose=4;
           glutPostRedisplay();
           break;
       case '+':
           lookUp +=.2;
           glutPostRedisplay();
           break;
       case '-':
           lookUp -=.2;
           glutPostRedisplay();
           break;
   }
}

void specialKeyInput(int key, int x, int y)
{
    switch(key){
        case GLUT_KEY_UP: //forward
            meZ += stepsize * cos(angle * PI / 180)/2;
            meX += stepsize * sin(angle * PI / 180)/2;
//            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN: //back
            meZ -= stepsize * cos(angle * PI / 180)/2;
            meX -= stepsize * sin(angle * PI / 180)/2;
            break;
        case GLUT_KEY_RIGHT: //turn right
            angle -= turnsize;
            break;
        case GLUT_KEY_LEFT: //turn left
            angle += turnsize;
            break;
    }//end switch
    glutPostRedisplay();
}
void menu(int id){
    if(id == 2) exit(0);
    if(id == 1) moonAppear = !moonAppear;
    glutPostRedisplay();
}

void makeMenu(void){
    glutCreateMenu(menu);
    glutAddMenuEntry("Moon", 1);
    glutAddMenuEntry("Quit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
}


int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sorting Hat");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(mouseControl);
    glutSpecialFunc(specialKeyInput);
    glutTimerFunc(20, animate, 0);
    makeMenu();

    
    
    glutMainLoop();

    return 0;
}
