package aufgabe1;

import java.util.Iterator;
import java.util.Spliterator;
import java.util.function.Consumer;

public class SortedArrayDictionary<K extends Comparable<? super K>, V> implements Dictionary<K, V> {

    private static final int DEF_CAPACITY = 16;
    private int size;
    private Entry<K, V>[] data;

    @SuppressWarnings("unchecked")
    public SortedArrayDictionary() {
        size = 0;
        data = new Entry[DEF_CAPACITY];
    }

    @Override
    public V insert(K key, V value) {
        V i = search(key);
        if (i != null) {
            V r = i;

        }

        return null;
    }

    @Override
    public V search(K key) {
        int li = 0;
        int re = size - 1;

        while (re >= li) {
            int m = (li + re) / 2;
            if (key.compareTo(data[m].getKey()) < 0) {
                re = m - 1;
            } else if (key.compareTo(data[m].getKey()) > 0) {
                li = m + 1;
            } else {
                return data[m].getValue();
            }
        }
        return null;
    }

    @Override
    public V remove(K key) {
        return null;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public Iterator<Entry<K, V>> iterator() {
        return null;
    }

    @Override
    public void forEach(Consumer<? super Entry<K, V>> action) {

    }

    @Override
    public Spliterator<Entry<K, V>> spliterator() {
        return null;
    }
}
