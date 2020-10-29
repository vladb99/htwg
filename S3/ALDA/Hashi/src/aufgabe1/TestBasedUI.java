package aufgabe1;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOError;
import java.io.IOException;
import java.util.Scanner;

public class TestBasedUI {
    public static void main(String[] args)  {
        Scanner scan = new Scanner(System.in);
        Dictionary<String, String> dict = new SortedArrayDictionary<>();

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
                    System.out.println("Falsche Implementation!");
                }
            }
            else if (cmd.startsWith("read ")) {
                BufferedReader reader;
                try {
                    String[] splitted = cmd.split(" ");
                    if (splitted.length == 3) {
                        int n = Integer.parseInt(splitted[1]);
                        reader = new BufferedReader(new FileReader("/Users/vladb/Git/htwg/S3/ALDA/Hashi/src/aufgabe1/" + splitted[2]));
                        String line = reader.readLine();
                        int i = 0;
                        while (line != null && i < n) {
                            System.out.println(line);
                            line = reader.readLine();
                            i++;
                        }
                    } else if (splitted.length == 2) {
                        reader = new BufferedReader(new FileReader("/Users/vladb/Git/htwg/S3/ALDA/Hashi/src/aufgabe1/" + splitted[1]));
                        String line = reader.readLine();
                        while (line != null) {
                            System.out.println(line);
                            line = reader.readLine();
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
