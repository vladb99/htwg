package aufgabe4;

import java.awt.*;
import java.util.*;
import java.util.List;

public class TelNet {
    public final int lbg;

    private List<TelVerbindung> optTelNet = null;
    private int optTelNetKosten = -1;

    private List<TelKnoten> nodes;
    private List<TelVerbindung> connections;
    private Map<TelKnoten, Integer> numeration;

    public TelNet(int lbg) {
        this.lbg = lbg;

        nodes = new LinkedList<>();
        connections = new LinkedList<>();
        numeration = new HashMap<>(); // needs to be hashmap, because TelKnoten doesn't implement Comparable
    }

    public boolean addTelKnoten(int x, int y) {
        TelKnoten node = new TelKnoten(x, y);
        if (nodes.contains(node)) {
            return false;
        }

        for (TelKnoten n : nodes) {
            int cost = calculateManhattanDistance(x, y, n.x, n.y);
            if (cost <= lbg) {
                TelVerbindung connection = new TelVerbindung(node, n, cost);
                connections.add(connection);
            }
        }
        numeration.put(node, nodes.size());
        nodes.add(node);
        return true;
    }

    public boolean computeOptTelNet() {
        if (connections.size() < 1) return false; // in order avoid PriorityQueue constructor from crashing

        UnionFind forest = new UnionFind(nodes.size());
        PriorityQueue<TelVerbindung> edges = new PriorityQueue<>(connections.size(), Comparator.comparingInt(e -> e.c)); // (e1, e2) -> e1.c - e2.c
        List<TelVerbindung> minSpanTree = new LinkedList<>();
        int minCost = 0;

        for (TelVerbindung e: connections) {
            edges.offer(e);
        }

        while (forest.size() != 1 && !edges.isEmpty()) {
            TelVerbindung connection = edges.poll();

            int t1 = forest.find(numeration.get(connection.u));
            int t2 = forest.find(numeration.get(connection.v));
            if (t1 != t2) {
                forest.union(t1, t2);

                minSpanTree.add(connection);
                minCost += connection.c;
            }
        }

        if (edges.isEmpty() && forest.size() != 1) {
            return false;
        }

        optTelNet = minSpanTree;
        optTelNetKosten = minCost;
        return true;
    }

    public List<TelVerbindung> getOptTelNet() throws IllegalStateException {
        if (optTelNet == null) {
            throw new IllegalStateException();
        }
        return optTelNet;
    }

    public int getOptTelNetKosten() throws IllegalStateException {
        if (optTelNetKosten == -1) {
            throw new IllegalStateException();
        }
        return optTelNetKosten;
    }

    public void drawOptTelNet(int xMax, int yMax) throws IllegalStateException {
        if(optTelNet == null) throw new IllegalStateException();

        StdDraw.setXscale(0, xMax);
        StdDraw.setYscale(0, yMax);
        StdDraw.setPenColor(Color.BLUE);

        Random r = new Random();

        for (TelVerbindung c: optTelNet) {
            StdDraw.setPenRadius(0.00525);
            StdDraw.point(c.u.x, c.u.y);
            StdDraw.point(c.v.x, c.v.y);
            StdDraw.setPenRadius();

            int x, y;
            int value = r.nextInt(2);
            if (value == 0) {
                x = c.u.x;
                y = c.v.y;
            } else {
                x = c.v.x;
                y = c.u.y;
            }

            StdDraw.line(c.u.x, c.u.y, x, y);
            StdDraw.line(c.v.x, c.v.y, x, y);
            StdDraw.show(0);
        }
    }

    public void generateRandomTelNet(int n, int xMax, int yMax) {
        Random r = new Random();
        while (n > 0) {
            int x = r.nextInt(xMax + 1);
            int y = r.nextInt(yMax + 1);
            if (addTelKnoten(x, y)) {
                n--;
            }
        }
    }

    public int size() {
        return nodes.size();
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        sb.append("Gesamtkosten: ").append(optTelNetKosten).append("\n");
        for (TelVerbindung c: optTelNet) {
            sb.append(c);
            sb.append("\n");
        }
        return sb.toString();
    }

    private int calculateManhattanDistance(int x1, int y1, int x2, int y2) {
        return Math.abs(x1 - x2) + Math.abs(y1 - y2);
    }

    public static void main(String[] args) {
        TelNet net1 = new TelNet(7);

        net1.addTelKnoten(1, 1);
        net1.addTelKnoten(3, 1);
        net1.addTelKnoten(4, 2);
        net1.addTelKnoten(2, 6);
        net1.addTelKnoten(3, 4);
        net1.addTelKnoten(4, 7);
        net1.addTelKnoten(7, 5);
        System.out.println(net1.computeOptTelNet());
        //net1.drawOptTelNet(20, 20);
        System.out.println(net1);

        TelNet net3 = new TelNet(100);
        net3.generateRandomTelNet(1000, 1000, 1000);
        System.out.println(net3.computeOptTelNet());
        net3.drawOptTelNet(1000, 1000);
    }
}
