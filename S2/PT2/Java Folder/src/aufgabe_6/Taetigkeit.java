package aufgabe_6;

public interface Taetigkeit {
    public double getTime();
    public void add(Taetigkeit tk);
    public void remove(Taetigkeit tk);
    public int getAnzahl();
}
