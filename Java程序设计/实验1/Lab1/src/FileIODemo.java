import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class FileIODemo {
    public static void main(String[] args) {
        String fileName = "FileIOTest.txt";
        try {
            FileWriter fileWriter = new FileWriter(fileName, true);
            PrintWriter printWriter = new PrintWriter(fileWriter);
            printWriter.println("Java Lab1");
            printWriter.println("文件读写操作");
            printWriter.close();
            System.out.println("数据已成功写入文件。");

            // 读取文件
            FileReader fileReader = new FileReader(fileName);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            String line;
            System.out.println("文件内容如下：");
            while ((line = bufferedReader.readLine()) != null) {
                System.out.println(line);
            }
            bufferedReader.close();
        } catch (IOException e) {
            System.out.println("处理文件时发生错误。");
            e.printStackTrace();
        }
    }
}
