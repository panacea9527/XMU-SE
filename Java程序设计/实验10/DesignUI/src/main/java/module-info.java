module com.example.designui {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.designui to javafx.fxml;
    exports com.example.designui;
}