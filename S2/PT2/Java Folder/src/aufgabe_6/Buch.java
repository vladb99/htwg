package aufgabe_6;

public class Buch {
    private String name;
    private Person entleiher;

    public Buch(String n) {
        this.name = n;
    }

    public String getName() {
        return this.name;
    }

    public Person getEntleiher() {
        return this.entleiher;
    }

    public boolean wirdAusgeliehen(Person p) {
        if (entleiher != null) {
            return false;
        }
        entleiher = p;
        p.leihtAus(this);
        return true;
    }

    public boolean wirdZurueckGegeben() {
        if (entleiher == null) {
            return false;
        }
        Person p = entleiher;
        entleiher = null;
        p.gibtZurueck(this);
        return true;
    }

    public void print() {
        System.out.println();
        System.out.println(name + " : " + (entleiher != null ? entleiher.getName() : " "));
    }
}
