#include <bits/stdc++.h>
#include <GL/glut.h>
using namespace std;
#define CYAN  0.529412, 0.907843, 0.921569//0.529412, 0.807843, 0.980392 //0, 191, 255
#define ORAGE 0.647059,0.164706,0.164706
#define BROWN 0.627451,0.321569,0.176471 // 1.0, 0.2, 0.2
#define GRAY  0.4, 0.5, 0.5
#define GREEEN 0.0, 0.6, 0.0
#define WHITE 0.9, 0.9, 0.8
// window size (side)
int win_size = 600;
int shad[36];
// position of camera
float x = 0, y = 1.0, z = 5;
float ua=0,ub=y,uc=0;
float ratio = 0.1f;

// look-at perspective to camera position
float l_x = 0, l_y = 0, l_z = -1;

// angle for rotation
float angle_xz = 0,beta=0;

// ground's size (side)
float ground_x = 30, ground_z = 30;

float colo [10][3] = {{0.5, 0.7, 0.4},  // lime GREEEN
                      {0.6, 0.4, 0.0},  // GREEEN
                      {0.5, 0.4, 0.4},  // yellow
                      {0.2, 0.4, 0.4},
                      {0.854902,0.647059, 0.12549},
                      {0.7, 0.3, 0.3},
                      {0.5, 0.5, 0.3},
                      {0.341176, 0.601961, 0.301961},
                      {0.741176,0.717647,0.419608},
                      {0.8, 0.5, 0.1}};

int co=0;
void drawArena () {
    glBegin (GL_QUADS); {
        glColor3f (GREEEN);
        glVertex3f ( 2.00, 0.0150,  2.00);
        glVertex3f (-2.00, 0.0150,  2.00);
        glVertex3f (-2.00, 0.0150, -2.00);
        glVertex3f ( 2.00, 0.0150, -2.00);

        glColor3f (WHITE);
        glVertex3f ( 2.90, 0.010,  2.90);
        glVertex3f (-2.90, 0.010,  2.90);
        glVertex3f (-2.90, 0.010, -2.90);
        glVertex3f ( 2.90, 0.010, -2.90);
    }     glEnd ();
}

void drawFence()
{
    glBegin(GL_QUADS); {

        //right
        glColor3f (BROWN);
        glVertex3f ( 2.9, 0.5,  2.9);
        glVertex3f ( 2.9, 0.5, -2.9);
        glVertex3f ( 2.9, 0.02, -2.9);
        glVertex3f ( 2.9, 0.02,  2.9);

        //back
        glColor3f (BROWN);
        glVertex3f ( 2.9, 0.5, -2.9);
        glVertex3f (-2.9, 0.5, -2.9);
        glVertex3f (-2.9, 0.02, -2.9);
        glVertex3f ( 2.9, 0.02, -2.9);

        //left
        glColor3f (BROWN);
        glVertex3f (-2.9, 0.5,  2.9);
        glVertex3f (-2.9, 0.5, -2.9);
        glVertex3f (-2.9, 0.02, -2.9);
        glVertex3f (-2.9, 0.02,  2.9);

        //front
        glColor3f (BROWN);
        glVertex3f ( 2.9, 0.5, 2.9);
        glVertex3f ( 0.3, 0.5, 2.9);
        glVertex3f ( 0.3, 0.02, 2.9);
        glVertex3f ( 2.9, 0.02, 2.9);

        glColor3f (BROWN);
        glVertex3f ( -2.9, 0.5, 2.9);
        glVertex3f ( -0.3, 0.5, 2.9);
        glVertex3f ( -0.3, 0.02, 2.9);
        glVertex3f ( -2.9, 0.02, 2.9);

    } glEnd();
}
void drawLine () {
    glBegin (GL_QUADS); {
        glColor3f (WHITE);
        glVertex3f ( 1.3, 0.015,  5.3);
        glVertex3f (-1.3, 0.015,  5.3);
        glVertex3f (-1.3, 0.015,  5.1);
        glVertex3f ( 1.3, 0.015,  5.1);

        glColor3f (WHITE);
        glVertex3f ( 5.3, 0.01,  1.3);
        glVertex3f ( 5.1, 0.01,  1.3);
        glVertex3f ( 5.1, 0.01, -1.3);
        glVertex3f ( 5.3, 0.01, -1.3);
    }     glEnd ();
}

void designFloor (float h,int flag) {
    glBegin (GL_QUADS); {
        // top side
        glColor3f(colo[flag][0],colo[flag][1],colo[flag][2]);
        glVertex3f ( 1.0, 1.0 + h, -1.0);
        glVertex3f (-1.0, 1.0 + h, -1.0);
        glVertex3f (-1.0, 1.0 + h,  1.0);
        glVertex3f ( 1.0, 1.0 + h,  1.0);

        // bottom side
        glVertex3f ( 1.0, 0.0 + h,  1.0);
        glVertex3f (-1.0, 0.0 + h,  1.0);
        glVertex3f (-1.0, 0.0 + h, -1.0);
        glVertex3f ( 1.0, 0.0 + h, -1.0);

        // front side
        glVertex3f ( 1.0, 1.0 + h, 1.0);
        glVertex3f (-1.0, 1.0 + h, 1.0);
        glVertex3f (-1.0, 0.0 + h, 1.0);
        glVertex3f ( 1.0, 0.0 + h, 1.0);

        // door
        glColor3f (0.25,0.25,0.24);
        //front window1
        glVertex3f ( 0.3, 0.75 + 0, 1.0111);
        glVertex3f (-0.3, 0.75 + 0, 1.0111);
        glVertex3f (-0.3, 0 + 0, 1.0111);
        glVertex3f ( 0.3, 0 + 0, 1.0111);

        //front windows
        if(h!=0)
        {
            glColor3f (0.25,0.25,0.24);
            //right window
            glVertex3f ( 0.75, 0.75 + h, 1.0111);
            glVertex3f ( 0.25, 0.75 + h, 1.0111);
            glVertex3f ( 0.25, 0.25 + h, 1.0111);
            glVertex3f ( 0.75, 0.25 + h, 1.0111);
            //left window
            glVertex3f ( -0.25, 0.75 + h, 1.0111);
            glVertex3f ( -0.75, 0.75 + h, 1.0111);
            glVertex3f ( -0.75, 0.25 + h, 1.0111);
            glVertex3f ( -0.25, 0.25 + h, 1.0111);
        }
        //back windows
        if(h!=0)
        {
            glColor3f (0.25,0.25,0.24);
            //right window
            glVertex3f ( 0.75, 0.75 + h, -1.0111);
            glVertex3f ( 0.25, 0.75 + h, -1.0111);
            glVertex3f ( 0.25, 0.25 + h, -1.0111);
            glVertex3f ( 0.75, 0.25 + h, -1.0111);
            //left window
            glVertex3f ( -0.25, 0.75 + h, -1.0111);
            glVertex3f ( -0.75, 0.75 + h, -1.0111);
            glVertex3f ( -0.75, 0.25 + h, -1.0111);
            glVertex3f ( -0.25, 0.25 + h, -1.0111);
        }
        //front window2
        glColor3f(colo[flag][0],colo[flag][1],colo[flag][2]);
        glVertex3f ( 1.0, 0.0 + h, -1.0);
        glVertex3f (-1.0, 0.0 + h, -1.0);
        glVertex3f (-1.0, 1.0 + h, -1.0);
        glVertex3f ( 1.0, 1.0 + h, -1.0);

        // left side
        glVertex3f (-1.0, 1.0 + h,  1.0);
        glVertex3f (-1.0, 1.0 + h, -1.0);
        glVertex3f (-1.0, 0.0 + h, -1.0);
        glVertex3f (-1.0, 0.0 + h,  1.0);

        // right side
        glVertex3f (1.0, 1.0 + h, -1.0);
        glVertex3f (1.0, 1.0 + h,  1.0);
        glVertex3f (1.0, 0.0 + h,  1.0);
        glVertex3f (1.0, 0.0 + h, -1.0);
    } glEnd();
}

void designBuilding (int x, int y, int flag) {
    x = (x == 0 ? 11 : x);
    y = (y == 0 ? 5 : y);

    // floor_cnt => [0, 3)
    int floor_cnt = (x * y) % 5;
    if (floor_cnt < 0) floor_cnt += 5;
    floor_cnt += 3;
    int col=5;
    // randomly choose the no. of floors in a house
    for (int i = 0; i < floor_cnt; ++i)
        designFloor (i,flag);
}

void designFloor () {
    glColor3f (GRAY);

    glBegin (GL_QUADS);
    glVertex3f (-ground_x + 5, 0, -ground_z + 5);
    glVertex3f (-ground_x + 5, 0,  ground_z + 5);
    glVertex3f ( ground_x + 5, 0,  ground_z + 5);
    glVertex3f ( ground_x + 5, 0, -ground_z + 5);
    glEnd ();
}

void drawCityfence()
{
    glColor3f (ORAGE);

    //left
    glBegin (GL_QUADS);
    glVertex3f (-ground_x + 5.1,  1.5, -ground_z + 5);
    glVertex3f (-ground_x + 5.1, 0.01, -ground_z + 5);
    glVertex3f (-ground_x + 5.1,  1.5,  ground_z + 5);
    glVertex3f (-ground_x + 5.1, 0.01,  ground_z + 5);

    //right
    glBegin (GL_QUADS);
    glVertex3f (ground_x + 5,  1.5, -ground_z + 5);
    glVertex3f (ground_x + 5, 0.01, -ground_z + 5);
    glVertex3f (ground_x + 5,  1.5,  ground_z + 5);
    glVertex3f (ground_x + 5, 0.01,  ground_z + 5);

    //front
    glBegin (GL_QUADS);
    glVertex3f ( ground_x + 5,  1.5,  ground_z + 5);
    glVertex3f (-ground_x + 5, 0.01,  ground_z + 5);
    glVertex3f (-ground_x + 5,  1.5,  ground_z + 5);
    glVertex3f ( ground_x + 5, 0.01,  ground_z + 5);

    //back
    glBegin (GL_QUADS);
    glVertex3f ( ground_x + 5.1,  1.5, -ground_z + 5);
    glVertex3f (-ground_x + 5.1, 0.01, -ground_z + 5);
    glVertex3f (-ground_x + 5.1,  1.5, -ground_z + 5);
    glVertex3f ( ground_x + 5.1, 0.01, -ground_z + 5);

    glEnd ();
}

void changeSize (int w, int h) {
    h = (h > 0 ? h : 1);
    float asc_ratio = (w * 1.0) / h;
    // use the Projection Matrix
    glMatrixMode (GL_PROJECTION);
    // reset Matrix
    glLoadIdentity ();
    // set the viewport to be the entire window
    glViewport (0, 0, w, h);
    // set the correct perspective.
    gluPerspective (45.0, asc_ratio, 0.1, 500.0);
    // get back to the modelview
    glMatrixMode (GL_MODELVIEW);
}
int fl=0;
void display_city () {
    // clear color and depth buffers
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw sky
    glClearColor (CYAN, 0);

    // reset transformations
    glLoadIdentity ();

    // set the camera
    gluLookAt (x,          y,          z, // camera position
              x + l_x, y + l_y, z + l_z, // look at
              ua,          ub,          uc); // up

    designFloor ();
    drawCityfence();
    int flag=0;
    for (int i = -2; i < 4; i++) {
        for (int j = -2; j < 4; j++) {
            glPushMatrix (); {
                glTranslatef (i * 10.0, 0, j * 10.0);
                drawArena ();
                drawFence();
                drawLine();
                designBuilding (i, j, shad[fl]);
            } glPopMatrix ();
            flag=(flag+1)%6;
            fl=(fl+1)%36;
        }
    }

    glutSwapBuffers ();
}
double p,q,r;
void get()
{
    float u1, u2, u3, v1, v2, v3;
    u1 = x-l_x;
    u2 = y-l_y;
    u3 = z-l_z;
    v1 = 0;
    v2 = 1;
    v3 = 0;

    float uvi, uvj, uvk;
    uvi = u2 * v3 - v2 * u3;
    uvj = v1 * u3 - u1 * v3;
    uvk = u1 * v2 - v1 * u2;
    p = uvi;
    q = uvj;
    r = uvk;
}

void get2()
{
    float u1, u2, u3, v1, v2, v3;
    v1 = x-l_x;
    v2 = y-l_y;
    v3 = z-l_z;
    u1 = p;
    u2 = q;
    u3 = r;

    float uvi, uvj, uvk;
    uvi = u2 * v3 - v2 * u3;
    uvj = v1 * u3 - u1 * v3;
    uvk = u1 * v2 - v1 * u2;
    ua = uvi;
    ub = uvj;
    uc = uvk;
}

void shiftMode (unsigned char key, int _x, int _y) {
//    float ratio = 0.1f;
    switch (key) {
        case '1'://For Side View
            // set default values
            x = 0, y = 1.0, z = 5;
            l_x = 0, l_y = 0, l_z = -1;
            angle_xz = 0;
            z = 70;
            break;
        case '2'://For Top View
            // set default values
            x = 0, y = 0, z = 21;
            l_x = 0, l_y = 0, l_z = -1;
            angle_xz = 0;
            y = 70; l_y = -5;
            break;
        case '3': //Return to Main View
            // set default values
            x = 0, y = 1.0, z = 5;
            ratio=0.1f;
            beta=0.0f;
            l_x = 0, l_y = 0, l_z = -1;
            ua=0,ub=y,uc=0;
            angle_xz = 0.0f;
            break;
        case '7':
            y += 0.5*ratio;
            break;
        case '4':
            if(y>0.5)
                y -= 0.5*ratio;
            else
                y=0.5;
            break;
        case '6':
            beta-= .01;
            l_y = sin (beta);
            l_z = -cos (beta);
            get();
            get2();
            break;
        case '9':
            beta+= .01;
            l_y = sin (beta);
            l_z = -cos (beta);
            get();
            get2();
            break;
        case 'a':
            if(ratio<1.0f)
                ratio+=0.1f;
            if(angle_xz<0.1f)
                angle_xz+=0.01f;
            break;
        case 'd':
            if(ratio>0.2f)
                ratio-=0.1f;
            if(angle_xz>0.1f)
                angle_xz-=0.01f;
            break;
    }
}
void keyFun (int keytype, int _x, int _y) {
//    float ratio = 0.1f;

    switch (keytype) {
        case GLUT_KEY_LEFT :
            angle_xz -= .01;
            l_x =  sin (angle_xz);
            l_z = -cos (angle_xz);
            break;
        case GLUT_KEY_RIGHT :
            angle_xz += .01;
            l_x =  sin (angle_xz);
            l_z = -cos (angle_xz);
            break;
        case GLUT_KEY_UP :
            x += l_x * ratio;
            z += l_z * ratio;
            break;
        case GLUT_KEY_DOWN :
            x -= l_x * ratio;
            z -= l_z * ratio;
            break;


    }
}


int main (int argc, char **argv) {
    srand(time(NULL));
    for(int i=0;i<36;i++)
        shad[i]=rand()%10;
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (2 * win_size, win_size);
    glutCreateWindow ("Graphics Lab Project");

    // register callbacks
    glutDisplayFunc (display_city);
    glutReshapeFunc(changeSize);
    glutIdleFunc (display_city);
    glutSpecialFunc (keyFun);
    glutKeyboardFunc (shiftMode);

    glEnable (GL_DEPTH_TEST);
    glutMainLoop ();
    return 0;
}
