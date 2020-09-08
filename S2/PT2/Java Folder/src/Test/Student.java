package Test;

public class Student extends Person {
    public void say() {
        System.out.println("student");
    }

    public static void main(String[] args) {
        Person p2 = new Student();
        ((Person)p2).say();

    }
}
