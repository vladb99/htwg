package aufgabe_4;

import java.util.Arrays;
import java.util.ConcurrentModificationException;
import java.util.Iterator;
import java.util.NoSuchElementException;

/**
 *
 * @author vladb
 * @since 18.4.2020
 */
public class ArrayFrequencyTable<T> extends AbstractFrequencyTable<T> {
    private int size;
    private Element<T>[] fqTable;
    private final int DefaultSize = 100;
    protected int modCount = 0;

    public ArrayFrequencyTable() {
        clear();
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    @SuppressWarnings("unchecked")
    public final void clear() {
        size = 0;
        fqTable = (Element<T>[]) new Element[DefaultSize];
        modCount++;
    }

    @Override
    public void add(T d, int f) {
        boolean fqSummed = false;

        if(fqTable.length == size) {
            fqTable = Arrays.copyOf(fqTable, 2*size);
        }

        for (int i = 0; i < size; i++) {
            if(d.equals(fqTable[i].getData())) {
                fqSummed = true;
                fqTable[i].addFrequency(f);
            }
        }

        if(!fqSummed) {
            fqTable[size] = new Element<T>(d, f);
            size++;
            modCount++;
        }

        for (int i = size - 1; i > 0; i--) {
            if(fqTable[i].getFrequency() > fqTable[i - 1].getFrequency()) {
                Element<T> temp = fqTable[i];
                fqTable[i] = fqTable[i - 1];
                fqTable[i - 1] = temp;
            }
        }
    }

    @Override
    public Element<T> get(int pos) {
        return fqTable[pos];
    }

    @Override
    public int get(T d) {
        for (int i = 0; i < size; i++) {
            if (d.equals(fqTable[i].getData())) {
                return fqTable[i].getFrequency();
            }
        }
        return 0;
    }

    @Override
    public Iterator<Element<T>> iterator() {
        return new ArrayListIterator();
    }

    private class ArrayListIterator implements Iterator<Element<T>> {
        private int current = 0;
        private int expectedMod = modCount;

        @Override
        public boolean hasNext() {
            return get(current) != null;
        }

        @Override
        public Element<T> next() {
            if (expectedMod != modCount) {
                throw new ConcurrentModificationException();
            }
            if(!hasNext()) {
                throw new NoSuchElementException();
            }
            return get(current++);
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }


    }
}