package aufgabe_6;

import java.util.LinkedList;
import java.util.List;

public class Person {
    private String name;
    private List<Buch> ausgelieheneBuecher = new LinkedList<>();

    public Person(String n) {
        this.name = n;
    }

    public String getName() {
        return this.name;
    }

    public boolean leihtAus(Buch b) {
        if (ausgelieheneBuecher.contains(b)) {
            return false;
        }
        if (b.getEntleiher() != null && b.getEntleiher() != this) {
            return false;
        }
        ausgelieheneBuecher.add(b);
        b.wirdAusgeliehen(this);
        return true;
    }

    public boolean gibtZurueck(Buch b) {
        if (!ausgelieheneBuecher.contains(b)) {
            return false;
        }
        ausgelieheneBuecher.remove(b);
        b.wirdZurueckGegeben();
        return true;
    }

    public void print() {
        System.out.println();
        System.out.print(name + " : ");
        for (Buch b : ausgelieheneBuecher) {
            System.out.print(b.getName() + ", ");
        }
        System.out.println();
    }
}
