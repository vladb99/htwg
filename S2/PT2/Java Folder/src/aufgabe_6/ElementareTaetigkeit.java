package aufgabe_6;

public class ElementareTaetigkeit implements Taetigkeit {
    private double time;
    private String beschr;

    public ElementareTaetigkeit(String b, double t) {
        this.beschr = b;
        this.time = t;
    }

    public double getTime() {
        return this.time;
    }

    public int getAnzahl() {
        return 1;
    }

    public void add(Taetigkeit tk) {}
    public void remove(Taetigkeit tk) {}
}
