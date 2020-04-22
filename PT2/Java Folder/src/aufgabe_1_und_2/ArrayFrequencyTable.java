package aufgabe_1_und_2;

import java.util.Arrays;

/**
 *
 * @author oliverbittel
 * @since 12.2.2020
 */
public class ArrayFrequencyTable extends AbstractFrequencyTable {
    private int size;
    private Word fqTable[];
    private final int DefaultSize = 100;

    public ArrayFrequencyTable() {
        clear();
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public final void clear() {
        size = 0;
        fqTable = new Word[DefaultSize];
    }

    @Override
    public void add(String w, int f) {
        boolean fqSummed = false;

        if(fqTable.length == size) {
            fqTable = Arrays.copyOf(fqTable, 2*size);
        }

        for (int i = 0; i < size; i++) {
            if(w.equals(fqTable[i].getWord())) {
                fqSummed = true;
                fqTable[i].addFrequency(f);
            }
        }

        if(!fqSummed) {
            fqTable[size] = new Word(w, f);
            size++;
        }

        for (int i = size - 1; i > 0; i--) {
            if(fqTable[i].getFrequency() > fqTable[i - 1].getFrequency()) {
                Word temp = fqTable[i];
                fqTable[i] = fqTable[i - 1];
                fqTable[i - 1] = temp;
            }
        }
    }

    @Override
    public Word get(int pos) {
        return fqTable[pos];
    }

    @Override
    public int get(String w) {
        for (int i = 0; i < size; i++) {
            if (w.equals(fqTable[i].getWord())) {
                return fqTable[i].getFrequency();
            }
        }
        return 0;
    }
}