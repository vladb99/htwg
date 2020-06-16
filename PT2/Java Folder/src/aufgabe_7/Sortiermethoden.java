package aufgabe_7;

import aufgabe_4.BlackCard;
import aufgabe_4.Card;
import aufgabe_4.RedCard;
import aufgabe_6.SerielleTaetigkeit;

import javax.sound.midi.Soundbank;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class Sortiermethoden {
    private static final int N = 100;
    private static final int M = 1000;

    public static void main(String[] args) throws IOException {
        //test1_2();
        //test3();
        test4();
    }

    /**
     *  Implementiert den vierten Test. Erstellt eine Liste mit gemischten Karten und sortiert dann die Liste zwei Mal
     */
    private static void test4()
    {
        long start = System.nanoTime(); // aktuelle Zeit in nsec

        List<Card> cardTab = new LinkedList<>();

        Random rand = new Random();
        for (int i = 0; i < 10000; i++) {
            if (rand.nextInt() % 2 == 0) {
                RedCard c = new RedCard();
                cardTab.add(c);
            } else {
                BlackCard c = new BlackCard();
                cardTab.add(c);
            }
        }

        //System.out.println(cardTab);
        hybrid_quicksort(cardTab, true);
        //Arrays.sort(cardTab.toArray());
        //System.out.println(cardTab);


        long end = System.nanoTime();
        double elapsedTime = (double)(end-start)/1.0e06; // Zeit in msec
        System.out.println("");
        System.out.println("Benoetigte Zeit in msec: " + elapsedTime);

        //Sortiert

        start = System.nanoTime(); // aktuelle Zeit in nsec

        //System.out.println(cardTab);
        hybrid_quicksort(cardTab, true);
        //Arrays.sort(cardTab.toArray());
        //System.out.println(cardTab);

        end = System.nanoTime();
        elapsedTime = (double)(end-start)/1.0e06; // Zeit in msec
        System.out.println("");
        System.out.println("Benoetigte Zeit in msec: " + elapsedTime);
    }

    /**
     * Implementiert Tests 1 und 2. Erstellt eine Liste mit zufälligen Zahlen und sortiert diese
     */
    private static void test1_2()
    {
        List<Integer> a = new LinkedList<>();
        for (int i = 0; i < M; ++i)
        {
            a.add((int)(Math.random() * M));
        }
        System.out.println(a);
        hybrid_quicksort(a, true);
        System.out.println(a);
    }

    /**
     * Implementiert Test 3. Erstellt eine Liste mit allen Wörtern aus der .txt Datei und sortiert diese
     * @throws IOException
     */
    private static void test3() throws IOException {
        List<String> tab = new LinkedList<>();

        long start = System.nanoTime(); // aktuelle Zeit in nsec
        LineNumberReader in;
        in = new LineNumberReader(new FileReader("Kafka_Der_Prozess.txt"));
        String line;

        // Text einlesen und HÃ¤figkeiten aller WÃ¶rter bestimmen:
        while ((line = in.readLine()) != null) {
            String[] wf = line.split("[^a-z^A-Z^ÃŸ^Ã¤^Ã¶^Ã¼^Ã„^Ã–^Ãœ]+");
            for (String w: wf) {
                if (w.length() == 0 || w.length() == 1)
                    continue;
                tab.add(w);
            }
        }
        System.out.println(tab);
        hybrid_quicksort(tab, true);
        System.out.println(tab);

        long end = System.nanoTime();
        double elapsedTime = (double)(end-start)/1.0e06; // Zeit in msec
    }

    /**
     * Quicksort
     * @param list, die zu sortierende Liste
     * @param threeMedStrat, wenn true dann QuickSort mit 3-Median
     * @param <T>, generischer Typ
     */
    private static <T extends Comparable<? super T>> void hybrid_quicksort(List<T> list, boolean threeMedStrat)
    {
        hybrid_quicksort(list, 0, list.size() - 1, threeMedStrat);
    }

    /**
     * Insertionsort
     * @param list, die zu sortierende Liste
     * @param <T>, generischer Typ
     */
    private static <T extends Comparable<? super T>> void insertionSort(List<T> list)
    {
        insertionSort(list, 0, list.size() - 1);
    }

    /**
     * QuickSort ohne Endrekursion
     * @param list, die zu sortierende Liste
     * @param li, Index vom linken Element
     * @param re, Index vom rechten Element
     * @param threeMedStrat, wenn true dann QuickSort mit 3-Median
     * @param <T>, generischer Typ
     */
    private static <T extends Comparable<? super T>> void hybrid_quicksort(List<T> list, int li, int re, boolean threeMedStrat)
    {
        /*if (re > li)
        {
            if (re - li < N)
            {
                insertionSort(list, li, re);
            }
            else
            {
                int i = partition(list, li, re);
                hybrid_quicksort(list, li, i-1);
                hybrid_quicksort(list, i+1, re);
            }
        }
         */
        while (re > li)
        {
            if (re - li < N)
            {
                insertionSort(list, li, re);
                break;
            }
            else
            {
                /*
                int i = partition(list, li, re);
                hybrid_quicksort(list, li, i-1);
                li = i + 1;
                 */
                int i = partition(list, li, re, threeMedStrat);
                if (i-li < re-i) {
                    hybrid_quicksort(list, li, i-1, threeMedStrat);
                    li = i+1;
                }
                else
                {
                    hybrid_quicksort(list, i+1, re, threeMedStrat);
                    re = i-1;
                }
            }
        }
    }

    /**
     * Partitioniert die Liste
     * @param list, die zu sortierende Liste
     * @param li, Index vom linken Element
     * @param re, Index vom rechten Element
     * @param threeMedStrat, wenn true dann QuickSort mit 3-Median
     * @param <T>, generischer Typ
     * @return Index vom Pivotelement
     */
    private static <T extends Comparable<? super T>> int partition(List<T> list, int li, int re, boolean threeMedStrat)
    {
        if (threeMedStrat)
        {
            int mid = (li + re) / 2;
            getMedian(list, li, re, mid);
            swap(list, re, mid);
        }

        T v = list.get(re);
        int i = li-1;
        int j = re;
        while (true) {
            do i++; while (list.get(i).compareTo(v) < 0);
            do j--; while (j >= li && list.get(j).compareTo(v) > 0);
            if (i >= j)
                break;
            swap(list, i, j);
        }
        list.set(re, list.get(i));
        list.set(i, v);
        return i;
    }

    /**
     * Stellt den Median in die Mitte
     * @param list, die Liste in der der Median 'in der Mitte' stehen soll
     * @param li, Index vom linken Element
     * @param re, Index vom rechten Element
     * @param mid, Index vom mittleren Element
     * @param <T>, generischer Typ
     */
    private static <T extends Comparable<? super T>> void getMedian(List<T> list, int li, int re, int mid)
    {
        T liElm = list.get(li);
        T reElm = list.get(re);
        T midElm = list.get(mid);

        if (reElm.compareTo(liElm) < 0)
        {
            swap(list, li, re);
        }
        if (midElm.compareTo(liElm) < 0)
        {
            swap(list, mid, li);
        }
        if (reElm.compareTo(midElm) < 0)
        {
            swap(list, re, mid);
        }
    }

    /**
     * Vertauscht die zwei Positionen von einer Liste
     * @param list, die Liste in der die Positionen vertauscht werden sollen
     * @param i, Index vom ersten Element
     * @param j, Index vom zweiten Element
     * @param <T>, generischer Typ
     */
    private static <T> void swap(List<T> list, int i, int j) {
        T t = list.get(i);
        list.set(i, list.get(j));
        list.set(j, t);
    }

    /**
     * InsertionSort
     * @param list, die zu sortierende Liste
     * @param li, Index vom linken Element
     * @param re, Index vom rechten Element
     * @param <T>, generischer Typ
     */
    private static <T extends Comparable<? super T>> void insertionSort(List<T> list, int li, int re)
    {
        for (int i = li + 1; i <= re; i++) {
            T v = list.get(i);
            int j = i - 1;
            while (j >= li && list.get(j).compareTo(v) > 0) {
                list.set(j + 1, list.get(j));
                j--;
            }
            list.set(j + 1, v);
        }
    }
}
