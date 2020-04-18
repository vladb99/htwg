package aufgabe_4;

/**
 *
 * @author oliverbittel
 * @since 22.2.2019
 */
public abstract class AbstractFrequencyTable<T> implements FrequencyTable<T> {
    @Override
    public boolean isEmpty() {
        return this.size() == 0;
    }

    @Override
    public void add(T d) {
        add(d, 1);
    }

    @Override
    public void addAll(FrequencyTable<T> fq) {
        for(int i = 0; i < fq.size(); i++) {
            Element<T> data = fq.get(i);
            add(data.getData(), data.getFrequency());
        }
    }

    @Override
    public void collectMostFrequent(FrequencyTable<T> fq) {
        fq.clear();
        Element<T> firstWord = get(0);
        fq.add(firstWord.getData(), firstWord.getFrequency());
        for(int j = 1; j < size(); j++) {
            Element<T> otherWord = get(j);
            if (otherWord.getFrequency() == firstWord.getFrequency()) {
                fq.add(otherWord.getData(), otherWord.getFrequency());
            } else {
                break;
            }
        }
    }

    @Override
    public void collectLeastFrequent(FrequencyTable<T> fq) {
        fq.clear();
        for(int j = 0; j < size(); j++) {
            Element<T> word = get(j);
            if (word.getFrequency() == 1) {
                fq.add(word.getData(), word.getFrequency());
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("");
        s.append("{");
        for(int i = 0; i < size(); i++) {
            Element<T> data = get(i);
            s.append(data.getData())
                    .append(":")
                    .append(data.getFrequency())
                    .append(", ");
        }
        s.append("}")
                .append(" size = ")
                .append(size());

        return s.toString();
    }
}