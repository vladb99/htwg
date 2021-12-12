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
    glBegin (GL_POINTS);
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
    // calculate ratio of:
    // distance between eyepoint and origin (of camera and world coordinate system)
    // and distance between eyepoint and object.
    // projection happens on plane in origin (z = 0)
    float ratio = fFocus / (fFocus - pView(2));
    
    // if you know the ratio of which z coordinate of object has to be changed to be on the plane
    // then you can use that ratio to also calculate the rest of the coordinated, because the ray is a line.
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

void drawQuader(CVec3f cuboid[8], float fFocus, Color c) {
    CVec3f projected_points[8];
    for (int i = 0; i < 8; i++) {
        float coords_to_array[4] = {cuboid[i](0), cuboid[i](1), cuboid[i](2), 1};
        CVec4f view = CVec4f(coords_to_array);
        CVec4f projected_point_homonized = projectZ(fFocus, view);
        
        float array[3] = {projected_point_homonized(0), projected_point_homonized(1), 1};
        CVec3f projected_point = CVec3f(array);
        projected_points[i] = projected_point;
    }
    drawProjektedZ(projected_points, c);
}

// display callback function
void display (void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    
    CVec3f quader1[8];
    Color c1 = Color(1, 0, 0);
    float q1_A[3] = {-200, 100, 0};
    float q1_B[3] = {0, 100, 0};
    float q1_C[3] = {0, 0, 0};
    float q1_D[3] = {-200, 0, 0};
    float q1_E[3] = {-200, 100, -50};
    float q1_F[3] = {0, 100, -50};
    float q1_G[3] = {0, 0, -50};
    float q1_H[3] = {-200, 0, -50};
    quader1[0] = CVec3f(q1_A);
    quader1[1] = CVec3f(q1_B);
    quader1[2] = CVec3f(q1_C);
    quader1[3] = CVec3f(q1_D);
    quader1[4] = CVec3f(q1_E);
    quader1[5] = CVec3f(q1_F);
    quader1[6] = CVec3f(q1_G);
    quader1[7] = CVec3f(q1_H);
    drawQuader(quader1, 300, c1);
    
    CVec3f quader2[8];
    Color c2 = Color(0, 1, 0);
    float q2_A[3] = {-50, 400, 50};
    float q2_B[3] = {50, 400, 50};
    float q2_C[3] = {50, 200, 50};
    float q2_D[3] = {-50, 200, 50};
    float q2_E[3] = {-50, 400, -50};
    float q2_F[3] = {50, 400, -50};
    float q2_G[3] = {50, 200, -50};
    float q2_H[3] = {-50, 200, -50};
    quader2[0] = CVec3f(q2_A);
    quader2[1] = CVec3f(q2_B);
    quader2[2] = CVec3f(q2_C);
    quader2[3] = CVec3f(q2_D);
    quader2[4] = CVec3f(q2_E);
    quader2[5] = CVec3f(q2_F);
    quader2[6] = CVec3f(q2_G);
    quader2[7] = CVec3f(q2_H);
    drawQuader(quader2, 300, c2);
    
    CVec3f quader3[8];
    Color c3 = Color(0, 0, 1);
    float q3_A[3] = {100, -50, 0};
    float q3_B[3] = {200, -50, 0};
    float q3_C[3] = {200, -250, 0};
    float q3_D[3] = {100, -250, 0};
    float q3_E[3] = {100, -50, -100};
    float q3_F[3] = {200, -50, -100};
    float q3_G[3] = {200, -250, -100};
    float q3_H[3] = {100, -250, -100};
    quader3[0] = CVec3f(q3_A);
    quader3[1] = CVec3f(q3_B);
    quader3[2] = CVec3f(q3_C);
    quader3[3] = CVec3f(q3_D);
    quader3[4] = CVec3f(q3_E);
    quader3[5] = CVec3f(q3_F);
    quader3[6] = CVec3f(q3_G);
    quader3[7] = CVec3f(q3_H);
    drawQuader(quader3, 300, c3);
    
    // auf der Z-Achse liegt
    
    glFlush();
    glutSwapBuffers (); // swap front and back buffer
}

//CMat4f getTransform(CVec4f viewOrigin, CVec4f viewDir, CVec4f viewUp) {
//
//}

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
