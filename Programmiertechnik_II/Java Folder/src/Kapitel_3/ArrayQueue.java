package Kapitel_3;

import java.util.NoSuchElementException;

public class ArrayQueue implements Queue {

    private static final int DEF_CAPACITY = 16;
    private int size;
    private int back;
    private int front;
    private int[] data;

    public ArrayQueue() {
        size = 0;
        back = DEF_CAPACITY - 1;
        front = 0;
        data = new int [DEF_CAPACITY];
    }

    @Override
    public void add(int x) {
        if(data.length == size) {
            resize(2*size);
        }
        back = (back + 1) % data.length;
        data[back] = x;
        size++;
    }

    private void resize(int newLength) {
        assert size == data.length && newLength > size;

        int[] old = data;
        data = new int[newLength];
        System.arraycopy(old, front, data, 0, old.length-front);
        if (front > 0) {
            System.arraycopy(old, 0, data, old.length-front, back+1);
        }
        front = 0;
        back = size - 1;
    }

    @Override
    public int remove() {
        if(size == 0) {
            throw new NoSuchElementException();
        }
        int x = data[front];
        front = (front + 1) % data.length;
        size--;
        return x;
    }

    @Override
    public int front() {
        if(size == 0) {
            throw new NoSuchElementException();
        }
        return data[front];
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    public String toString() {
        StringBuilder s = new StringBuilder("");
        for (int i = 0; i < size; i++) {
            s.append(data[(front+i)%data.length]).append(", ");
        }
        s.append("size = ").append(size);
        return s.toString();
    }
}
