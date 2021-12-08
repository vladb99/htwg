#include <stdlib.h>

// Sample code for ‹bung 2

#include "vec.h"
#include "mat.h"
#include <cmath>

// might be you have to swith to
// #include "glut.h" depending on your GLUT installation
// #include "Uebung2/Uebung2/glut.h"
#include "GLUT/glut.h"

////////////////////////////////////////////////////////////
//
// system relevant global variables
//

// window width and height (choose an appropriate size)
const int g_iWidth  = 1000;
const int g_iHeight = 1000;

// global variable to tune the timer interval
int g_iTimerMSecs;

//
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// private, global variables ... replace by your own ones
//
// some global state variables used to describe ...
float g_iPos;        // ... position and ...
float g_iPosIncr;    // ... position increment (used in display1)

CVec2i g_vecPos;        // same as above but in vector form ...
CVec2i g_vecPosIncr;    // (used in display2)

float earth_angle_step ;
float moon_angle_step;


//
/////////////////////////////////////////////////////////////

// Eine �beraus primitive Punktklasse
class Point {
public:
    
    Point (float x=0, float y=0) {
        this->x = x;
        this->y = y;
    }
    
    float x, y;
};

// Eine �beraus primitive Farbklasse
class Color {
public:
    
    Color (float r=1.0f, float g=1.0f, float b=1.0f) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    float r, g, b;
};

Point earth_pos;
Point sun_pos;
Point moon_pos;

int sun_to_earth ;
int earth_to_moon ;

int sun_r;
Color sun_color;

int earth_r;

Color earth_color;

int moon_r;
Color moon_color;

// function to initialize our own variables
void init ()
{
    
    // init timer interval
    g_iTimerMSecs = 10;
    
    earth_pos = Point(300, 0);
    sun_pos = Point(0, 0);
    moon_pos = Point(400, 0);
    
    
    sun_to_earth = sun_pos.x - earth_pos.x;
    earth_to_moon = earth_pos.x - moon_pos.x;
    // init variables for display1
    g_iPos     = 0;
    g_iPosIncr = 2;
    
    // init variables for display2
    int aiPos    [2] = {0, 0};
    int aiPosIncr[2] = {2, 2};
    g_vecPos.setData (aiPos);
    g_vecPosIncr.setData (aiPosIncr);
    
    earth_angle_step = 180;
    moon_angle_step = 0;
    
    sun_r = 100;
    sun_color = Color(255, 200, 0);

    earth_r = 40;

    earth_color = Color(0, 100, 255);

    moon_r = 20;
    moon_color = Color(100, 100, 100);
}

// function to initialize the view to ortho-projection
void initGL ()
{
    glViewport (0, 0, g_iWidth, g_iHeight);    // Establish viewing area to cover entire window.
    
    glMatrixMode (GL_PROJECTION);            // Start modifying the projection matrix.
    glLoadIdentity ();                        // Reset project matrix.
    glOrtho (-g_iWidth/2, g_iWidth/2, -g_iHeight/2, g_iHeight/2, 0, 1);    // Map abstract coords directly to window coords.
    
    // tell GL that we draw to the back buffer and
    // swap buffers when image is ready to avoid flickering
    glDrawBuffer (GL_BACK);
    
    // tell which color to use to clear image
    glClearColor (0,0,0,1);
}


int min (int a, int b) { return a>b? a: b; }
// timer callback function
void timer (int value)
{
    ///////
    // update your variables here ...
    //
    
    int size2 = min (g_iWidth, g_iHeight) / 2;
    
    // variables for display1 ...
    if (g_iPos<=-size2 || g_iPos>=size2) g_iPosIncr = -g_iPosIncr;
    g_iPos += g_iPosIncr;
    
    // variables for display2 ...
    if (g_vecPos(1)<=-size2 || g_vecPos(1)>=size2) g_vecPosIncr = -g_vecPosIncr;
    g_vecPos += g_vecPosIncr;
    
    //
    ///////
    
    // the last two lines should always be
    glutPostRedisplay ();
    glutTimerFunc (g_iTimerMSecs, timer, 0);    // call timer for next iteration
}

void drawSymetricPoints(int x, int y, Color c, int px, int py) {
    glVertex2i((x+px), y+py);
    glVertex2i(-x+px, y+py);
    glVertex2i(-x+px, -y+py);
    glVertex2i((x+px), -y+py);
}

void bhamCircle (Point p, int r, Color c) {
    glBegin (GL_QUADS);
    glColor3f (c.r, c.g, c.b);
    
    int x = 0;
    int y = r;
    int d = 5 - 4 * r;
    int delta_se = 0;
    int delta_e = 0;
    
    drawSymetricPoints(x, y, c, p.x, p.y);
    drawSymetricPoints(y, x, c, p.x, p.y);
    // Mittelpunkt
    //glVertex2i(p.x, p.y);
    
    while (y > x) {
        if (d >= 0) {
            delta_se = 4*(2*(x-y)+5);
            d += delta_se;
            x++;
            y--;
        } else {
            delta_e = 4*(2*x+3);
            d += delta_e;
            x++;
        }
        drawSymetricPoints(x, y, c, p.x, p.y);
        drawSymetricPoints(y, x, c, p.x, p.y);
    }
    glEnd ();
}

Point move(Point ref, int distance, float angle) {
    float new_x = ref.x + distance * cos(angle*M_PI/180);
    float new_y = ref.y + distance * sin(angle*M_PI/180);
    Point new_position = Point(new_x, new_y);
    return new_position;
}

// display callback function
void display1 (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    
    bhamCircle(sun_pos, sun_r, sun_color);
    bhamCircle(earth_pos, earth_r, earth_color);
    bhamCircle(moon_pos, moon_r, moon_color);
    
    earth_pos = move(sun_pos, sun_to_earth, earth_angle_step += 1);
    moon_pos = move(earth_pos, earth_to_moon, moon_angle_step += 7);
    
    if(earth_angle_step > 360 ) {earth_angle_step -= 360;}
    if(moon_angle_step > 360 ) {moon_angle_step -= 360;}
    
    glFlush ();
    glutSwapBuffers (); // swap front and back buffer
}

CMat3f translation(Point t, bool inverted) {
    CMat3f matrix = CMat3f();
    for (int i = 0; i < 3; i++) {
        matrix.set(i, i, 1);
    }
    if (inverted) {
        matrix.set(0, 2, -t.x);
        matrix.set(1, 2, -t.y);
    } else {
        matrix.set(0, 2, t.x);
        matrix.set(1, 2, t.y);
    }
    return matrix;
}

CVec3f homonize(Point p) {
    CVec3f vector = CVec3f();
    float data[3] = {static_cast<float>(p.x), static_cast<float>(p.y), 1};
    vector.setData(data);
    return vector;
}

CMat3f rotation(float angle) {
    CMat3f matrix = CMat3f();
    matrix.set(0, 0, cos(angle*3.14159/180));
    matrix.set(0, 1, -sin(angle*3.14159/180));
    matrix.set(1, 0, sin(angle*3.14159/180));
    matrix.set(1, 1, cos(angle*3.14159/180));
    matrix.set(2, 2, 1);
    return matrix;
}

Point move_homogenous(Point ref, Point current_pos, float angle) {
    CMat3f translation_matrix = translation(ref, false);
    CMat3f rotation_matrix = rotation(angle);
    CMat3f translation_inverted = translation(ref, true);
    
    CMat3f transformation_matrix = translation_matrix * rotation_matrix * translation_inverted;
    
    CVec3f rotated_point = transformation_matrix * homonize(current_pos);
    
    float data[3];
    rotated_point.getData(data);
    Point p = Point(data[0], data[1]);
    return p;
}

// display callback function
void display2 (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    
    bhamCircle(sun_pos, sun_r, Color(1, 0, 0));
    bhamCircle(earth_pos, earth_r, earth_color);
    bhamCircle(moon_pos, moon_r, moon_color);
        
    earth_pos = move_homogenous(sun_pos, earth_pos, 1);
    moon_pos = move_homogenous(sun_pos, moon_pos, 1);
    moon_pos = move_homogenous(earth_pos, moon_pos, 7);
    
    earth_angle_step += 1;
    moon_angle_step += 7;
    
    if(earth_angle_step > 360 ) {earth_angle_step -= 360;}
    if(moon_angle_step > 360 ) {moon_angle_step -= 360;}
     
    glFlush();
    glutSwapBuffers (); // swap front and back buffer
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 'q':
        case 'Q':
            exit (0); // quit program
            break;
        case '1':
            glutDisplayFunc (display1);
            //glutPostRedisplay ();    // not needed since timer triggers redisplay
            break;
        case '2':
            glutDisplayFunc (display2);
            //glutPostRedisplay ();    // not needed since timer triggers redisplay
            break;
        default:
            // do nothing ...
            break;
    };
}

int main (int argc, char **argv)
{
    glutInit (&argc, argv);
    // we have to use double buffer to avoid flickering
    // TODO: lookup "double buffer", what is it for, how is it used ...
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutCreateWindow ("‹bung 2");
    
    init ();    // init my variables first
    initGL ();    // init the GL (i.e. view settings, ...)
    
    // assign callbacks
    glutTimerFunc (10, timer, 0);
    glutKeyboardFunc (keyboard);
    glutDisplayFunc (display1);
    // you might want to add a resize function analog to
    // ‹bung1 using code similar to the initGL function ...
    
    // start main loop
    glutMainLoop ();
    
    return 0;
}
