package com.example.dialog;

import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;

public class DialogController {
    @FXML
    private Button showDialogButton;

    @FXML
    private void onShowDialogButtonClick() {
        showAlert(Alert.AlertType.INFORMATION, "Information Dialog", "信息对话框！");
        showAlert(Alert.AlertType.WARNING, "Warning Dialog", "警告对话框！");
        showAlert(Alert.AlertType.ERROR, "Error Dialog", "错误对话框！");
        showAlert(Alert.AlertType.CONFIRMATION, "Confirmation Dialog", "确认对话框！");
    }

    private void showAlert(Alert.AlertType alertType, String title, String content) {
        Alert alert = new Alert(alertType);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);
        alert.showAndWait();
    }
}
