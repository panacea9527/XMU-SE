package com.notepad;

import javafx.fxml.FXML;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextArea;
import javafx.scene.paint.Color;
import javafx.scene.text.FontPosture;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import javafx.scene.control.ColorPicker;

import java.util.List;

public class FontsController {
    @FXML private TextArea fontDisplay;
    @FXML private TextArea shapeDisplay;
    @FXML private TextArea sizeDisplay;
    @FXML private TextArea display;
    @FXML private ComboBox<String> fontBox;
    @FXML private ComboBox<String> shapeBox;
    @FXML private ComboBox<String> sizeBox;
    @FXML private ColorPicker colorPicker;
    @FXML private Button confirm;
    @FXML private Button cancel;

    private String name = "微软雅黑";
    private String style = "常规";
    private int size = 12;
    private Color color = Color.BLACK;
    private Font font = Font.font(name, FontWeight.NORMAL, FontPosture.REGULAR, size);
    private Font ret;

    private final List<String> names = Font.getFontNames();
    private final String[] styles = {"常规", "斜体", "粗体", "粗斜体"};
    private final String[] sizes = {"8", "9", "10", "11", "12", "14", "16", "18", "20", "22", "24", "36", "48", "72"};

    public void initialize() {
        display.setText("This is test text!");
        updateFont();
        fontBox.getItems().addAll(names);
        shapeBox.getItems().addAll(styles);
        sizeBox.getItems().addAll(sizes);

        fontBox.setOnAction(event -> {
            name = fontBox.getValue();
            fontDisplay.setText(name);
            updateFont();
        });

        shapeBox.setOnAction(event -> {
            style = shapeBox.getValue();
            shapeDisplay.setText(style);
            updateFont();
        });

        sizeBox.setOnAction(event -> {
            size = Integer.parseInt(sizeBox.getValue());
            sizeDisplay.setText(sizeBox.getValue());
            updateFont();
        });

        colorPicker.setOnAction(event -> {
            color = colorPicker.getValue();
            updateFont();
        });

        confirm.setOnAction(event -> {
            ret = font;
            Scene scene = confirm.getScene();
            scene.setUserData(new Object[]{ret, color});
            Stage stage = (Stage) confirm.getScene().getWindow();
            stage.close();
        });

        cancel.setOnAction(event -> {
            Stage stage = (Stage) cancel.getScene().getWindow();
            stage.close();
        });
    }

    private void updateFont() {
        FontWeight weight = FontWeight.NORMAL;
        FontPosture posture = FontPosture.REGULAR;

        switch (style) {
            case "粗体":
                weight = FontWeight.BOLD;
                break;
            case "斜体":
                posture = FontPosture.ITALIC;
                break;
            case "粗斜体":
                weight = FontWeight.BOLD;
                posture = FontPosture.ITALIC;
                break;
            default:
                break;
        }

        font = Font.font(name, weight, posture, size);
        display.setFont(font);
        display.setStyle("-fx-text-fill: " + toRgbString(color) + ";");
    }

    private String toRgbString(Color color) {
        int red = (int) (color.getRed() * 255);
        int green = (int) (color.getGreen() * 255);
        int blue = (int) (color.getBlue() * 255);
        return String.format("rgb(%d, %d, %d)", red, green, blue);
    }
}
