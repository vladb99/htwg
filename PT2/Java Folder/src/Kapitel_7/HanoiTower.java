package Kapitel_7;

public class HanoiTower {
    static int counter = -1;
    static int counterScheiben = 0;

    // Aufgabe 7.1:
    // a) Antwort ist (2^n) - 2
    // b) Antowrt ist (2^n) - 1

    public static void main(String[] args) {
        bewegeTurm(3, 1, 2, 3);
        System.out.println(counter);
        System.out.println(counterScheiben);
    }

    static void bewegeTurm(int n, int s, int z, int h) { // n = #Scheiben, s = start, z = ziel, h = hilfplatz
        counter++;
        if (n == 1) {
            System.out.println("Bewege Scheibe von " + s + " nach " + z);
            counterScheiben++;
        } else {
            bewegeTurm(n - 1, s, h, z);
            System.out.println("Bewege Scheibe von " + s + " nach " + z);
            counterScheiben++;
            bewegeTurm(n - 1, h, z, s);
        }
    }
}
