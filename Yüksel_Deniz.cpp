
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800

#define TIMER_PERIOD  1000/60 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532




/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
int r, g, b;
typedef struct {
    int x;

    int y;
}pel_t;

pel_t pelikans[10];
int x_mouse, y_mouse;

bool activeTimer = false;


int pelikan_no = 0;
//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}





void gemi(int x,int y) {
    glColor3ub(204, 102, 0);
    glRectf(x, y,x+ 90,y+ 30);

    glColor3ub(204, 102, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 90, y + 0);
    glVertex2f(x + 120, y + 30);
    glVertex2f(x + 90, y + 30);
    glEnd();
    glColor3ub(204, 102, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x + -30, y + 30);
    glVertex2f(x + 0, y + 30);
    glEnd();
    
    glColor3ub(204, 102, 0);
    glRectf(x+43, y,x+ 47, y+120);
    


    glColor3ub(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 48, y + 37);
    glVertex2f(x + 48, y + 120);
    glColor3ub(g, b, r);
    glVertex2f(x + 90, y + 37);
    glEnd();

    glColor3ub(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 43, y + 37);
    glVertex2f(x + 43, y + 120);
    glColor3ub(b, r, g);
    glVertex2f(x + 0,y+ 37);
    glEnd();

}


void pelikan(int x,int y) {
    glLineWidth(3);
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y);
    glVertex2f(x, y+-120);
    glVertex2f(x+10, y+-120);
    glEnd();

 
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y);
    glVertex2f(x+-50, y+-60);
    glVertex2f(x+30, y+-60);
    glVertex2f(x+35, y+-65);
    glEnd();

    glLineWidth(1);
    
    glColor3ub(255, 20, 147);
    circle(x, y, 30);

    glColor3ub(199, 21, 133);
    glBegin(GL_QUADS);
    glVertex2f(x+0, y+5);
    glVertex2f(x+-80, y+5);
    glVertex2f(x+-20, y+25);
    glVertex2f(x+10, y+18);
    glEnd();

    glColor3ub(255, 182, 203);
    glBegin(GL_QUADS);
    glVertex2f(x + 30, y + -10);
    glVertex2f(x + -5, y + 100);
    glVertex2f(x + 10, y + 90);
    glVertex2f(x + 35, y + 10);
    glEnd();

    glColor3ub(255, 191, 203);
    glBegin(GL_QUADS);
    glVertex2f(x + -5, y + 100);
    glVertex2f(x + 15, y + 120);
    glVertex2f(x + 20, y + 110);
    glVertex2f(x + 10, y + 90);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(x + 20, y + 110);
    glVertex2f(x + 30, y + 95);
    glVertex2f(x + 24, y + 92);
    glVertex2f(x + 13, y + 95);
    glEnd();
    glColor3ub(255, 20, 147);
    circle(x+15, y+110,2);


   glBegin(GL_TRIANGLES);

    glColor3f(1, 1, 0);

    glVertex2f(x+30, y+95);
    glVertex2f(x+28, y+82);
    glVertex2f(x+24, y+92);

    glEnd();




}
void cloud(int x, int y)
{
    glColor3f(1.0, 1.0, 1.0);
    circle(x, y + 50, 25);
    circle(x + 20, y + 30, 25);
    circle(x + 10, y + 30, 25);
    circle(x + -20, y + 30, 25);
    circle(x + -10, y + 30, 30);
}
void display() {
    //
    // clear window to black
    //
    glClearColor(135.0/255, 206.0/255, 250.0/255, 0);
    glClear(GL_COLOR_BUFFER_BIT);

  

    glColor3ub(0, 191, 255);
    glBegin(GL_QUADS);
    glVertex2f(-500  ,   -400);
    glVertex2f(500, -400);
    glColor3ub(0, 0, 255);
    glVertex2f(500,   -60);
    glVertex2f(-500,   -60);
    glEnd();

    glColor3f( 1, 1, 0 ) ;
   circle( 400, 350, 30 ) ;
   
   glLineWidth(5);
   glColor3f(0, 0, 0);
   glBegin(GL_LINE_STRIP);
   glVertex2f(-100, 350);
   glVertex2f(-100, 390);
   glVertex2f( 100, 390);
   glVertex2f(100, 350);
   glVertex2f(-100, 350);
   glEnd();

   glLineWidth(1);
   glColor3f(0, 0, 1);
   glRectf(-100, +350, +100, +390);
   glColor3f(1, 1, 1);
   vprint2(-40, +375, 0.1, "Deniz Yuksel");
   vprint2(-35, +360, 0.1, "21803358");
  
   
   cloud(-200, 300);
   cloud(250, 250);
   cloud(-150, 175);
   cloud(20, 180);
   cloud(-350, 250);
   
  

   gemi(-350, -100);
   gemi(-380, -300);
   gemi(-180, -150);
   gemi(0, -250);
   gemi(100, -350);
   gemi(200, -125);
   gemi(350, -310);

   for (int i = 0; i < pelikan_no; i++) {
       pelikan(pelikans[i].x, pelikans[i].y);
       vprint2(pelikans[i].x -2, pelikans[i].y -4, 0.1, "%d", i + 1);
   }

   glColor3ub(0, 0, 0);
   vprint2(winWidth / 2 - 100, -winHeight / 2 + 10, 0.1, "(%d, %d)", x_mouse, y_mouse);

    glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_F1: activeTimer = !activeTimer; break;
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
    
    // Write your codes here.
    if (stat == GLUT_DOWN)
        switch (button) {
        case GLUT_LEFT_BUTTON: {
            r = rand() % 256;
            g = rand() % 256;
            b = rand() % 256;

            bool checkplk = false;
            for (int i = 0; i < pelikan_no; i++)

                if (abs(x_mouse - pelikans[i].x) < 150 && abs(y_mouse - pelikans[i].y) < 75) {
                    checkplk = true;
                    break;
                }
            if (pelikan_no < 10 && !checkplk && y_mouse > 0 && y_mouse < 400 && y_mouse && x_mouse > -500 && x_mouse < 500) {
                pelikans[pelikan_no].x = x_mouse;
                pelikans[pelikan_no].y = y_mouse;
                pelikan_no++;
            }
            else
                printf("pelikans cannot swim\n");
            break;
        }
        }



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.
 

    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.
    x_mouse = x - winWidth / 2;
    y_mouse = winHeight / 2 - y;


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    // Write your codes here.
    if (activeTimer) {
        for (int i = 0; i < pelikan_no; i++)
            if (pelikans[i].x < WINDOW_WIDTH / 2 + 60)
                pelikans[i].x += 3;
            else
                pelikans[i].x = -WINDOW_WIDTH / 2 - 120;
    }


    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}
#endif

void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Homework-1");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    srand(time(0));
#endif

    Init();

    glutMainLoop();
}