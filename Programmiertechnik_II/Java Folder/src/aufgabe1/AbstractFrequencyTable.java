package aufgabe1;

/**
 *
 * @author oliverbittel
 * @since 22.2.2019
 */
public abstract class AbstractFrequencyTable implements FrequencyTable {
    @Override
    public boolean isEmpty() {
        return this.size() == 0;
    }

    @Override
    public void add(String w) {
        add(w, 1);
    }

    @Override
    public void addAll(FrequencyTable fq) {
        // Ihr Code:

    }

    @Override
    public void collectMostFrequent(FrequencyTable fq) {
        // Ihr Code:
    }

    @Override
    public void collectLeastFrequent(FrequencyTable fq) {
        // Ihr Code:
    }

    /**
     * Liefert eine String-Darstellung zur&uuml;ck.
     * @return String-Darstellung.
     */
    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("");
        // Ihr Code:

        return s.toString();
    }
}