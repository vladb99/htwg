package aufgabe_7;

import java.util.LinkedList;
import java.util.List;
import java.util.Random;

public class Sortiermethoden {
    private static final int N = 100;

    public static void main(String[] args) {
        List<Integer> a = new LinkedList<>();
        Random r = new Random();
        for (int i = 0; i < 1000; ++i)
        {
            a.add(r.nextInt(200));
        }

        System.out.println(a);
        hybrid_quicksort(a, true);
        System.out.println(a);
    }

    private static <T extends Comparable<? super T>> void hybrid_quicksort(List<T> list, boolean threeMedStrat)
    {
        hybrid_quicksort(list, 0, list.size() - 1, threeMedStrat);
    }

    private static <T extends Comparable<? super T>> void insertionSort(List<T> list)
    {
        insertionSort(list, 0, list.size() - 1);
    }

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
                } else {
                    hybrid_quicksort(list, i+1, re, threeMedStrat);
                    re = i-1;
                }
            }
        }
    }

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

    private static <T> void swap(List<T> list, int i, int j) {
        T t = list.get(i);
        list.set(i, list.get(j));
        list.set(j, t);
    }

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
