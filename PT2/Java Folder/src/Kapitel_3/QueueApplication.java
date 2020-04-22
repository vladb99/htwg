package Kapitel_3;

import java.util.Scanner;

public class QueueApplication {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in); int d = in.nextInt();
        Queue q;
        if (d == 0)
            q = new ArrayQueue();
        else
            q = new LinkedQueue();
        q.add(1);
        q.add(2);
        q.add(3);
        q.add(4);
        int x = q.remove();
        System.out.println(q);
    }
}
