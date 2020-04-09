package Kapitel_2;

public class LinkedList implements List {
    private Node head;
    private int size;

    public LinkedList() {
        clear();
    }

    public LinkedList(List list) {
        clear();
        append(list);
    }

    public final void clear() {
        head = new Node(0, null);
        size = 0;
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
        Node p = head;
        for (int i = 0; i < idx; i++) {
            p = p.next;
        }
        p.next = new Node(x, p.next);
        size++;
    }

    public int set(int idx, int x) {
        if (idx < 0 || idx >= size) {
            throw new IndexOutOfBoundsException();
        }
        Node p = head.next;
        for(int i = 0; i < idx; i++) {
            p = p.next;
        }
        int old = p.data;
        p.data = x;
        return old;
    }

    public int get(int idx) {
        if(idx < 0 || idx >= size) {
            throw new IndexOutOfBoundsException();
        }
        Node p = head.next;
        for (int i = 0; i < idx; i++) {
            p = p.next;
        }
        return p.data;
    }

    public void remove(int idx) {
        if(idx < 0 || idx >= size) {
            throw new IndexOutOfBoundsException();
        }
        Node p = head;
        for (int i = 0; i < idx; i++) {
            p = p.next;
        }
        p.next = p.next.next;
        size--;
    }

    public boolean removeElement(int x) {
        Node p = head;
        int start = size;
        boolean elementFound = false;
        for (int i = 0; i < start; i++) {
            p = p.next;
            if (p.data == x) {
                if(elementFound) {
                    return true;
                }
                elementFound = true;
                remove(i);
            }
        }
        return false;
    }

    public void removeAllElement(int x) {
        while(removeElement(x));
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("");
        for(Node p = head.next; p != null; p = p.next) {
            s.append(p.data).append(", ");
        }
        s.append("size = ").append(size);
        return s.toString();
    }

    private static class Node {
        Node next;
        int data;
        Node(int x, Node p) {
            data = x;
            next = p;
        }
    }
}
