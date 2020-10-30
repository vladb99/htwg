package aufgabe1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.LinkedList;
import java.util.Scanner;

public class TestBasedUI {
    private static Dictionary<String, String> dict = new SortedArrayDictionary<>();

    public static void main(String[] args)  {
        Scanner scan = new Scanner(System.in);

        while (true) {
            System.out.print("Befehl eingeben: ");
            String cmd = scan.nextLine();

            if (cmd.startsWith("create ")) {
                String[] splitted = cmd.split(" ");
                if (splitted[1].equals("SortedArrayDictionary")) {
                    dict = new SortedArrayDictionary<>();
                } else if (splitted[1].equals("HashDictionary")) {
                    dict = new HashDictionary<>();
                } else {
                    System.out.println("Wrong implementation!");
                }
            } else if (cmd.startsWith("read ")) {
                try {
                    String[] splitted = cmd.split(" ");
                    if (splitted.length == 3) {
                        int n = Integer.parseInt(splitted[1]);
                        createDict(n, splitted[2]);
                    } else if (splitted.length == 2) {
                        createDict(16000, splitted[1]);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            } else if (cmd.equals("p")) {
                System.out.println(dict);
            } else if (cmd.startsWith("s ")) {
                String[] splitted = cmd.split(" ");
                System.out.println(dict.search(splitted[1]));
            } else if (cmd.startsWith("i ")) {
                String[] splitted = cmd.split(" ");
                dict.insert(splitted[1], splitted[2]);
            } else if (cmd.startsWith("r ")) {
                String[] splitted = cmd.split(" ");
                dict.remove(splitted[1]);
            } else if (cmd.equals("exit")) {
                System.exit(1);
            } else if (cmd.equals("b")) {
                System.out.println("SortedArrayDictionary");
                benchmarkCreation(8000, 100, "Aufbau 8000: ", Type.sorted);
                benchmarkCreation(16000, 100, "Aufbau 16000: ", Type.sorted);
                benchmarkSearchSuccess(8000, 1000, "Search Success 8000: ", Type.sorted, true);
                benchmarkSearchSuccess(16000, 1000, "Search Success 16000: ", Type.sorted, true);
                benchmarkSearchSuccess(8000, 1000, "Search Failure 8000: ", Type.sorted, false);
                benchmarkSearchSuccess(16000, 1000, "Search Failure 16000: ", Type.sorted, false);
                System.out.println("");
                System.out.println("HashDictionary");
                benchmarkCreation(8000, 5000, "Aufbau 8000: ", Type.hash);
                benchmarkCreation(16000, 5000, "Aufbau 16000: ", Type.hash);
                benchmarkSearchSuccess(8000, 1000, "Search Success 8000: ", Type.hash, true);
                benchmarkSearchSuccess(16000, 1000, "Search Success 16000: ", Type.hash, true);
                benchmarkSearchSuccess(8000, 1000, "Search Failure 8000: ", Type.hash, false);
                benchmarkSearchSuccess(16000, 1000, "Search Failure 16000: ", Type.hash, false);
                System.out.println("");
            }
        }
    }

    private static void createDict(int n, String file) {
        BufferedReader reader;
        try {
            reader = new BufferedReader(new FileReader("/Users/vladb/Git/htwg/S3/ALDA/Hashi/src/aufgabe1/" + file));
            String line = reader.readLine();
            int i = 0;
            while (line != null && i < n) {
                String[] words = line.split(" ");
                String german = words[0];
                String english = words[1];
                dict.insert(german, english);
                line = reader.readLine();
                i++;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void initDict(Type type) {
        switch (type) {
            case sorted:
                dict = new SortedArrayDictionary<>();
                break;
            case hash:
                dict = new HashDictionary<>();
                break;
            case binary:
                System.out.println("Not yet implemented");
                break;
        }
    }

    private static void benchmarkSearchSuccess(int n, int loops, String msg, Type type, boolean success) {
        initDict(type);
        createDict(n, "dtengl.txt");
        LinkedList<String> list = wordsInList(n, success);
        double sumElapsedTime = 0;

        for (int i = 0; i < loops; i++) {
            long start = System.nanoTime();
            for (String word : list) {
                dict.search(word);
            }
            long end = System.nanoTime();
            double elapsedTime = (double) (end - start) / 1.0e06;
            sumElapsedTime += elapsedTime;
        }

        double average = sumElapsedTime / loops;
        System.out.println(msg + "" + average);
    }

    private static LinkedList<String> wordsInList(int n, boolean success) {
        BufferedReader reader;
        LinkedList<String> list = new LinkedList<>();
        try {
            reader = new BufferedReader(new FileReader("/Users/vladb/Git/htwg/S3/ALDA/Hashi/src/aufgabe1/dtengl.txt"));
            String line = reader.readLine();
            int i = 0;
            while (line != null && i < n) {
                String[] words = line.split(" ");
                String german = words[0];
                String english = words[1];

                if (success) {
                    list.add(german);
                } else {
                    list.add(english);
                }

                line = reader.readLine();
                i++;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return list;
    }

    private static void benchmarkCreation(int n, int loops, String msg, Type type) {
        double sumElapsedTime = 0;

        for (int i = 0; i < loops; i++) {
            BufferedReader reader;
            try {
                initDict(type);
                reader = new BufferedReader(new FileReader("/Users/vladb/Git/htwg/S3/ALDA/Hashi/src/aufgabe1/dtengl.txt"));
                String line = reader.readLine();
                int j = 0;

                long start = System.nanoTime();

                while (line != null && j < n) {
                    String[] words = line.split(" ");
                    String german = words[0];
                    String english = words[1];
                    dict.insert(german, english);
                    line = reader.readLine();
                    j++;
                }

                long end = System.nanoTime();
                double elapsedTime = (double)(end-start)/1.0e06;
                sumElapsedTime += elapsedTime;

            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        double average = sumElapsedTime / loops;
        System.out.println(msg + "" + average);
    }

    private enum Type {
        sorted, hash, binary;
    }
}
