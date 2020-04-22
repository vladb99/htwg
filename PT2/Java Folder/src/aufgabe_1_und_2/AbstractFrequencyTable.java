package aufgabe_1_und_2;

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
        for(int i = 0; i < fq.size(); i++) {
            Word word = fq.get(i);
            add(word.getWord(), word.getFrequency());
        }
    }

    @Override
    public void collectMostFrequent(FrequencyTable fq) {
        fq.clear();
        Word firstWord = get(0);
        fq.add(firstWord.getWord(), firstWord.getFrequency());
        for(int j = 1; j < size(); j++) {
            Word otherWord = get(j);
            if (otherWord.getFrequency() == firstWord.getFrequency()) {
                fq.add(otherWord.getWord(), otherWord.getFrequency());
            } else {
                break;
            }
        }
    }

    @Override
    public void collectLeastFrequent(FrequencyTable fq) {
        fq.clear();
        for(int j = 0; j < size(); j++) {
            Word word = get(j);
            if (word.getFrequency() == 1) {
                fq.add(word.getWord(), word.getFrequency());
            }
        }
    }

    /**
     * Liefert eine String-Darstellung zur&uuml;ck.
     * @return String-Darstellung.
     */
    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("");
        s.append("{");
        for(int i = 0; i < size(); i++) {
            Word word = get(i);
            s.append(word.getWord())
                    .append(":")
                    .append(word.getFrequency())
                    .append(", ");
        }
        s.append("}")
                .append(" size = ")
                .append(size());

        return s.toString();
    }
}