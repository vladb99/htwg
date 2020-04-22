package Kapitel_2;

public class Test {
    public static void main(String[] args) {
        List l2 = new LinkedList();
        l2.add(1);
        l2.add(7);
        l2.add(6);

        LinkedList l = new LinkedList(l2);

        System.out.println(l);

        l.removeElement(1);

        System.out.println(l);

    }
}
