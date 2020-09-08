package aufgabe_6;

import java.util.LinkedList;
import java.util.List;

public abstract class ZusammengesetzteTaetigkeit implements Taetigkeit {
    protected List<Taetigkeit> meineTaetigkeiten = new LinkedList<>();

    public abstract double getTime();

    public void add(Taetigkeit tk) {
        meineTaetigkeiten.add(tk);
    }

    public void remove(Taetigkeit tk) {
        meineTaetigkeiten.remove(tk);
    }

    public int getAnzahl() {
        int a = 0;
        for (Taetigkeit tk : meineTaetigkeiten) {
            a += tk.getAnzahl();
        }
        return a;
    }
}
