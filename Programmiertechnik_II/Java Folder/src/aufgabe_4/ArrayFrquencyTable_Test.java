package aufgabe_4;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;

/**
 *
 * @author vladb
 * @since 18.4.2020
 */
public class ArrayFrquencyTable_Test {

    public static void main(String[] args) throws FileNotFoundException, IOException {
        test1();
        test2();
    }

    private static void test1() {
        // Test von add:
        FrequencyTable<String> tab1 = new ArrayFrequencyTable<>();
        tab1.add("das");
        tab1.add("ist");
        tab1.add("ein",2);
        tab1.add("Test");
        tab1.add("Test",2);

        System.out.println("Soll: Test:3");
        System.out.println("Ist:  " + tab1.get(0) + "\n");

        System.out.println("Soll: ein:2");
        System.out.println("Ist:  " + tab1.get(1) + "\n");

        System.out.println("Soll: 2");
        System.out.println("Ist:  " + tab1.get("ein") +  "\n");

        System.out.println("Soll: 1");
        System.out.println("Ist:  " + tab1.get("ist") +  "\n");

        System.out.println("Soll: 3");
        System.out.println("Ist:  " + tab1.get("Test") +  "\n");

        System.out.println("Soll: {Test:3, ein:2, das:1, ist:1, } size = 4");
        System.out.println("Ist:  " + tab1 +  "\n");

        // Test von addAll:
        FrequencyTable<String> tab2 = new ArrayFrequencyTable<>();
        tab2.add("das",2);
        tab2.add("ist",4);
        tab2.add("kurzer");
        tab2.add("Text");
        tab2.add("Test",2);
        tab1.addAll(tab2);
        System.out.println("Soll: {ist:5, Test:5, das:3, ein:2, kurzer:1, Text:1, } size = 6");
        System.out.println("Ist:  " + tab1 +  "\n");

        // Test von copyMostFrequent und copyLeastFrequent:
        tab1.collectMostFrequent(tab2);
        System.out.println("Soll: {ist:5, Test:5, } size = 2");
        System.out.println("Ist:  " + tab2 +  "\n");
        tab1.collectLeastFrequent(tab2);
        System.out.println("Soll: {kurzer:1, Text:1, } size = 2");
        System.out.println("Ist:  " + tab2 +  "\n");
    }

    private static void test2() throws FileNotFoundException, IOException {
        FrequencyTable<String> tab = new ArrayFrequencyTable<>();

        long start = System.nanoTime(); // aktuelle Zeit in nsec
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

        long end = System.nanoTime();
        double elapsedTime = (double)(end-start)/1.0e06; // Zeit in msec

        // Ausageb der 100 hÃ¤ufigsten WÃ¶rter:
        for (int i = 0; i < 100; i++) {
            if (tab.get(i) == null)
                break;
            System.out.println(tab.get(i));
        }

        System.out.println("");
        System.out.println("BenÃ¶tigte Zeit in msec: " + elapsedTime);
    }
}