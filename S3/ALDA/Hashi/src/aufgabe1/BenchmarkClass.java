package aufgabe1;

import java.io.BufferedReader;
import java.io.FileReader;

public class BenchmarkClass {
    private static final int size = 16000;
    private static Dictionary<String, String> dict = new SortedArrayDictionary<>();
    //private static Dictionary<String, String> dict = new HashDictionary<>();

    private static final int loops = 100;

    public static void main(String[] args) {
        measureInit();
    }

    private static void cleanDict() {
        for (Dictionary.Entry<String, String> entry : dict) {
            dict.remove(entry.getKey());
        }
    }

    private static void measureInit() {
        double sumElapsedTime = 0;

        for (int i = 0; i < loops; i++) {
            BufferedReader reader;
            try {
                dict = new SortedArrayDictionary<>();
                reader = new BufferedReader(new FileReader("/Users/vladb/Git/htwg/S3/ALDA/Hashi/src/aufgabe1/dtengl.txt"));
                String line = reader.readLine();
                int j = 0;

                long start = System.nanoTime();

                while (line != null && j < size) {
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
        System.out.println("");
        System.out.println("Aufbau : " + average);
    }
}
