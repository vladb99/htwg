package aufgabe_4;

public class LinkedListFrequencyTable<T> extends AbstractFrequencyTable<T> {
    private Node<T> begin;
    private Node<T> end;
    private int size;

    public LinkedListFrequencyTable() {
        clear();
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public void clear() {
        size = 0;
        begin = new Node<>(new Element<T>(null, 0), end,null);
        end = new Node<>(new Element<T>(null, 0), null, begin);
    }

    @Override
    public void add(T d, int f) {
        boolean fqSummed = false;

        Node<T> p = begin.next;
        for (int i = 0; i < size; i++) {
            if(d.equals(p.data.getData())) {
                fqSummed = true;
                p.data.addFrequency(f);
            }
            p = p.next;
        }

        if(!fqSummed) {
            Node<T> r = new Node<>(new Element<T>(d, f), end, end.prev);
            r.prev.next = r;
            end.prev = r;
            size++;
        }

        p = end.prev;
        for (int i = size - 1; i > 0; i--) {
            if(p.data.getFrequency() > p.prev.data.getFrequency()) {
                Element<T> temp = p.data;
                p.data = p.prev.data;
                p.prev.data = temp;
            }
            p = p.prev;
        }
    }

    @Override
    public Element<T> get(int pos) {
        if(pos < 0 || pos >= size) {
            throw new IndexOutOfBoundsException();
        }
        if (size == 0) {
            throw new IllegalStateException();
        }
        Node<T> p = begin.next;
        for(int i = 0; i < pos; i++) {
            p = p.next;
        }
        return p.data;
    }

    @Override
    public int get(T d) {
        Node<T> p = begin.next;
        for(int i = 0; i < size; i++) {
            if(d.equals(p.data.getData())) {
                return p.data.getFrequency();
            }
            p = p.next;
        }
        return 0;
    }

    private static class Node<T> {
        private Node<T> next;
        private Node<T> prev;
        private Element<T> data;

        public Node(Element<T> d, Node<T> n, Node<T> p) {
            data = d;
            next = n;
            prev = p;
        }
    }
}
