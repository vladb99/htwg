package aufgabe1;

import java.util.Arrays;
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
        V v = search(key);
        if (v != null) {
            V r = v;
            v = value;
            return r;
        }

        if (data.length == size) {
            Arrays.copyOf(data, 2*size);
        }
        int j = size - 1;
        while (j >= 0 && key.compareTo(data[j].getKey()) < 0) {
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = new Entry<K,V>(key, value);
        size++;
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
        V v = search(key);
        if (v == null) {
            return null;
        }

        V r = v;
        for (int j ) {

        }

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
