package com.example.test;

import javafx.collections.FXCollections;
        import javafx.collections.ObservableList;
        import javafx.event.ActionEvent;
        import javafx.fxml.FXML;
        import javafx.scene.control.Alert;
        import javafx.scene.control.ListView;
        import javafx.scene.control.TextField;

        import java.io.*;
        import java.util.List;

public class EmployeeController {
    @FXML
    private ListView<String> employeeListView;
    @FXML
    private TextField idField;
    @FXML
    private TextField nameField;
    @FXML
    private TextField departmentField;
    @FXML
    private TextField positionField;

    private ObservableList<String> employeeList = FXCollections.observableArrayList();
    private List<Employee> employees = FXCollections.observableArrayList();
    private Employee selectedEmployee = null;

    @FXML
    public void initialize() {
        employeeListView.setItems(employeeList);
        employeeListView.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                displayEmployeeDetails(newValue);
            }
        });
    }

    @FXML
    public void handleAddEmployee(ActionEvent event) {
        /*处理新增员工的方法，处理逻辑如下
        * 首先生成一个id
        * 接着创建一个新员工对象
        * 将新创建的对象加入列表中
        * 调用显示方法在界面上更新*/
        String newId = generateNewId();
        Employee newEmployee = new Employee(newId, "", "", "");
        employees.add(newEmployee);
        updateEmployeeList();
        employeeListView.getSelectionModel().select(newEmployee.getId() + ": " + newEmployee.getName());
        displayEmployeeDetails(newEmployee.getId() + ": " + newEmployee.getName());
    }

    private String generateNewId() {
        /*
        * 供handleAddEmployee方法使用，生成一个新id
        * 生成的逻辑是遍历链表中所有id，找到最大的并+1
        */
        int maxId = employees.stream()
                .mapToInt(emp -> Integer.parseInt(emp.getId()))
                .max()
                .orElse(0);
        return String.valueOf(maxId + 1);
    }

    @FXML
    public void handleSaveEmployee(ActionEvent event) {
        /*
        * 处理保存按钮的逻辑
        * 用户输入员工ID、姓名、部门、岗位级别信息后，点击“保存”按钮，则保存该员工信息。
        * 如果用户修改信息，点击“保存”按钮，则保存修改后的该员工信息。
        * 执行保存操作后，界面左侧相关内容更新
        * */
        if (selectedEmployee != null) {
            String newId = idField.getText();
            if (!newId.equals(selectedEmployee.getId())) {
                if (employees.stream().anyMatch(emp -> emp.getId().equals(newId))) {
                    showAlert("保存失败", "ID 已存在，请使用不同的 ID", Alert.AlertType.ERROR);
                    return;
                }
                selectedEmployee.setId(newId);
            }
            selectedEmployee.setName(nameField.getText());
            selectedEmployee.setDepartment(departmentField.getText());
            selectedEmployee.setPosition(positionField.getText());

            updateEmployeeList();
            employeeListView.getSelectionModel().select(selectedEmployee.getId() + ": " + selectedEmployee.getName());
        }
    }

    @FXML
    public void handleDeleteEmployee(ActionEvent event) {
        /*
        * 删除用户选中的员工信息
        * */
        String selectedEmployee = employeeListView.getSelectionModel().getSelectedItem();
        if (selectedEmployee != null) {
            employees.removeIf(emp -> emp.getId().equals(selectedEmployee.split(":")[0]));
            updateEmployeeList();
        }
    }

    @FXML
    public void handleSaveToFile(ActionEvent event) {
        /*
        * 将所有员工信息保存到文件中，文件保存到对应resource文件夹下，文件名为“employeesData.txt”。
        * 然后根据结果提供对应的提醒。
        * */
        try {
            File file = new File("./src/main/resources/com/example/test/employeesData.txt");
            try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
                for (Employee employee : employees) {
                    writer.write(employee.toString());
                    writer.newLine();
                }
            }
            showAlert("保存成功", "员工信息已保存至文件 employeesData.txt", Alert.AlertType.INFORMATION);
        } catch (IOException e) {
            e.printStackTrace();
            showAlert("保存失败", "员工信息保存至文件失败", Alert.AlertType.ERROR);
        }
    }

    private void updateEmployeeList() {
        /*
        * 更新员工列表，并在界面上显示。
        * */
        employeeList.clear();
        for (Employee employee : employees) {
            employeeList.add(employee.getId() + ": " + employee.getName());
        }
    }

    private void displayEmployeeDetails(String employeeDetails) {
        /*
        * 点击员工列表选中员工后，在右侧信息界面显示员工完整的信息。
        * */
        String[] details = employeeDetails.split(":");
        selectedEmployee = employees.stream().filter(emp -> emp.getId().equals(details[0])).findFirst().orElse(null);

        if (selectedEmployee != null) {
            idField.setText(selectedEmployee.getId());
            nameField.setText(selectedEmployee.getName());
            departmentField.setText(selectedEmployee.getDepartment());
            positionField.setText(selectedEmployee.getPosition());
        }
    }

    private void showAlert(String title, String content, Alert.AlertType alertType) {
        Alert alert = new Alert(alertType);
        alert.setTitle(title);
        alert.setContentText(content);
        alert.showAndWait();
    }
}