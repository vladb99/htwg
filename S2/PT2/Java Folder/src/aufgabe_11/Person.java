package aufgabe_11;

import java.time.LocalDate;

public class Person {
    private String vorname;
    private String nachname;
    private LocalDate geburtsdatum;

    public Person(String vorname, String nachname, LocalDate geburtsdatum) {
        this.vorname = vorname;
        this.nachname = nachname;
        this.geburtsdatum = geburtsdatum;
    }

    public String getNachname() {
        return nachname;
    }

    public void setNachname(String nachname) {
        this.nachname = nachname;
    }

    public LocalDate getGeburtsdatum() {
        return geburtsdatum;
    }

    public void setGeburtsdatum(LocalDate geburtsdatum) {
        this.geburtsdatum = geburtsdatum;
    }

    public String getVorname() {
        return vorname;
    }

    public void setVorname(String vorname) {
        this.vorname = vorname;
    }

    @Override
    public String toString() {
        return new StringBuilder().append(vorname)
                .append(" ")
                .append(nachname)
                .append(" geboren am ")
                .append(geburtsdatum)
                .toString();
    }
}
