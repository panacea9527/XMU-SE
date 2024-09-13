package org.example;

import org.apache.poi.ss.usermodel.*;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class ExcelFileHandler {

    public static void main(String[] args) {
        String filePath = "singer.xlsx";
        if (!Files.exists(Paths.get(filePath))) {
            System.out.println("文件不存在: " + filePath);
            return;
        }

        try (FileInputStream fis = new FileInputStream(filePath);
             Workbook workbook = new XSSFWorkbook(fis)) {
            // 获取第一个工作表
            Sheet sheet = workbook.getSheetAt(0);
            // 遍历所有行和单元格
            for (Row row : sheet) {
                for (Cell cell : row) {
                    if (cell.getCellType() == CellType.STRING) {
                        String text = cell.getStringCellValue();
                        if (text.contains("孙燕资")) {
                            cell.setCellValue(text.replace("孙燕资", "孙燕姿"));
                        }
                    }
                }
            }
            // 在最后一行添加修改时间
            int lastRowNum = sheet.getLastRowNum();
            Row newRow = sheet.createRow(lastRowNum + 1);
            Cell newCell = newRow.createCell(0);
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
            String currentTime = LocalDateTime.now().format(formatter);
            newCell.setCellValue("最后修改时间：" + currentTime);
            // 保存修改后的文件
            try (FileOutputStream fos = new FileOutputStream(filePath)) {
                workbook.write(fos);
            }
            System.out.println("文件已成功修改并保存: " + filePath);
        } catch (IOException e) {
            System.out.println("发生IO异常: " + e.getMessage());
        }
    }
}
