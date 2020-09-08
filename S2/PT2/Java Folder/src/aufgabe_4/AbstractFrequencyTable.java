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
    public void addAll(FrequencyTable<? extends T> fq) {
        for (Element<? extends T> data : fq) {
            add(data.getData(), data.getFrequency());
        }
    }

    @Override
    public void collectMostFrequent(FrequencyTable<? super T> fq) {
        fq.clear();
        Element<T> firstData = get(0);
        fq.add(firstData.getData(), firstData.getFrequency());
        for (Element<T> otherData : this) {
            if (otherData != firstData) {
                if (otherData.getFrequency() == firstData.getFrequency()) {
                    fq.add(otherData.getData(), otherData.getFrequency());
                } else {
                    break;
                }
            }
        }
    }

    @Override
    public void collectLeastFrequent(FrequencyTable<? super T> fq) {
        fq.clear();
        for(Element<T> data : this) {
            if (data.getFrequency() == 1) {
                fq.add(data.getData(), data.getFrequency());
            }
        }
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("");
        s.append("{");
        for(Element<T> data : this) {
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