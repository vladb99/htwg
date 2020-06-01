package aufgabe_5;

import java.awt.*;
import java.awt.geom.Point2D;
import java.util.Random;

public class PythagorasBaum {
    private static double leanAngle = 30;
    private static double limit = 5;
    private static double colorLimit = 6;
    private static Color tree = new Color(102, 65, 32);
    private static Color leaf = new Color(0, 204, 0);
    private static final Random random = new Random();

    public static void main(String[] args) {
        Point2D a = new Point2D.Double(0,-600);
        Point2D b = new Point2D.Double(200, -600);

        StdDraw.setXscale(-1200, 1200);
        StdDraw.setYscale(-1200, 1200);
        StdDraw.setPenColor(tree);

        drawTree(a, b);
    }

    private static void drawTree(Point2D a, Point2D b) {
        drawTree(a, b, false);
    }

    private static void drawTree(Point2D a, Point2D b, boolean r) {
        double w = a.distance(b);
        double u, h = 0;

        if (w < colorLimit) {
            StdDraw.setPenColor(leaf);
        } else {
            StdDraw.setPenColor(tree);
        }

        Point2D c = rotatePoint(b, a, Math.toRadians(-90));
        Point2D d = rotatePoint(a, b, Math.toRadians(90));

        if (r) {
            leanAngle = 20 + (70 - 20) * random.nextDouble();
            double dist = d.distance(a);
            h = 1 + (2 * dist - 1) * random.nextDouble(); //dist + dist * random.nextDouble();
            c = scale(b, c, h);
            d = scale(a, d, h);
        }

        u = w * Math.cos(Math.toRadians(leanAngle));
        Point2D e = scale(d, rotatePoint(d, c, Math.toRadians(leanAngle)), u);

        drawLine(a, d);
        drawLine(b, c);

        if (w > limit) {
            drawTree(d, e, r);
            StdDraw.show(0);
            drawTree(e, c, r);
        }
    }

    private static Point2D scale(Point2D p1, Point2D p2, double factor) {
        Point2D vector = subPoint(p2, p1);
        double normalizer = Math.sqrt(Math.pow(vector.getX(), 2) + Math.pow(vector.getY(), 2));
        vector = mulPoint(vector, (1 / normalizer) * factor);
        return addPoint(p1, vector);
    }

    private static Point2D subPoint(Point2D p1, Point2D p2) {
        return new Point2D.Double(
                p1.getX() - p2.getX(),
                p1.getY() - p2.getY()
        );
    }

    private static Point2D addPoint(final Point2D p1, final Point2D p2) {
        return new Point2D.Double(
                p1.getX() + p2.getX(),
                p1.getY() + p2.getY()
        );
    }


    private static Point2D mulPoint(final Point2D p, final double factor) {
        return new Point2D.Double(
                p.getX() * factor,
                p.getY() * factor
        );
    }


    private static void drawLine(Point2D p1, Point2D p2) {
        StdDraw.line(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }

    private static Point2D rotatePoint(Point2D center, Point2D p, double angle)
    {
        // translate point back to origin:
        double x = p.getX() - center.getX();
        double y = p.getY() - center.getY();

        // rotate point
        double xnew = x * Math.cos(angle) - y * Math.sin(angle);
        double ynew = x * Math.sin(angle) + y * Math.cos(angle);

        // translate point back:
        x = xnew + center.getX();
        y = ynew + center.getY();
        return new Point2D.Double(x, y);
    }
}
