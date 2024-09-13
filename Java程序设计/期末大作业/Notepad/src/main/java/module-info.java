module com.notepad {
    requires javafx.controls;
    requires javafx.fxml;

    opens com.notepad to javafx.fxml;
    exports com.notepad;
}