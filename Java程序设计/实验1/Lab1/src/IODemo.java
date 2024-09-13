import javax.swing.JOptionPane;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

public class IODemo {
    public static void main(String[] args) throws IOException {
        IOUsingJOptionPane();
        IOUsingBufferedReader();
        IOUsingScanner();
    }

    public static void IOUsingJOptionPane() {
        // 使用 JOptionPane
        String jOptionPaneInput = JOptionPane.showInputDialog("请输入你的专业:");
        JOptionPane.showMessageDialog(null, "你的专业为: " + jOptionPaneInput);
    }

    public static void IOUsingScanner() {
        // 使用 Scanner
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入一些内容（使用Scanner）：");
        String scannerInput = scanner.nextLine();
        System.out.printf("你输入的内容是：%s\n", scannerInput);
        scanner.close();
        System.out.println("以下展示System.out的不同打印方法：");
        System.out.println("这是使用System.out.print打印的，格式化输出：");
        String[] products = {"iPhone 15", "Xiaomi 14"};
        double[] prices = {9999.99, 2999.99};
        int[] quantities = {1, 2};
        System.out.printf("%-20s %10s %10s\n", "商品名称", "价格", "数量");
        for (int i = 0; i < products.length; i++) {
            System.out.printf("%-20s %10.2f元 %10d件\n", products[i], prices[i], quantities[i]);
        }
        System.out.print("这是使用System.out.print打印的，没有自动换行。");
        System.out.println("\n这是使用System.out.println打印的，自动换行。");
    }

    public static void IOUsingBufferedReader() throws IOException {
        // 使用 BufferedReader
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("请输入一些内容（BufferedReader）: ");
        String bufferedReaderInput = reader.readLine();
        System.out.println("你输入的内容是: " + bufferedReaderInput);
    }
}
