package aufgabe1;

import java.util.Iterator;
import java.util.NoSuchElementException;

public class HashDictionary<K, V> implements Dictionary<K, V> {

    private static final int DEF_CAPACITY = 31;
    private Node<K, V>[] tab;
    private int size;

    @SuppressWarnings("unchecked")
    public HashDictionary() {
        size = 0;
        tab = new Node[DEF_CAPACITY];
        initNodes(tab);
    }

    @SuppressWarnings("unchecked")
    public HashDictionary(int n) {
        size = 0;
        int prime = calculatePrimeNumber(n);
        tab = new Node[prime];
        initNodes(tab);
    }

    private void initNodes(Node<K, V>[] t) {
        for (int i = 0; i < t.length; i++) {
            t[i] = new Node<>(null, null);
        }
    }

    @Override
    @SuppressWarnings("unchecked")
    public V insert(K key, V value) {
        Node<K, V> n = searchForNode(key);
        if (n != null) {
            V oldValue = n.next.data.getValue();
            n.next.data = new Entry<>(key, value);
            return oldValue;
        }
        size++;
        if (size / tab.length >= 2) {
            migrateToTable();
        }

        int adr = key.hashCode();
        if (adr < 0) {
            adr = -adr;
        }
        adr = adr % tab.length;
        Node<K, V> p = tab[adr];
        while (p.next != null) {
            p = p.next;
        }
        p.next = new Node<>(new Entry<K, V>(key, value), null);

        return null;
    }

    private void migrateToTable() {
        int prime = calculatePrimeNumber(tab.length * 2);
        Node<K, V>[] tab2 = new Node[prime];
        initNodes(tab2);
        for (Entry<K, V> e : this) {
            int adr = e.getKey().hashCode();
            if (adr < 0) {
                adr = -adr;
            }
            adr = adr % tab2.length;
            Node<K, V> p = tab2[adr];
            while (p.next != null) {
                p = p.next;
            }
            p.next = new Node<>(new Entry<K, V>(e.getKey(), e.getValue()),null);
        }

        /*for (Node<K, V> n : tab) {
            while (n.next != null) {
                int adr = n.next.data.getKey().hashCode();
                if (adr < 0) {
                    adr = -adr;
                }
                adr = adr % tab2.length;
                Node<K, V> p = tab2[adr];
                while (p.next != null) {
                    p = p.next;
                }
                K key = n.next.data.getKey();
                V value = n.next.data.getValue();
                p.next = new Node<>(new Entry<K, V>(key, value),null);
                n = n.next;
            }
        }*/
        tab = tab2;
    }

    private int calculatePrimeNumber(int min) {
        int i = 0, p;
        do {
            p = 4 * i + 3;
            i++;
        } while (min > p);
        return p;
    }

    @Override
    public V search(K key) {
        Node<K, V> n = searchForNode(key);
        if (n != null) {
            return n.next.data.getValue();
        }
        return null;
    }

    // Returns parent of node associated with key
    public Node<K, V> searchForNode(K key) {
        int adr = key.hashCode();
        if (adr < 0) {
            adr = -adr;
        }
        adr = adr % tab.length;
        Node<K, V> p = tab[adr];

        while (p.next != null) {
            if (p.next.data.getKey().equals(key)) {
                return p;
            }
            p = p.next;
        }
        return null;
    }

    @Override
    public V remove(K key) {
        Node<K, V> n = searchForNode(key);
        if (n != null) {
            V oldValue = n.next.data.getValue();
            n.next = n.next.next;
            size--;
            return oldValue;
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
        private int current = 0;
        private Node<K, V> currentNode = tab[current].next;

        @Override
        public boolean hasNext() {
            while (currentNode == null) {
                if (current + 1 >= tab.length) {
                    return false;
                }
                currentNode = tab[++current].next;
            }
            return true;
        }

        @Override
        public Entry<K, V> next() {
            if(!hasNext()) {
                throw new NoSuchElementException();
            }
            Entry<K, V> data = currentNode.data;
            currentNode = currentNode.next;
            return data;
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

    private static class Node<K, V> {
        Node<K, V> next;
        Entry<K, V> data;
        Node(Entry<K, V> x, Node<K, V> p) {
            data = x;
            next = p;
        }
    }
}
