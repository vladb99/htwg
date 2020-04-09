package aufgabe_1_und_2;

public class LinkedListFrequencyTable extends AbstractFrequencyTable {
    private Node begin;
    private Node end;
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
        begin = new Node(new Word("", 0), end,null);
        end = new Node(new Word("", 0), null, begin);
    }

    @Override
    public void add(String w, int f) {
        boolean fqSummed = false;

        Node p = begin.next;
        for (int i = 0; i < size; i++) {
            if(w.equals(p.word.getWord())) {
                fqSummed = true;
                p.word.addFrequency(f);
            }
            p = p.next;
        }

        if(!fqSummed) {
            Node r = new Node(new Word(w, f), end, end.prev);
            r.prev.next = r;
            end.prev = r;
            size++;
        }

        p = end.prev;
        for (int i = size - 1; i > 0; i--) {
            if(p.word.getFrequency() > p.prev.word.getFrequency()) {
                Word temp = p.word;
                p.word = p.prev.word;
                p.prev.word = temp;
            }
            p = p.prev;
        }
    }

    @Override
    public Word get(int pos) {
        if(pos < 0 || pos >= size) {
            throw new IndexOutOfBoundsException();
        }
        if (size == 0) {
            throw new IllegalStateException();
        }
        Node p = begin.next;
        for(int i = 0; i < pos; i++) {
            p = p.next;
        }
        return p.word;
    }

    @Override
    public int get(String w) {
        Node p = begin.next;
        for(int i = 0; i < size; i++) {
            if(w.equals(p.word.getWord())) {
                return p.word.getFrequency();
            }
            p = p.next;
        }
        return 0;
    }

    private static class Node {
        private Node next;
        private Node prev;
        private Word word;

        public Node(Word w, Node n, Node p) {
            word = w;
            next = n;
            prev = p;
        }
    }
}
