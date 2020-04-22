package Kapitel_2;

import java.util.Arrays;

public class ArrayList implements List {
    private static final int DEF_CAPACITY = 32;
    private int size;
    private int[] data;

    public ArrayList() {
        clear();
    }

    public ArrayList(List list) {
        clear();
        append(list);
    }

    public final void clear(){
        size = 0;
        data = new int[DEF_CAPACITY];
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public void append(List list) {
        for (int i = 0; i < list.size(); i++) {
            add(list.get(i));
        }
    }

    public void add(int x) {
        add(size(), x);
    }

    public void add(int idx, int x) {
        if (idx < 0 || idx > size) {
            throw new IndexOutOfBoundsException();
        }
        if (data.length == size) {
            data = Arrays.copyOf(data, 2 * size);
        }
        for (int i = size; i > idx; i--) {
            data[i] = data[i-1];
        }
        data[idx] = x;
        size++;
    }

    public int set(int idx, int x) {
        if (idx < 0 || idx >= size) {
            throw new IndexOutOfBoundsException();
        }
        int old = data[idx];
        data[idx] = x;
        return old;
    }

    public int get(int idx) {
        if (idx < 0 || idx >= size) {
            throw new IndexOutOfBoundsException();
        }
        return data[idx];
    }
    public void remove(int idx) {
        if (idx < 0 || idx >= size) {
            throw new IndexOutOfBoundsException();
        }
        for (int i = idx; i < size-1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("");
        for (int i = 0; i < size; i++) {
            s.append(data[i]).append(", ");
        }
        s.append("size = ").append(size);
        return s.toString();
    }

    public static void main(String[] args) {
        List l = new ArrayList();
        l.add(5);
        l.add(3);
        l.add(2);

        List l2 = new ArrayList(l);
        System.out.println(l2.toString());
    }
}
