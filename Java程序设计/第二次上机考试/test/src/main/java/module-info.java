module com.example.test {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.test to javafx.fxml;
    exports com.example.test;
}