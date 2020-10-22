package aufgabe1;

import java.util.Iterator;
import java.util.Spliterator;
import java.util.function.Consumer;

public class HashDictionary<K, V> implements Dictionary<K, V> {
    @Override
    public V insert(K key, V value) {
        return null;
    }

    @Override
    public V search(K key) {
        return null;
    }

    @Override
    public V remove(K key) {
        return null;
    }

    @Override
    public int size() {
        return 0;
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
