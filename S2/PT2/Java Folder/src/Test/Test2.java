package Test;

public class Test2 {
    static int i = 0;
    public static void main(String[] args) {
        hello(2);
    }

    public static int hello(int p) {
        i++;
        System.out.println(i);
        return hello(p);
    }
}
