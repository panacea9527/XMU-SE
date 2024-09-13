package com.notepad;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.input.KeyCode;
import javafx.scene.text.Font;
import javafx.scene.paint.Color;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Optional;

public class NotepadController {
    @FXML private TextArea textArea;
    @FXML private MenuItem create, open, save, saveAs, exit;
    @FXML private MenuItem undo, cut, copy, paste, delete;
    @FXML private MenuItem search, search_last, search_next, replace, select_all, font, about;
    @FXML private RadioMenuItem status, autoEnd;
    @FXML private Label label, info;

    private String path = null;
    private boolean isSave = true;
    private String filename = null;
    private String searchStr = null;
    private String replaceStr = null;
    private int row = 1, column = 1;

    public void initialize() {
        initMenuItems();
        textArea.textProperty().addListener((observable, oldValue, newValue) -> handleTextChange());
        textArea.selectedTextProperty().addListener((observable, oldValue, newValue) -> handleSelectionChange(newValue));
        textArea.caretPositionProperty().addListener((observable, oldValue, newValue) -> updateInfo());
        textArea.setOnKeyPressed(event -> handleKeyPress(event.getCode()));
        setupMenuActions();
    }

    private void initMenuItems() {
        cut.setDisable(true);
        copy.setDisable(true);
        delete.setDisable(true);
        undo.setDisable(true);
        search_last.setDisable(true);
        search_next.setDisable(true);
        search.setDisable(true);

        status.setSelected(true);
        info.setVisible(true);
        info.setText(getStatusText());
        autoEnd.setSelected(false);
    }

    private String getStatusText() {
        return "第" + row + "行，第" + column + "列    Windows(记事本 By 任宇)    UTF-8";
    }

    private void handleTextChange() {
        isSave = false;
        undo.setDisable(false);
        boolean hasText = !textArea.getText().isEmpty();
        search.setDisable(!hasText);
        search_last.setDisable(!hasText);
        search_next.setDisable(!hasText);
        updateLabel();
    }

    private void handleSelectionChange(String newValue) {
        boolean hasSelection = !newValue.isEmpty();
        cut.setDisable(!hasSelection);
        copy.setDisable(!hasSelection);
        delete.setDisable(!hasSelection);
    }

    private void handleKeyPress(KeyCode code) {
        if (code == KeyCode.ENTER || code == KeyCode.DELETE) {
            updateInfo();
        }
    }

    private void setupMenuActions() {
        create.setOnAction(event -> handleCreate());
        open.setOnAction(event -> handleOpen());
        save.setOnAction(event -> handleSave());
        saveAs.setOnAction(event -> saveAs());
        exit.setOnAction(event -> handleExit());
        undo.setOnAction(event -> handleUndo());
        cut.setOnAction(event -> textArea.cut());
        copy.setOnAction(event -> textArea.copy());
        paste.setOnAction(event -> textArea.paste());
        delete.setOnAction(event -> textArea.deleteText(textArea.getSelection()));
        search.setOnAction(event -> handleSearch());
        search_next.setOnAction(event -> handleSearchNext());
        search_last.setOnAction(event -> handleSearchLast());
        replace.setOnAction(event -> handleReplace());
        select_all.setOnAction(event -> textArea.selectAll());
        about.setOnAction(event -> showAbout());
        font.setOnAction(event -> handleFont());
        status.setOnAction(event -> updateInfo());
        autoEnd.setOnAction(event -> textArea.setWrapText(autoEnd.isSelected()));
    }

    private void handleCreate() {
        if (!isSave) {
            int response = promptSave();
            if (response == 0) save();
            else if (response == 2) return;
        }
        File file = promptFileSave("新建文件", "未命名.txt");
        if (file != null) {
            path = file.getAbsolutePath();
            filename = file.getName();
            textArea.clear();
            isSave = false;
            updateLabel();
        }
    }

    private void handleOpen() {
        if (!isSave) {
            int response = promptSave();
            if (response == 0) save();
            else if (response == 2) return;
        }
        selectFileShow();
    }

    private void handleSave() {
        if (path == null) saveAs();
        else save();
    }

    private void handleExit() {
        if (!isSave) {
            int response = promptSave();
            if (response == 0) save();
            else if (response == 2) return;
        }
        System.exit(0);
    }

    private void handleUndo() {
        textArea.undo();
        undo.setDisable(true);
    }

    private void handleSearch() {
        searchStr = promptInput("查找", "请输入要查找的内容：");
        if (searchStr != null) {
            selectSearchResult(searchStr);
        }
    }

    private void handleSearchNext() {
        if (searchStr == null) {
            searchStr = promptInput("查找", "请输入要查找的内容：");
        }
        if (searchStr != null) {
            selectSearchResult(searchStr, textArea.getSelection().getEnd());
        }
    }

    private void handleSearchLast() {
        if (searchStr == null) {
            searchStr = promptInput("查找", "请输入要查找的内容：");
        }
        if (searchStr != null) {
            selectLastSearchResult(searchStr, textArea.getSelection().getStart() - 1);
        }
    }

    private void handleReplace() {
        searchStr = promptInput("查找", "请输入要查找的内容：");
        replaceStr = promptInput("替换", "请输入要替换成的内容：");
        if (searchStr != null && replaceStr != null) {
            promptReplaceOptions();
        }
    }

    private void showAbout() {
        Alert alert = new Alert(AlertType.INFORMATION);
        alert.setTitle("关于记事本");
        alert.setHeaderText("关于记事本");
        alert.setContentText("记事本应用程序\n版本 1.0\n由 任宇 开发");
        alert.showAndWait();
    }

    private void handleFont() {
        try {
            Stage stage = new Stage();
            Parent root = FXMLLoader.load(getClass().getResource("Fonts.fxml"));
            Scene scene = new Scene(root);
            stage.setTitle("选择字体");
            stage.setScene(scene);
            stage.showAndWait();
            Object[] result = (Object[]) scene.getUserData();
            if (result != null) {
                Font selectedFont = (Font) result[0];
                Color selectedColor = (Color) result[1];
                textArea.setFont(selectedFont);
                textArea.setStyle("-fx-text-fill: " + toRgbString(selectedColor) + ";");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void saveAs() {
        File file = promptFileSave("保存文件", "未命名.txt");
        if (file != null) {
            path = file.getAbsolutePath();
            filename = file.getName();
            writeFile(file);
        }
    }

    private void save() {
        File file = new File(path);
        if (file.exists()) {
            file.delete();
        }
        writeFile(file);
    }

    private File promptFileSave(String title, String initialFileName) {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle(title);
        fileChooser.setInitialFileName(initialFileName);
        return fileChooser.showSaveDialog(new Stage());
    }

    private void writeFile(File file) {
        try (FileWriter fileWriter = new FileWriter(file)) {
            fileWriter.write(textArea.getText());
            isSave = true;
            updateLabel();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void selectFileShow() {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("选择文件");
        File file = fileChooser.showOpenDialog(new Stage());
        if (file != null) {
            path = file.getAbsolutePath();
            filename = file.getName();
            isSave = true;
            updateLabel();
            readFile(file);
        }
    }

    private void readFile(File file) {
        try (FileReader fileReader = new FileReader(file)) {
            textArea.clear();
            char[] buffer = new char[1024];
            int len;
            while ((len = fileReader.read(buffer)) != -1) {
                textArea.appendText(new String(buffer, 0, len));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private int promptSave() {
        Alert alert = new Alert(AlertType.CONFIRMATION);
        alert.setTitle("记事本");
        alert.setHeaderText(null);
        alert.setContentText("是否保存更改？");

        ButtonType buttonTypeSave = new ButtonType("保存");
        ButtonType buttonTypeNotSave = new ButtonType("不保存");
        ButtonType buttonTypeCancel = new ButtonType("取消", ButtonBar.ButtonData.CANCEL_CLOSE);

        alert.getButtonTypes().setAll(buttonTypeSave, buttonTypeNotSave, buttonTypeCancel);
        Optional<ButtonType> result = alert.showAndWait();

        if (result.isPresent()) {
            if (result.get() == buttonTypeSave) {
                return 0;
            } else if (result.get() == buttonTypeNotSave) {
                return 1;
            } else {
                return 2;
            }
        }
        return 2;
    }

    private String promptInput(String title, String content) {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle(title);
        dialog.setHeaderText(title);
        dialog.setContentText(content);
        Optional<String> result = dialog.showAndWait();
        return result.orElse(null);
    }

    private void selectSearchResult(String searchString) {
        int startIndex = textArea.getText().indexOf(searchString);
        if (startIndex != -1) {
            textArea.selectRange(startIndex, startIndex + searchString.length());
        } else {
            showAlert("找不到 " + "\"" + searchString + "\"");
        }
    }

    private void selectSearchResult(String searchString, int fromIndex) {
        int startIndex = textArea.getText().indexOf(searchString, fromIndex);
        if (startIndex != -1) {
            textArea.selectRange(startIndex, startIndex + searchString.length());
        } else {
            showAlert("找不到 " + "\"" + searchString + "\"");
        }
    }

    private void selectLastSearchResult(String searchString, int fromIndex) {
        int startIndex = textArea.getText().lastIndexOf(searchString, fromIndex);
        if (startIndex != -1) {
            textArea.selectRange(startIndex, startIndex + searchString.length());
        } else {
            showAlert("找不到 " + "\"" + searchString + "\"");
        }
    }

    private void promptReplaceOptions() {
        Alert alert = new Alert(AlertType.CONFIRMATION);
        alert.setTitle("替换");
        alert.setHeaderText(null);
        alert.setContentText("选择替换选项：");

        ButtonType buttonTypeAll = new ButtonType("全部替换");
        ButtonType buttonTypePartial = new ButtonType("部分替换");
        ButtonType buttonTypeCancel = new ButtonType("取消", ButtonBar.ButtonData.CANCEL_CLOSE);

        alert.getButtonTypes().setAll(buttonTypeAll, buttonTypePartial, buttonTypeCancel);
        Optional<ButtonType> result = alert.showAndWait();

        if (result.isPresent()) {
            if (result.get() == buttonTypeAll) {
                textArea.setText(textArea.getText().replaceAll(searchStr, replaceStr));
            } else if (result.get() == buttonTypePartial) {
                replacePartial();
            }
        }
    }

    private void replacePartial() {
        while (true) {
            Alert partialAlert = new Alert(AlertType.CONFIRMATION);
            partialAlert.setTitle("替换");
            partialAlert.setHeaderText(null);
            partialAlert.setContentText("选择替换选项：");

            ButtonType buttonTypeReplace = new ButtonType("替换");
            ButtonType buttonTypeNext = new ButtonType("下一个");
            ButtonType buttonTypeCancel = new ButtonType("取消", ButtonBar.ButtonData.CANCEL_CLOSE);

            partialAlert.getButtonTypes().setAll(buttonTypeReplace, buttonTypeNext, buttonTypeCancel);
            Optional<ButtonType> partialResult = partialAlert.showAndWait();

            if (partialResult.isPresent()) {
                if (partialResult.get() == buttonTypeReplace) {
                    textArea.replaceSelection(replaceStr);
                } else if (partialResult.get() == buttonTypeNext) {
                    selectSearchResult(searchStr, textArea.getSelection().getEnd());
                } else {
                    break;
                }
            }
        }
    }

    private void showAlert(String message) {
        Alert alert = new Alert(AlertType.INFORMATION);
        alert.setTitle("记事本");
        alert.setHeaderText("记事本");
        alert.setContentText(message);
        alert.showAndWait();
    }

    private void updateInfo() {
        if (status.isSelected()) {
            row = getRow();
            column = getColumn();
            info.setText(getStatusText());
            info.setVisible(true);
        } else {
            info.setVisible(false);
        }
    }

    private int getRow() {
        int caretPosition = textArea.getCaretPosition();
        String text = textArea.getText();
        return (int) text.substring(0, caretPosition).chars().filter(ch -> ch == '\n').count() + 1;
    }

    private int getColumn() {
        int caretPosition = textArea.getCaretPosition();
        String text = textArea.getText();
        int rowStart = text.lastIndexOf('\n', caretPosition - 1);
        return caretPosition - rowStart;
    }

    private void updateLabel() {
        label.setText((filename == null ? "无标题" : filename) + (isSave ? "_已保存" : "_未保存"));
    }

    private String toRgbString(Color color) {
        int red = (int) (color.getRed() * 255);
        int green = (int) (color.getGreen() * 255);
        int blue = (int) (color.getBlue() * 255);
        return String.format("rgb(%d, %d, %d)", red, green, blue);
    }
}
