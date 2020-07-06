package aufgabe_11;

import java.time.LocalDate;
import java.util.*;
import java.util.function.Predicate;

public class TestKlasse {
    public static void main(String[] args) {
        //Aufgabe a)
        List<Person> persList = new LinkedList<>();
        persList.add(new Person("Andy", "Mueller", LocalDate.of(1961, 2, 10)));
        persList.add(new Person("Peter", "Schneider", LocalDate.of(1959, 10, 20)));
        persList.add(new Person("Andrea", "Schmidt", LocalDate.of(1969, 3, 28)));
        persList.add(new Person("Petra", "Fischer", LocalDate.of(1961, 9, 5)));
        persList.add(new Person("Albert","Meyer", LocalDate.of(1979, 4, 12)));
        persList.add(new Person("Anton", "Wagner", LocalDate.of(1961, 7, 19)));
        persList.add(new Person("Iris", "Klein", LocalDate.of(2003, 1, 3)));

        Predicate<Person> istVolljaehrig = p -> p.getGeburtsdatum().until(LocalDate.now()).getYears() >= 18;

        for (var p : persList) {
            System.out.print(p);
            if (istVolljaehrig.test(p)) {
                System.out.print(", ist volljährig\n");
            } else {
                System.out.print(", ist nicht volljährig\n");
            }
        }

        //Aufgabe b)
        Collections.sort(persList, Comparator.comparing(Person::getGeburtsdatum));
        System.out.println("\n\n Sortiert aufsteigend:");
        persList.forEach(System.out::println);

        //Aufgabe c)
        Collections.sort(persList, Comparator.comparing(Person::getGeburtsdatum).reversed());
        System.out.println("\n\n Sortiert absteigend:");
        persList.forEach(System.out::println);

        //Aufgabe d)
        System.out.println("\n\n");
        persList.stream()
                .filter(istVolljaehrig)
                .sorted(Comparator.comparing(Person::getGeburtsdatum))
                .forEach(p-> System.out.println(p.getGeburtsdatum()));

        //Aufgabe e)
        System.out.println("\n\n");
        persList.stream()
                .filter(p -> p.getVorname().startsWith("A"))
                .sorted(Comparator.comparing(Person::getGeburtsdatum))
                .limit(3)
                .forEach(System.out::println);
    }
}

