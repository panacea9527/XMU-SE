import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        try {
            System.out.println("请输入一个正整数以初始化第一个SomeClass对象:");
            int firstInput = scanner.nextInt();
            SomeClass sc = new SomeClass(firstInput);

            System.out.println("请输入一个正整数以初始化第二个SomeClass对象:");
            int secondInput = scanner.nextInt();
            SomeClass sc1 = new SomeClass(secondInput);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        } finally {
            scanner.close();
        }
    }
}
