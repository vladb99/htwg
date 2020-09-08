package Test;

import aufgabe_4.ArrayFrequencyTable;
import aufgabe_4.Element;
import aufgabe_4.FrequencyTable;
import aufgabe_4.LinkedListFrequencyTable;

import java.util.Iterator;
import java.util.function.BiFunction;

public class Test {
    public static void main(String[] args) {
        /*FrequencyTable<Integer> fq = new LinkedListFrequencyTable<>();
        fq.add(2, 10);
        fq.add(5, 9);
        fq.add(7, 8);
        fq.add(1, 7);
        Iterator<Element<Integer>> it = fq.iterator();

        System.out.println(fq);
        System.out.println(it.next().getData());
        System.out.println(it.next().getData());
        it.remove();
        System.out.println(fq);
        //it.remove();
        System.out.println(it.next().getData());
        fq.add(8, 1);
        //System.out.println(it.next().getData());
        System.out.println("Hi");
        FrequencyTable<Integer> list = new ArrayFrequencyTable<>();
        list.add(2, 10);
        list.add(5, 9);
        list.add(7, 8);
        list.add(1, 7);
        Iterator<Element<Integer>> it2 = list.iterator();

        System.out.println(list);
        System.out.println(it2.next().getData());
        System.out.println(it2.next().getData());
        //it2.remove();
        System.out.println(list);
        //it2.remove();
        System.out.println(it2.next().getData());
        list.add(8, 1);
        //System.out.println(it2.next().getData());
         */
        BiFunction<Integer, Integer, Integer> add = (x,y) -> {
            if (x>=y) {
                return x;
            }
            else {
                return y;
            }
        };
        System.out.println(add.apply(4,5));

    }
}
