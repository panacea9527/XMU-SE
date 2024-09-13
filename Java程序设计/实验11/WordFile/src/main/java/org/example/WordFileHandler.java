package org.example;

import org.apache.poi.xwpf.usermodel.XWPFDocument;
import org.apache.poi.xwpf.usermodel.XWPFParagraph;
import org.apache.poi.xwpf.usermodel.XWPFRun;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class WordFileHandler {

    public static void main(String[] args) {
        String filePath = "test.docx";
        if (!Files.exists(Paths.get(filePath))) {
            System.out.println("文件不存在: " + filePath);
            return;
        }

        // 处理文件输入流和XWPFDocument
        try (FileInputStream fis = new FileInputStream(filePath);
             XWPFDocument document = new XWPFDocument(fis)) {
            for (XWPFParagraph paragraph : document.getParagraphs()) {
                for (XWPFRun run : paragraph.getRuns()) {
                    String text = run.getText(0);
                    if (text != null) {
                        text = text.replace("我怀念的", "what I miss");
                        run.setText(text, 0);
                    }
                }
            }
            XWPFParagraph newParagraph = document.createParagraph();
            XWPFRun newRun = newParagraph.createRun();
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
            String currentTime = LocalDateTime.now().format(formatter);
            newRun.setText("最后修改时间：" + currentTime);
            try (FileOutputStream fos = new FileOutputStream(filePath)) {
                document.write(fos);
            }
            System.out.println("文件已成功修改并保存: " + filePath);

        } catch (IOException e) {
            System.out.println("发生IO异常: " + e.getMessage());
        }
    }
}
