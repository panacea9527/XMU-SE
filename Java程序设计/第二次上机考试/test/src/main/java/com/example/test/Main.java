package com.example.test;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("ui.fxml"));
        primaryStage.setTitle("员工信息管理");
        primaryStage.setScene(new Scene(root, 450, 260));
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
