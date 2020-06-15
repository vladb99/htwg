package aufgabe_7;

import java.util.LinkedList;
import java.util.List;

public class Sortiermethoden {
    public static void main(String[] args) {
        List<Integer> a = new LinkedList<>();
        a.add(7);
        a.add(2);
        a.add(1);
        a.add(2);
        a.add(8);
        a.add(9);
        a.add(4);
        a.add(3);
        a.add(6);
        System.out.println(a);
        hybrid_quicksort(a);
        System.out.println(a);
    }

    private static <T extends Comparable<? super T>> void hybrid_quicksort(List<T> list)
    {
        hybrid_quicksort(list, 0, list.size() - 1);
    }

    private static <T extends Comparable<? super T>> void hybrid_quicksort(List<T> list, int li, int re)
    {
        if (re > li)
        {
            int i = partition(list, li, re);
            hybrid_quicksort(list, li, i-1);
            hybrid_quicksort(list, i+1, re);
        }
    }

    private static <T extends Comparable<? super T>> int partition(List<T> list, int li, int re) {
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

    public static <T> void swap(List<T> list, int i, int j) {
        T t = list.get(i);
        list.set(i, list.get(j));
        list.set(j, t);
    }

    private static <T extends Comparable<T>> void insertionSort(T[] a, int li, int re)
    {

    }
}
