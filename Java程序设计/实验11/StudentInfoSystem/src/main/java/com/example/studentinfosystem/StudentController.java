package com.example.studentinfosystem;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.stage.FileChooser;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import java.util.List;
import java.util.Optional;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class StudentController {
    @FXML
    private TableView<Student> studentTable;
    @FXML
    private TableColumn<Student, String> idColumn;
    @FXML
    private TableColumn<Student, String> nameColumn;
    @FXML
    private TableColumn<Student, String> phoneColumn;
    @FXML
    private TableColumn<Student, String> emailColumn;

    @FXML
    private TextField idField;
    @FXML
    private TextField nameField;
    @FXML
    private TextField phoneField;
    @FXML
    private TextField emailField;
    @FXML
    private ImageView photoView;
    @FXML
    private Button saveButton;

    private ObservableList<Student> studentData = FXCollections.observableArrayList();
    private ObservableList<Student> currentList = FXCollections.observableArrayList();
    private File photoFile;
    private int currentIndex = -1;

    public void initialize() {
        idColumn.setCellValueFactory(cellData -> cellData.getValue().idProperty());
        nameColumn.setCellValueFactory(cellData -> cellData.getValue().nameProperty());
        phoneColumn.setCellValueFactory(cellData -> cellData.getValue().phoneProperty());
        emailColumn.setCellValueFactory(cellData -> cellData.getValue().emailProperty());

        loadStudents();
        studentTable.setItems(studentData);
        currentList.addAll(studentData);

        studentTable.getSelectionModel().selectedItemProperty().addListener(
                (observable, oldValue, newValue) -> showStudentDetails(newValue));

        setFieldsEditable(false);
        saveButton.setDisable(true);
    }

    @FXML
    private void handleChoosePhoto() {
        FileChooser fileChooser = new FileChooser();
        fileChooser.getExtensionFilters().add(new FileChooser.ExtensionFilter("JPG files (*.jpg)", "*.jpg"));
        photoFile = fileChooser.showOpenDialog(null);
        if (photoFile != null) {
            photoView.setImage(new Image(photoFile.toURI().toString()));
        }
    }

    @FXML
    private void handleAdd() {
        Dialog<Student> dialog = new Dialog<>();
        dialog.setTitle("新增学生");
        dialog.setHeaderText("请输入学生信息");

        ButtonType addButtonType = new ButtonType("新增", ButtonBar.ButtonData.OK_DONE);
        dialog.getDialogPane().getButtonTypes().addAll(addButtonType, ButtonType.CANCEL);

        GridPane grid = new GridPane();
        grid.setHgap(10);
        grid.setVgap(10);
        grid.setPadding(new javafx.geometry.Insets(20, 150, 10, 10));

        TextField idField = new TextField();
        idField.setPromptText("学号");
        TextField nameField = new TextField();
        nameField.setPromptText("姓名");
        TextField phoneField = new TextField();
        phoneField.setPromptText("电话");
        TextField emailField = new TextField();
        emailField.setPromptText("邮箱");

        Button choosePhotoButton = new Button("选择照片");
        ImageView photoPreview = new ImageView();
        photoPreview.setFitWidth(100);
        photoPreview.setFitHeight(100);

        choosePhotoButton.setOnAction(e -> {
            FileChooser fileChooser = new FileChooser();
            fileChooser.getExtensionFilters().add(new FileChooser.ExtensionFilter("JPG files (*.jpg)", "*.jpg"));
            photoFile = fileChooser.showOpenDialog(null);
            if (photoFile != null) {
                photoPreview.setImage(new Image(photoFile.toURI().toString()));
            }
        });

        grid.add(new Label("学号:"), 0, 0);
        grid.add(idField, 1, 0);
        grid.add(new Label("姓名:"), 0, 1);
        grid.add(nameField, 1, 1);
        grid.add(new Label("电话:"), 0, 2);
        grid.add(phoneField, 1, 2);
        grid.add(new Label("邮箱:"), 0, 3);
        grid.add(emailField, 1, 3);
        grid.add(new Label("照片:"), 0, 4);
        grid.add(choosePhotoButton, 1, 4);
        grid.add(photoPreview, 2, 4);

        dialog.getDialogPane().setContent(grid);

        dialog.setResultConverter(dialogButton -> {
            if (dialogButton == addButtonType) {
                if (!isInputValid(idField.getText(), nameField.getText(), phoneField.getText(), emailField.getText())) {
                    showAlert("输入无效", "请检查输入的内容是否有效！");
                    return null;
                }
                String photoPath = copyPhoto(photoFile);
                return new Student(idField.getText(), nameField.getText(), phoneField.getText(), emailField.getText(), photoPath);
            }
            return null;
        });

        Optional<Student> result = dialog.showAndWait();
        result.ifPresent(student -> {
            studentData.add(student);
            saveStudents();
        });
    }

    @FXML
    private void handleDelete() {
        int selectedIndex = studentTable.getSelectionModel().getSelectedIndex();
        if (selectedIndex >= 0) {
            studentTable.getItems().remove(selectedIndex);
            saveStudents();
        } else {
            showAlert("未选择", "未选择学生");
        }
    }

    @FXML
    private void handleUpdate() {
        Student selectedStudent = studentTable.getSelectionModel().getSelectedItem();
        if (selectedStudent != null) {
            setFieldsEditable(true);
            saveButton.setDisable(false);
        } else {
            showAlert("未选择", "未选择学生");
        }
    }

    @FXML
    private void handleSave() {
        Student selectedStudent = studentTable.getSelectionModel().getSelectedItem();
        if (selectedStudent != null) {
            String id = idField.getText();
            String name = nameField.getText();
            String phone = phoneField.getText();
            String email = emailField.getText();

            if (!isInputValid(id, name, phone, email)) {
                showAlert("输入无效", "请检查输入的内容是否有效！");
                return;
            }

            selectedStudent.setId(id);
            selectedStudent.setName(name);
            selectedStudent.setPhone(phone);
            selectedStudent.setEmail(email);
            selectedStudent.setPhotoPath(copyPhoto(photoFile));
            saveStudents();
            studentTable.refresh();
            setFieldsEditable(false);
            saveButton.setDisable(true);
        }
    }

    @FXML
    private void handleSearch() {
        TextInputDialog dialog = new TextInputDialog();
        dialog.setTitle("查询学生");
        dialog.setHeaderText("请输入要查询的学生姓名");
        dialog.setContentText("姓名:");

        Optional<String> result = dialog.showAndWait();
        if (result.isPresent()) {
            String name = result.get();
            List<Student> filteredStudents = studentData.stream()
                    .filter(student -> student.getName().equalsIgnoreCase(name))
                    .collect(Collectors.toList());
            if (!filteredStudents.isEmpty()) {
                currentList.setAll(filteredStudents);
                currentIndex = 0;
                showStudentDetails(currentList.get(currentIndex));
                studentTable.setItems(FXCollections.observableArrayList(filteredStudents));
            } else {
                showAlert("未找到", "未找到姓名为" + name + "的学生");
            }
        }
    }

    @FXML
    private void handleShowAll() {
        currentList.setAll(studentData);
        currentIndex = -1;
        studentTable.setItems(studentData);
    }

    @FXML
    private void handlePrevious() {
        if (currentList.isEmpty()) return;
        if (currentIndex > 0) {
            currentIndex--;
            showStudentDetails(currentList.get(currentIndex));
            studentTable.getSelectionModel().select(currentIndex);
        }
    }

    @FXML
    private void handleNext() {
        if (currentList.isEmpty()) return;
        if (currentIndex < currentList.size() - 1) {
            currentIndex++;
            showStudentDetails(currentList.get(currentIndex));
            studentTable.getSelectionModel().select(currentIndex);
        }
    }

    private void showStudentDetails(Student student) {
        if (student != null) {
            idField.setText(student.getId());
            nameField.setText(student.getName());
            phoneField.setText(student.getPhone());
            emailField.setText(student.getEmail());
            photoView.setImage(new Image(new File(student.getPhotoPath()).toURI().toString()));
        } else {
            clearFields();
        }
    }

    private void clearFields() {
        idField.clear();
        nameField.clear();
        phoneField.clear();
        emailField.clear();
        photoView.setImage(null);
    }

    private void setFieldsEditable(boolean editable) {
        idField.setEditable(editable);
        nameField.setEditable(editable);
        phoneField.setEditable(editable);
        emailField.setEditable(editable);
    }

    private void loadStudents() {
        try (BufferedReader br = new BufferedReader(new FileReader("students.txt"))) {
            String line;
            while ((line = br.readLine()) != null) {
                try {
                    studentData.add(Student.fromString(line));
                } catch (IllegalArgumentException e) {
                    System.err.println("Skipping invalid student data: " + line);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void saveStudents() {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter("students.txt"))) {
            for (Student student : studentData) {
                bw.write(student.toString());
                bw.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private String copyPhoto(File photoFile) {
        if (photoFile != null) {
            String photoDirectory = "photos";
            File directory = new File(photoDirectory);
            if (!directory.exists()) {
                directory.mkdirs();
            }

            String fileName = photoFile.getName();
            String fileExtension = "";
            int dotIndex = fileName.lastIndexOf('.');
            if (dotIndex > 0) {
                fileExtension = fileName.substring(dotIndex);
                fileName = fileName.substring(0, dotIndex);
            }

            File destFile = new File(directory, fileName + fileExtension);
            int counter = 1;
            while (destFile.exists()) {
                destFile = new File(directory, fileName + "_" + counter + fileExtension);
                counter++;
            }
            try {
                Files.copy(photoFile.toPath(), destFile.toPath(), StandardCopyOption.REPLACE_EXISTING);
                return destFile.getPath();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return null;
    }


    private boolean isInputValid(String id, String name, String phone, String email) {
        String emailRegex = "^[A-Za-z0-9+_.-]+@(.+)$";
        String phoneRegex = "^[0-9]{11}$";
        return !(id.isEmpty() || name.isEmpty() || phone.isEmpty() || email.isEmpty() ||
                !Pattern.matches(emailRegex, email) || !Pattern.matches(phoneRegex, phone));
    }

    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }
}