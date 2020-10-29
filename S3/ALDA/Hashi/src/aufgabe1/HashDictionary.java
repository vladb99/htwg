package aufgabe1;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.NoSuchElementException;

public class HashDictionary<K, V> implements Dictionary<K, V> {

    private static final int DEF_CAPACITY = 31;
    private LinkedList<Entry<K, V>>[] tab;
    private int size;
    private final int loadFactor = 2;

    @SuppressWarnings("unchecked")
    public HashDictionary() {
        size = 0;
        tab = new LinkedList[DEF_CAPACITY];
        initNodes(tab);
    }

    @SuppressWarnings("unchecked")
    public HashDictionary(int n) {
        int prime;
        if (!isPrime(n)) {
            prime = nextPrime(n);
        } else {
            prime = n;
        }
        size = 0;
        tab = new LinkedList[prime];
        initNodes(tab);
    }

    private void initNodes(LinkedList<Entry<K, V>>[] t) {
        for (int i = 0; i < t.length; i++) {
            t[i] = new LinkedList<>();
        }
    }

    @Override
    public V insert(K key, V value) {
        int adr = getAdrFromKey(key);
        adr = adr % tab.length;
        for (Entry<K, V> entry : tab[adr]) {
            if (entry.getKey().equals(key)) {
                V oldValue = entry.getValue();
                entry.setValue(value);
                return oldValue;
            }
        }

        size++;
        if (size / tab.length >= loadFactor) {
            migrateToTable();
        }

        adr = getAdrFromKey(key);
        adr = adr % tab.length;
        tab[adr].add(new Entry<>(key, value));

        return null;
    }

    @SuppressWarnings("unchecked")
    private void migrateToTable() {
        int prime = nextPrime(tab.length * 2);
        LinkedList<Entry<K, V>>[] tab2 = new LinkedList[prime];
        initNodes(tab2);
        for (Entry<K, V> e : this) {
            int adr = getAdrFromKey(e.getKey());
            adr = adr % tab2.length;
            tab2[adr].add(new Entry<>(e.getKey(), e.getValue()));
        }
        tab = tab2;
    }

    private int nextPrime(int num) {
        num++;
        for (int i = 2; i < num; i++) {
            if(num%i == 0) {
                num++;
                i=2;
            }
        }
        return num;
    }

    private boolean isPrime(int num){
        boolean prime = true;
        for(int i = 2; i < num; i++) {
            if((num % i) == 0) {
                prime = false;
            }
        }
        return prime;
    }

    private int getAdrFromKey(K key) {
        int adr = key.hashCode();
        if (adr < 0) {
            adr = -adr;
        }
        return adr;
    }

    @Override
    public V search(K key) {
        int adr = getAdrFromKey(key);
        adr = adr % tab.length;
        for (Entry<K, V> entry : tab[adr]) {
            if (entry.getKey().equals(key)) {
                return entry.getValue();
            }
        }
        return null;
    }

    @Override
    public V remove(K key) {
        int adr = getAdrFromKey(key);
        adr = adr % tab.length;
        for (Entry<K, V> entry : tab[adr]) {
            if (entry.getKey().equals(key)) {
                tab[adr].remove(entry);
                --size;
                return entry.getValue();
            }
        }
        return null;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public Iterator<Entry<K, V>> iterator() {
        return new HashDictionaryIterator();
    }

    private class HashDictionaryIterator implements Iterator<Entry<K, V>> {
        private int currentRow = 0;
        private Iterator<Entry<K, V>> iterator = tab[currentRow].iterator();

        @Override
        public boolean hasNext() {
            while (!iterator.hasNext()) {
                if (currentRow + 1 >= tab.length) {
                    return false;
                }
                iterator = tab[++currentRow].iterator();
            }
            return true;
        }

        @Override
        public Entry<K, V> next() {
            if(!hasNext()) {
                throw new NoSuchElementException();
            }
            return iterator.next();
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("");
        for (Entry<K, V> e : this) {
            s.append(e.getKey()).append(": ").append(e.getValue()).append("\n");
        }
        s.append("size = ").append(size);
        return s.toString();
    }
}
