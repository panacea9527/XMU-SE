import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.text.SimpleDateFormat;
import java.util.Scanner;

public class RandomAccessFileInfo {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入文件路径: ");
        String pathInput = scanner.nextLine();
        File file = new File(pathInput);

        if (file.exists()) {
            if (file.isDirectory()) {
                int fileCount = 0;
                int directoryCount = 0;
                File[] files = file.listFiles();
                if (files != null) {
                    for (File f : files) {
                        if (f.isDirectory()) {
                            directoryCount++;
                        } else {
                            fileCount++;
                        }
                    }
                }
                System.out.println("文件夹包含文件个数: " + fileCount);
                System.out.println("文件夹包含文件夹个数: " + directoryCount);
            } else if (file.isFile()) {
                try (RandomAccessFile raf = new RandomAccessFile(file, "r")) {
                    long fileSize = raf.length();
                    long lastModified = file.lastModified();
                    SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

                    System.out.println("文件大小: " + fileSize + " 字节");
                    System.out.println("最后修改日期: " + dateFormat.format(lastModified));
                } catch (IOException e) {
                    System.err.println("无法读取文件: " + e.getMessage());
                }
            } else {
                System.out.println("该路径既不是文件也不是文件夹。");
            }
        } else {
            System.out.println("路径不存在。");
        }
    }
}
