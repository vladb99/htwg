package Kapitel_3;

import Kapitel_2.LinkedList;

import java.util.NoSuchElementException;

public class LinkedQueue implements Queue {

    private Node front;
    private Node back;

    public LinkedQueue() {
        front = back = null;
    }

    public boolean  isEmpty() {
        return front == null;
    }

    public void add(int x) {
        if(front == null) {
            front = back = new Node(null, x);
        } else {
            back.next = new Node(null,x);
            back = back.next;
        }
    }

    public int front() {
        if (front == null) {
            throw new NoSuchElementException();
        }
        return front.data;
    }

    public int remove() {
        if (front == null) {
            throw new NoSuchElementException();
        }
        int x = front.data;
        front = front.next;
        if (front == null) {
            back = null;
        }
        return x;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("");
        s.append("front = ");
        for(Node p = front; p != null; p = p.next) {
            s.append(p.data).append(", ");
        }
        s.deleteCharAt(s.length() - 2);
        s.append("= back");
        return s.toString();
    }

    private static class Node {
        int data;
        Node next;
        Node(Node p, int x) {
            data = x;
            next = p;
        }
    }
}
