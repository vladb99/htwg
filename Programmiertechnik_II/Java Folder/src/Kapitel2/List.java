package Kapitel2;

public interface List {
    void add(int x);
    void add(int idx, int x);
    int set(int idx, int x);
    int get(int idx);
    void remove(int idx);
    int size();
    void clear();
    boolean isEmpty();
    void append(List list);
}
