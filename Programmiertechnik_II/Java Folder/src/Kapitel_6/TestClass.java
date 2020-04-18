package Kapitel_6;

import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

public class TestClass {
        public static void main(String[] args) {
            List<Integer> intList = new LinkedList<>();
            for (int i = 1; i <= 10; i++) {
                intList.add(i);
            }
            System.out.println(intList);
            // Reverse Iterator
            ListIterator<Integer> it
                    = intList.listIterator(intList.size());
            while (it.hasPrevious()) {
                System.out.print(it.previous() + ", ");
            }
            System.out.println();
        }
}
