package Kapitel_2;

public class DoubleLinkedList implements List {
    private Node begin;
    private Node end;
    private int size;

    public DoubleLinkedList() {
        clear();
    }

    private static class Node {
        private Node next;
        private Node prev;
        private int data;

        public Node(int x, Node n, Node p) {
            data = x;
            next = n;
            prev = p;
        }
    }

    @Override
    public void add(int x) {

    }

    @Override
    public void add(int idx, int x) {

    }

    @Override
    public int set(int idx, int x) {
        return 0;
    }

    @Override
    public int get(int idx) {
        return 0;
    }

    @Override
    public void remove(int idx) {

    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public void clear() {
        end = new Node(0, null, begin);
        begin = new Node(0, end,null);
        size = 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public void append(List list) {

    }
}
