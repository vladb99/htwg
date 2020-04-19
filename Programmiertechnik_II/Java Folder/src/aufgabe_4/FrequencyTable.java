package aufgabe_4;

/**
 *
 * @author vladb
 * @since 18.4.2020
 */
public interface FrequencyTable<T> {

    int size();
    boolean isEmpty();
    void clear();
    void add(T d, int f);
    void add(T d);
    void addAll(FrequencyTable<? extends T> fq);
    Element<T> get(int pos);
    int get(T d);
    void collectMostFrequent(FrequencyTable<? super T> fq);
    void collectLeastFrequent(FrequencyTable<? super T> fq);
}