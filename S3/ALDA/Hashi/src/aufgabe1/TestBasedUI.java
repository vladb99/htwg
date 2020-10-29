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
            } else if (cmd.startsWith("read ")) {
                BufferedReader reader;
                try {
                    String[] splitted = cmd.split(" ");
                    if (splitted.length == 3) {
                        int n = Integer.parseInt(splitted[1]);
                        reader = new BufferedReader(new FileReader("/Users/vladb/Git/htwg/S3/ALDA/Hashi/src/aufgabe1/" + splitted[2]));
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
                    } else if (splitted.length == 2) {
                        reader = new BufferedReader(new FileReader("/Users/vladb/Git/htwg/S3/ALDA/Hashi/src/aufgabe1/" + splitted[1]));
                        String line = reader.readLine();
                        while (line != null) {
                            String[] words = line.split(" ");
                            String german = words[0];
                            String english = words[1];
                            dict.insert(german, english);
                            line = reader.readLine();
                        }
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
            }
        }
    }
}
