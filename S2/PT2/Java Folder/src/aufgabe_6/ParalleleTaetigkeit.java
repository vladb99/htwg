package aufgabe_6;

public class ParalleleTaetigkeit extends ZusammengesetzteTaetigkeit {

    @Override
    public double getTime() {
        double t = meineTaetigkeiten.get(0).getTime();
        for (Taetigkeit tk : meineTaetigkeiten) {
            if (tk.getTime() > t) {
                t = tk.getTime();
            }
        }
        return t;
    }
}
