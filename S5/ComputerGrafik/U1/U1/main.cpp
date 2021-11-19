///////////////////////////////////////////////////////////////////////
//                                                                                         //
// Codeger�st f�r Vorlesung Computergraphik WS 2021/22 �bung 1       //
//                                                                               //
///////////////////////////////////////////////////////////////////////

#define GL_SILENCE_DEPRECATION
// Include-File f�r die Text Ein-/Ausgabe
#include <iostream>
#include <unistd.h>
using namespace std;

// Include-File f�r die GLUT-Library
#include "GLUT/glut.h"
//#include <OpenGL/gl.h>



/////////////////////////////////////////////////////////////////////////////////////////
//
// Hier wird einiges initialisiert. Sie duerfen sich gerne den Code anschauen und
// versuchen ihn zu verstehen. Das sollte Ihnen nicht allzu schwer fallen. Es werden
// jedoch einige Techniken benutzt (Texturen, ...) die wir in der Vorlesung noch
// nicht besprochen haben, die wir aber aus techn. Gr�nden hier benöttigen.
//
// Weiter unten finden Sie einen Vermerk, ab dem Sie den Code jedoch vollstaendig
// verstehen sollten!!!


// Aufloesungen der gesamten Textur
// !!!ACHTUNG!!! nicht alle Texturaufl�sungen funktionieren!
// Stichwort ungef�hr: POT2 Problematik
#define TEX_RES_X 60
#define TEX_RES_Y 60
// Anzahl der Pixel der Textur
#define TEX_RES TEX_RES_X*TEX_RES_Y
// Achsenl�nge der Textur (Achsen sind asymmetrisch von -TexRes#/2 bis TesRes#/2-1)
#define TEX_HALF_X TEX_RES_X/2
#define TEX_HALF_Y TEX_RES_Y/2
// Konvertiert Indices von (x,y) Koordinaten in ein lineares Array
#define TO_LINEAR(x, y) (((x)) + TEX_RES_X*((y)))

// globaler Speicher f�r Texturdaten
char g_Buffer[3*TEX_RES];
// Textur ID Name
GLuint g_TexID = 0;

// Aufl�sung des Hauptfensters (kann sich durch User �ndern)
int g_WinWidth = 800;
int g_WinHeight = 800;

// Funktion organisiert die Textur.
// Kuemmern Sie sich nicht weiter um diese Funktion, da
// sie momentan nur ein notwendiges uebel darstellt!
void manageTexture () {
    
    glEnable (GL_TEXTURE_2D);
    
    if (g_TexID==0)    glGenTextures (1, &g_TexID);
    
    glBindTexture (GL_TEXTURE_2D, g_TexID);
    
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, TEX_RES_X, TEX_RES_Y, 0, GL_RGB, GL_UNSIGNED_BYTE, g_Buffer);
    
    glBindTexture (GL_TEXTURE_2D, 0);
    
    glDisable (GL_TEXTURE_2D);
}

// Callback Funktion um die Fenstergr��en anzupassen.
// Auch diese Funktion ist ein notwendiges �bel! K�mmern
// Sie sich im Moment nicht weiter darum.
void reshape(int w, int h) {
    
    g_WinWidth = w;
    g_WinHeight = h;
    
    glViewport(0, 0, w, h);                    // Establish viewing area to cover entire window.
    
    glMatrixMode(GL_PROJECTION);            // Start modifying the projection matrix.
    glLoadIdentity();                        // Reset project matrix.
    glOrtho(-w/2, w/2, -h/2, h/2, 0, 1);    // Map abstract coords directly to window coords.
    
    glutPostRedisplay ();
}




//
//
/////////////////////////////////////////////////////////////////////////////////////////
//
// Hier f�ngt der f�r Sie wirklich relevante Teil des Programms an.
//




// Eine �beraus primitive Punktklasse
class Point {
public:
    
    Point (int x=0, int y=0) {
        this->x = x;
        this->y = y;
    }
    
    int x, y;
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

// Funktion l�scht den Bildschirm mit der angegebenen Farbe
// Usage z.B.: clearImage (Color (1,1,1))
// l�scht den Bildschirm in Wei�.
// Ohne Farbangabe ist der Standard Wei�
void clearImage (Color c=Color()) {
    for (int i=0; i<TEX_RES; i++) {
        g_Buffer[3*i  ] = 255.0*c.r;
        g_Buffer[3*i+1] = 255.0*c.g;
        g_Buffer[3*i+2] = 255.0*c.b;
    }
}

// Funktion malt einen Punkt an die angegebenen Koordinaten
// Usage z.B.: setPoint (Point(10, 5), Color (1,0,0))
// malt einen Punkt an die Koordinate (10, 5)
// Ohne Farbangabe ist die standard Malfarbe Schwarz
//
// Nutzen Sie diese Funktion ...
void setPoint (Point p, Color c=Color(0,0,0)) {
    int x = p.x + TEX_HALF_X;
    int y = p.y + TEX_HALF_Y;
    if (x < 0 || y < 0 || x >= TEX_RES_X || y >= TEX_RES_Y) {
        cerr << "Illegal point co-ordinates (" << p.x << ", " << p.y << ")\n" << flush;
        return;
    }
    
    g_Buffer[3*TO_LINEAR (x, y)  ] = 255.0*c.r;
    g_Buffer[3*TO_LINEAR (x, y)+1] = 255.0*c.g;
    g_Buffer[3*TO_LINEAR (x, y)+2] = 255.0*c.b;
}

//
// �BUNG 1 AUFGABE 1:
//
// Diese Funktion soll eine Gerade zwischen den Punkten
// p1 und p2 in der Farbe c malen. Benutzen Sie die Funktion
// setPoint um die individuellen Punkte zu zeichnen.
void bhamLine (Point p1, Point p2, Color c) {
    
    //p1 = Point(0,0);
    //p2 = Point(3,10);
    
    int x1 = p1.x;
    int x2 = p2.x;
    int y1 = p1.y;
    int y2 = p2.y;
    
    int t_x_1 = 0;
    int t_y_1 = 0;
    int t_x_2 = x2 - x1;
    int t_y_2 = y2 - y1;
    
    bool x_m = false;
    bool y_m = false;
    bool o_m = false;
    
    if (t_x_2 <= 0){
        x_m = true;
        t_x_2 *= -1;
    }
    if (t_y_2 <= 0){
        y_m = true;
        t_y_2 *= -1;
    }
    if (t_y_2 > t_x_2){
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
    setPoint (p1, c);
    while (t_x_1 < t_x_2) {
        
        if (d >= 0) {
            //printf("%d if \n", d);
            d += delta_ne;
            t_x_1++;
            t_y_1++;
        } else {
            //printf("%d else\n", d);
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
        setPoint (p, c);
    }
    
    // ...
    
    // letzter Punkt
    setPoint (p2, c);
}

void drawSymetricPoints(int x, int y, Color c, int px, int py) {
    setPoint(Point((x+px), y+py), c);
    setPoint(Point(-x+px, y+py), c);
    setPoint(Point(-x+px, -y+py), c);
    setPoint(Point((x+px), -y+py), c);
}

//
// �BUNG 1 AUFGABE 2:
//
// Diese Funktion soll einen Kreis mit Radius r um den Punkt p
// malen. Benutzen Sie die Funktion setPoint um die individuellen
// Punkte zu zeichnen. Vergessen Sie nicht auch den Mittelpunkt zu
// zeichnen!
void bhamCircle (Point p, int r, Color c) {
    
    int x = 0;
    int y = r;
    int d = 5 - 4 * r;
    int delta_se = 0;
    int delta_e = 0;
    
    drawSymetricPoints(x, y, c, p.x, p.y);
    drawSymetricPoints(y, x, c, p.x, p.y);
    // Mittelpunkt
    setPoint (p, c);
    
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
}

// Die Callback Funktion die f�r das eigentliche Malen
// zust�ndig ist. Im Wesentlichen brauchen Sie sich nur
// um den Bereich zwischen den Kommentaren zu k�mmern,
// alles andere ist wiederum ein notwendiges �bel!
void display (void) {
    
    //////////////////////////////////////////////////////////////////
    //
    // Hier sollen Ihre Bresenham-Funktionen
    // eine Gerade und einen Kreis zeichnen.
    //
    // Im Prinzip brauchen Sie hier keine
    // gro�artigen �nderungen vorzunehmen, es
    // sei denn Sie wollen "spielen" :-D
    //
    
    clearImage ();            // altes Bild l�schen
    
    Point p1(-10, -20);        // ersten Punkt f�r Gerade definieren
    Point p2(15, 25);        // ebenso den zweiten Punkt
    Color cl(1,0,0);        // es soll eine rote Gerade sein ...
    
    // ersten Punkt f�r Gerade definieren
    Point p11(-10, -25);
    Point p21(26, 20);
    
    Point p12(-10, -20);        // ersten Punkt f�r Gerade definieren
    Point p22(26, 20);
    
    bhamLine (p1, p2, cl);    // Gerade zeichnen ...
    
    //bhamLine (p11, p21, cl);    // Gerade zeichnen ...
    
    //bhamLine (p12, p22, cl);    // Gerade zeichnen ...
    
    Point p(5, 0);        // Mittelpunkt f�r Kreis definieren
    int r = 17;            // Radius festlegen
    Color cc(0,0,1);        // es soll ein blauer Kreis sein ...
    
    bhamCircle (p, r, cc);    // Kreis zeichnen ...
    
    //
    // Ab hier sollten Sie nichts mehr �ndern!
    //
    //////////////////////////////////////////////////////////////////
    
    manageTexture ();
    
    glClear (GL_COLOR_BUFFER_BIT);
    glBindTexture (GL_TEXTURE_2D, g_TexID);
    
    glEnable (GL_TEXTURE_2D);
    glBegin (GL_QUADS);
    glColor3f (1, 0, 0);
    glTexCoord2f (0, 0);
    glVertex2f (-g_WinWidth/2, -g_WinHeight/2);
    glTexCoord2f (1, 0);
    glVertex2f (g_WinWidth/2, -g_WinHeight/2);
    glTexCoord2f (1, 1);
    glVertex2f (g_WinWidth/2, g_WinHeight/2);
    glTexCoord2f (0, 1);
    glVertex2f (-g_WinWidth/2, g_WinHeight/2);
    glEnd ();
    
    glBindTexture (GL_TEXTURE_2D, 0);
    glDisable (GL_TEXTURE_2D);
    
    glFlush ();
}

// Die Main-Funktion
int main (int argc, char **argv) {
    
    glutInit (&argc, argv);
    glutInitWindowSize (g_WinWidth, g_WinHeight);
    glutCreateWindow ("Uebung 1: Bresenham");
    
    glutReshapeFunc (reshape);    // zust�ndig f�r Gr��en�nderungen des Fensters
    glutDisplayFunc (display);    // zust�ndig f�r das wiederholte Neuzeichnen des Bildschirms
    
    glutMainLoop ();
    
    glDeleteTextures (1, &g_TexID); // l�scht die oben angelegte Textur
    
    return 0;
}
