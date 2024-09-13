package com.example.login;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.PasswordField;

public class RegisterController {
    @FXML
    private Label messageLabel;
    @FXML
    private TextField usernameField;
    @FXML
    private PasswordField passwordField;
    @FXML
    private PasswordField confirmPasswordField;

    @FXML
    protected void onRegisterButtonClick() {
        String username = usernameField.getText();
        String password = passwordField.getText();
        String confirmPassword = confirmPasswordField.getText();

        if (username.length() < 4) {
            messageLabel.setText("用户名长度不能小于4!");
        } else if (!password.equals(confirmPassword)) {
            messageLabel.setText("两次密码必须相同!");
        } else {
            messageLabel.setText("注册成功!");
        }
    }
}
