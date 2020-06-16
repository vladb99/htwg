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
import java.lang.reflect.Array;
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
        int anz = 100000;

        //List<Card> cardTab = new LinkedList<>();
        Card[] cardTab = new Card[anz];


        Random rand = new Random();
        for (int i = 0; i < anz; i++) {
            if (rand.nextInt() % 2 == 0) {
                RedCard c = new RedCard();
                //cardTab.add(c);
                cardTab[i] = c;
            } else {
                BlackCard c = new BlackCard();
                //cardTab.add(c);
                cardTab[i] = c;
            }
        }

        //System.out.println(Arrays.asList(cardTab));
        hybrid_quicksort(cardTab, false);
        //Arrays.sort(cardTab);
        //System.out.println(Arrays.asList(cardTab));


        long end = System.nanoTime();
        double elapsedTime = (double)(end-start)/1.0e06; // Zeit in msec
        System.out.println("");
        System.out.println("Benoetigte Zeit in msec: " + elapsedTime);

        //Sortiert

        start = System.nanoTime(); // aktuelle Zeit in nsec

        //System.out.println(cardTab);
        hybrid_quicksort(cardTab, false);
        //Arrays.sort(cardTab);
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
        Integer[] a = new Integer[M];
        for (int i = 0; i < M; ++i)
        {
            a[i] = (int)(Math.random() * M);
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
        String[] list = new String[tab.size()];

        for (int i = 0; i < tab.size(); i++)
        {
            list[i] = tab.get(i);
        }

        System.out.println(tab);
        hybrid_quicksort(list, true);
        System.out.println(Arrays.asList(list));
    }

    /**
     * Quicksort
     * @param list, die zu sortierende Liste
     * @param threeMedStrat, wenn true dann QuickSort mit 3-Median
     * @param <T>, generischer Typ
     */
    private static <T extends Comparable<T>> void hybrid_quicksort(T[] list, boolean threeMedStrat)
    {
        hybrid_quicksort(list, 0, list.length - 1, threeMedStrat);
    }

    /**
     * Insertionsort
     * @param list, die zu sortierende Liste
     * @param <T>, generischer Typ
     */
    private static <T extends Comparable<T>> void insertionSort(T[] list)
    {
        insertionSort(list, 0, list.length - 1);
    }

    /**
     * QuickSort ohne Endrekursion
     * @param list, die zu sortierende Liste
     * @param li, Index vom linken Element
     * @param re, Index vom rechten Element
     * @param threeMedStrat, wenn true dann QuickSort mit 3-Median
     * @param <T>, generischer Typ
     */
    private static <T extends Comparable<T>> void hybrid_quicksort(T[] list, int li, int re, boolean threeMedStrat)
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
    private static <T extends Comparable<T>> int partition(T[] list, int li, int re, boolean threeMedStrat)
    {
        if (threeMedStrat)
        {
            int mid = (li + re) / 2;
            getMedian(list, li, re, mid);
            swap(list, re, mid);
        }

        T v = list[re];

        int i = li-1;
        int j = re;
        while (true) {
            do i++; while (list[i].compareTo(v) < 0);
            do j--; while (j >= li && list[j].compareTo(v) > 0);
            if (i >= j)
                break;
            swap(list, i, j);
        }
        list[re] = list[i];
        list[i] = v;
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
    private static <T extends Comparable<T>> void getMedian(T[] list, int li, int re, int mid)
    {
        T liElm = list[li];
        T reElm = list[re];
        T midElm = list[mid];

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
    private static <T> void swap(T[] list, int i, int j) {
        T t = list[i];
        list[i] = list[j];
        list[j] = t;
    }

    /**
     * InsertionSort
     * @param list, die zu sortierende Liste
     * @param li, Index vom linken Element
     * @param re, Index vom rechten Element
     * @param <T>, generischer Typ
     */
    private static <T extends Comparable<T>> void insertionSort(T[] list, int li, int re)
    {
        for (int i = li + 1; i <= re; i++) {
            T v = list[i];
            int j = i - 1;
            while (j >= li && list[j].compareTo(v) > 0) {
                list[j + 1] = list[j];
                j--;
            }
            list[j + 1] = v;
        }
    }
}
