import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.nio.file.attribute.FileTime;
import java.text.SimpleDateFormat;
import java.util.Scanner;

public class FileInfo {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("请输入文件路径: ");
        String pathInput = scanner.nextLine();
        Path path = Paths.get(pathInput);

        if (Files.exists(path)) {
            if (Files.isDirectory(path)) {
                processDirectory(path);
            } else if (Files.isRegularFile(path)) {
                processFile(path);
            } else {
                System.out.println("该路径既不是文件也不是文件夹。");
            }
        } else {
            System.out.println("路径不存在。");
        }
    }

    private static void processDirectory(Path path) {
        try {
            DirectoryStream<Path> directoryStream = Files.newDirectoryStream(path);
            int fileCount = 0;
            int directoryCount = 0;
            for (Path p : directoryStream) {
                if (Files.isDirectory(p)) {
                    directoryCount++;
                } else {
                    fileCount++;
                }
            }
            System.out.println("文件夹包含文件个数: " + fileCount);
            System.out.println("文件夹包含文件夹个数: " + directoryCount);
        } catch (IOException e) {
            System.err.println("无法读取目录: " + e.getMessage());
        }
    }

    private static void processFile(Path path) {
        try {
            BasicFileAttributes attrs = Files.readAttributes(path, BasicFileAttributes.class);
            long fileSize = attrs.size();
            FileTime lastModifiedTime = attrs.lastModifiedTime();
            SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

            System.out.println("文件大小: " + fileSize + " 字节");
            System.out.println("最后修改日期: " + dateFormat.format(lastModifiedTime.toMillis()));
        } catch (IOException e) {
            System.err.println("无法读取文件属性: " + e.getMessage());
        }
    }
}
