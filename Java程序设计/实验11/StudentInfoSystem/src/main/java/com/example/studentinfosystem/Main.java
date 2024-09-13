package com.example.studentinfosystem;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;

public class Main extends Application {
    @Override
    public void start(Stage primaryStage) {
        try {
            File photoDir = new File("photos");
            if (!photoDir.exists()) {
                photoDir.mkdirs();
            }

            FXMLLoader loader = new FXMLLoader(getClass().getResource("student_view.fxml"));
            VBox root = loader.load();
            Scene scene = new Scene(root, 500, 600);
            primaryStage.setTitle("学生信息管理");
            primaryStage.setScene(scene);
            primaryStage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}


