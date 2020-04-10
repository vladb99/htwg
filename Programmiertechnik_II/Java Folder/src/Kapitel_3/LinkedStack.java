package Kapitel_3;

import Kapitel_2.LinkedList;

import java.util.EmptyStackException;

public class LinkedStack implements Stack {
    private Node top;

    public LinkedStack() {
        top = null;
    }

    @Override
    public void push(int x) {
        top = new Node(x,top);
    }

    @Override
    public int pop() {
        if (top == null) {
            throw new EmptyStackException();
        }
        int x = top.data;
        top = top.next;
        return x;
    }

    @Override
    public int top() {
        if (top == null) {
            throw new EmptyStackException();
        }
        return top.data;
    }

    @Override
    public boolean isEmpty() {
        return top == null;
    }

    private static class Node {
        int data;
        Node next;
        Node(int x, Node n) {
            data = x;
            next = n;
        }
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder("");
        LinkedStack r = new LinkedStack();
        r.push(top.data);
        for(Node p = top.next; p != null; p = p.next) {
            r.push(p.data);
        }
        for(Node p = r.top; p != null; p = p.next) {
            if (p.next == null) {
                s.append(p.data);
            } else {
                s.append(p.data).append(", ");
            }
        }
        s.append(" = top");
        return s.toString();
    }
}
