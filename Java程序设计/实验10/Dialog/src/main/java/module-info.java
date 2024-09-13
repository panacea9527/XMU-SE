module com.example.dialog {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.dialog to javafx.fxml;
    exports com.example.dialog;
}