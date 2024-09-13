import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Set<String> names = new HashSet<>();

        System.out.println("请输入名字，输入 'END' 结束：");

        while (true) {
            String input = scanner.nextLine();
            if ("END".equalsIgnoreCase(input)) {
                break;
            }
            names.add(input);
        }

        System.out.println("去重后的的名字列表：");
        for (String name : names) {
            System.out.println(name);
        }

        scanner.close();
    }
}