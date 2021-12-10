#include <stdlib.h>

#include "vec.h"
#include "mat.h"
#include <cmath>

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

// https://math.stackexchange.com/questions/2305792/3d-projection-on-a-2d-plane-weak-maths-ressources

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

// Eine überaus primitive Punktklasse
class Point {
public:
    
    Point (float x=0, float y=0) {
        this->x = x;
        this->y = y;
    }
    
    float x, y;
};

// Eine überaus primitive Farbklasse
class Color {
public:
    
    Color (float r=1.0f, float g=1.0f, float b=1.0f) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    float r, g, b;
};

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

void drawPoint(float x, float y) {
    glVertex2f(x, y);
}

void bhamLine (CVec3f p1, CVec3f p2, Color c) {
    glBegin (GL_POINT);
    glColor3f (c.r, c.g, c.b);
    
    int x1 = p1(0);
    int x2 = p2(0);
    int y1 = p1(1);
    int y2 = p2(1);
    
    int t_x_1 = 0;
    int t_y_1 = 0;
    int t_x_2 = x2 - x1;
    int t_y_2 = y2 - y1;
    
    bool x_m = false;
    bool y_m = false;
    bool o_m = false;
    
    if (t_x_2 <= 0) {
        x_m = true;
        t_x_2 *= -1;
    }
    if (t_y_2 <= 0) {
        y_m = true;
        t_y_2 *= -1;
    }
    if (t_y_2 > t_x_2) {
        o_m = true;
        int temp = t_y_2;
        t_y_2 = t_x_2;
        t_x_2 = temp;
    }
    
    int delta_x = t_x_2 - t_x_1;
    int delta_y = t_y_2 - t_y_1;
    
    int delta_ne = 2 * (delta_y - delta_x);
    int delta_e = 2 * delta_y;
    int d = 2 * delta_y - delta_x;
    
    int y = 0;
    int x = 0;
    
    // erster Punkt
    drawPoint(p1(0), p1(1));
    while (t_x_1 < t_x_2) {
        
        if (d >= 0) {
            d += delta_ne;
            t_x_1++;
            t_y_1++;
        } else {
            d += delta_e;
            t_x_1++;
        }
        
        x = t_x_1;
        y = t_y_1;
        
        if (o_m){
            int temp = x;
            x = y;
            y = temp;
        }
        if (y_m){
            y *= -1;
        }
        if (x_m){
            x *= -1;
        }
        y += y1;
        x += x1;
        
        Point p = Point(x, y);
        drawPoint(p.x, p.y);
    }
    
    // letzter Punkt
    drawPoint(p2(0), p2(1));
    glEnd ();
}

CVec4f projectZ(float fFocus, CVec4f pView) {
    CVec4f projected_point;
    float ratio = fFocus / pView(2);
    projected_point(0) = pView(0) * ratio;
    projected_point(1) = pView(1) * ratio;
    projected_point(2) = 0;
    projected_point(3) = 1;
    return projected_point;
}

// A B C D E F G H
// 0 1 2 3 4 5 6 7
void drawProjektedZ(CVec3f points[8], Color c) {
    bhamLine(points[0], points[1], c);
    bhamLine(points[0], points[3], c);
    bhamLine(points[2], points[1], c);
    bhamLine(points[2], points[3], c);
    
    bhamLine(points[0], points[4], c);
    bhamLine(points[1], points[5], c);
    bhamLine(points[2], points[6], c);
    bhamLine(points[3], points[7], c);
    
    bhamLine(points[4], points[5], c);
    bhamLine(points[4], points[7], c);
    bhamLine(points[6], points[5], c);
    bhamLine(points[6], points[7], c);
}

// display callback function
void display (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    
    float vector[4] = {4, 8, -6 , 1};
    CVec4f view = CVec4f(vector);
    projectZ(3, view);
    
    Color c = Color(1, 1, 1);
    CVec3f quader[8];
    float p0[3] = { 0, 20, 1 };
    float p1[3] = { 20, 20, 1 };
    float p2[3] = { 20, 0, 1 };
    float p3[3] = { 0, 0, 1 };
    float p4[3] = { 10, 30, 1 };
    float p5[3] = { 30, 30, 1 };
    float p6[3] = { 30, 10, 1 };
    float p7[3] = { 10, 10, 1 };
    quader[0] = CVec3f(p0);
    quader[1] = CVec3f(p1);
    quader[2] = CVec3f(p2);
    quader[3] = CVec3f(p3);
    quader[4] = CVec3f(p4);
    quader[5] = CVec3f(p5);
    quader[6] = CVec3f(p6);
    quader[7] = CVec3f(p7);
    
    drawProjektedZ(quader, c);
    
    glFlush();
    glutSwapBuffers (); // swap front and back buffer
}

// function to initialize our own variables
void init ()
{
    
    // init timer interval
    g_iTimerMSecs = 10;
    
    // init variables for display1
    g_iPos     = 0;
    g_iPosIncr = 2;
    
    // init variables for display2
    int aiPos    [2] = {0, 0};
    int aiPosIncr[2] = {2, 2};
    g_vecPos.setData (aiPos);
    g_vecPosIncr.setData (aiPosIncr);
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
    //glutKeyboardFunc (keyboard);
    glutDisplayFunc (display);
    // you might want to add a resize function analog to
    // ‹bung1 using code similar to the initGL function ...
    
    // start main loop
    glutMainLoop ();
    
    return 0;
}
