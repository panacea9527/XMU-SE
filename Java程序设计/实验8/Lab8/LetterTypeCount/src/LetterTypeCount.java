import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.TreeSet;
import java.util.Scanner;

public class LetterTypeCount {
    public static void main(String[] args) {
        // create HashMap to store String keys and Integer values
        Map<Character, Integer> myMap = new HashMap<>();

        createMap(myMap); // create map based on user input
        displayMap(myMap); // display map content
    }

    // create map from user input
    private static void createMap(Map<Character, Integer> map) {
        Scanner scanner = new Scanner(System.in); // create scanner
        System.out.println("Enter a string:"); // prompt for user input
        String input = scanner.nextLine();

        // tokenize the input
        String[] tokens = input.split(" ");

        // 处理输入文本
        for (char ch : input.toCharArray()) {
            char character = Character.toLowerCase(ch); // 将字符转换为小写
            if (Character.isLetter(character)) {
                if (map.containsKey(character)) { // 检查映射中是否已存在该字符
                    int count = map.get(character);
                    map.put(character, count + 1); // 增加计数
                } else {
                    map.put(character, 1);
                }
            }
        }
    }

    // display map content
    private static void displayMap(Map<Character, Integer> map) {
        Set<Character> keys = map.keySet(); // get keys

        // sort keys
        TreeSet<Character> sortedKeys = new TreeSet<>(keys);

        System.out.printf("%nMap contains:%nKey\t\tValue%n");

        // generate output for each key in map
        for (Character key : sortedKeys) {
            System.out.printf("%-10s%10s%n", key, map.get(key));
        }

        System.out.printf(
                "%nsize: %d%nisEmpty: %b%n", map.size(), map.isEmpty());
    }
}
