package aufgabe4;

public class UnionFind {
    private int size;
    private int[] p;

    public UnionFind(int n) {
        this.p = new int[n];
        this.size = n;

        for (int i = 0; i < n; i++) {
            p[i] = -1;
        }
    }

    int find(int e) {
        if (e >= p.length) throw new IllegalArgumentException();

        while (p[e] >= 0) {
            e = p[e];
        }
        return e;
    }

    int size() {
        return this.size;
    }

    void union(int s1, int s2) {
        unionByHeight(s1, s2);
    }

    void unionByHeight(int s1, int s2) {
        if (p[s1] >= 0 || p[s2] >= 0) throw new IllegalArgumentException();
        if (s1 == s2) throw new IllegalArgumentException();

        --size;
        if (-p[s1] < -p[s2]) {
            p[s1] = s2;
        } else {
            if (-p[s1] == -p[s2]) {
                p[s1]--;
            }
            p[s2] = s1;
        }
    }

    public static void main(String[] args) {
        UnionFind u = new UnionFind(10);

        System.out.println("Anzahl der Partionierungen " + u.size());
        System.out.println();

        u.union(0, 1);
        System.out.println("Anzahl der Partionierungen " + u.size());
        System.out.println("1 befindet sich in " + u.find(1));
        System.out.println();

        u.union(3, 2);
        System.out.println("Anzahl der Partionierungen " + u.size());
        System.out.println();

        u.union(4, 5);
        System.out.println("Anzahl der Partionierungen " + u.size());
        System.out.println();

        u.union(3, 4);
        System.out.println("Anzahl der Partionierungen " + u.size());
        System.out.println("5 befindet sich in " + u.find(5));
        System.out.println();

        u.union(0, 3);
        System.out.println("Anzahl der Partionierungen " + u.size());
        System.out.println("1 befindet sich in " + u.find(1));
        System.out.println();

        u.union(7, 8);
        System.out.println("Anzahl der Partionierungen " + u.size());
        System.out.println();

        // u.union(7, 0); // throws IllegalArgumentException
        u.union(7, 3);
        System.out.println("Anzahl der Partionierungen " + u.size());
        System.out.println("8 befindet sich in " + u.find(8));
        System.out.println();
    }
}
