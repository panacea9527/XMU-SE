package com.notepad;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application
{
    public static void main(String[] args) {
        launch(args);
    }

    public void start(Stage stage) throws Exception
    {
        Parent root = FXMLLoader.load(this.getClass().getResource("Notepad.fxml"));
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.setTitle("记事本");
        stage.show();
    }
}
