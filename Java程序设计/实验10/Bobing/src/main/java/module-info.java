module com.example.bobing {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.bobing to javafx.fxml;
    exports com.example.bobing;
}