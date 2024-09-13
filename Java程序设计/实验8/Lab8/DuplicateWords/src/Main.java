import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入一个句子：");

        String input = scanner.nextLine();
        input = input.toLowerCase(); // 转换为小写
        input = input.replaceAll("[^a-z\\d\\s]", ""); // 去除标点符号，保留字母、数字和空格

        String[] words = input.split("\\s+"); // 根据空格分割单词

        Map<String, Integer> wordCount = new HashMap<>();
        for (String word : words) {
            if (!word.isEmpty()) { // 忽略空字符串
                wordCount.put(word, wordCount.getOrDefault(word, 0) + 1);
            }
        }

        System.out.println("重复的单词及其次数：");
        boolean foundDuplicate = false;
        for (Map.Entry<String, Integer> entry : wordCount.entrySet()) {
            if (entry.getValue() > 1) {
                System.out.println(entry.getKey() + ": " + entry.getValue());
                foundDuplicate = true;
            }
        }

        if (!foundDuplicate) {
            System.out.println("没有重复的单词。");
        }

        scanner.close();
    }
}