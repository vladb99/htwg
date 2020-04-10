package Kapitel_3;

import java.util.Scanner;

public class StackApplication {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in); int d = in.nextInt();
        Stack s;
        if (d == 0)
            s = new ArrayStack();
        else
            s = new LinkedStack();
        s.push(3);
        s.push(2);
        s.push(1);
        System.out.println(s);
    }
}
