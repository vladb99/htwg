package Kapitel_3;

import java.util.Arrays;
import java.util.EmptyStackException;

public class ArrayStack implements Stack {

    private static final int DEF_CAPACITY = 16;
    private int size;
    private int[] data;

    public ArrayStack() {
        size = 0;
        data = new int[DEF_CAPACITY];
    }

    @Override
    public void push(int x) {
        if (data.length == size) {
            data = Arrays.copyOf(data, 2*size);
        }
        data[size++] = x;
    }

    @Override
    public int pop() {
        if (size == 0) {
            throw new EmptyStackException();
        }
        return data[--size];
    }

    @Override
    public int top() {
        if (size == 0) {
            throw new EmptyStackException();
        }
        return data[size-1];
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
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
}
