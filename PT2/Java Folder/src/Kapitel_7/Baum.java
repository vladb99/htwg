package Kapitel_7;

import aufgabe_5.StdDraw;

public class Baum {

    static void draw(double x, double y, double alpha, double len, double d, int n) {
        if (n >= 0) {
            double xe = x + len * Math.cos(alpha);
            double ye = y + len * Math.sin(alpha);
            StdDraw.setPenRadius(d);
            StdDraw.line(x, y, xe, ye);
            draw(xe, ye, alpha + 0.90, len * 0.55, d / 1.5, n - 1);
            draw(xe, ye, alpha + 0.25, len * 0.25, d / 1.8, n - 1);
            draw(xe, ye, alpha - 0.40, len * 0.70, d / 1.5, n - 1);
        }
    }

    public static void main(String[] args) {
        StdDraw.setXscale(-6, +6);
        StdDraw.setYscale(-1, +11);
        draw(0, 0, 1.7, 4.0, 0.02, 7);
    }
}
