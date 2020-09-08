package aufgabe_6;

public class SerielleTaetigkeit extends ZusammengesetzteTaetigkeit {

    @Override
    public double getTime() {
        double t = 0;
        for (Taetigkeit tk : meineTaetigkeiten) {
            t += tk.getTime();
        }
        return t;
    }
}
