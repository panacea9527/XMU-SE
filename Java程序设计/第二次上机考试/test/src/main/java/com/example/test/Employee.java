package com.example.test;

// 员工类
class Employee {
    private String id; //id
    private String name; //姓名
    private String department; //部门
    private String position; //岗位级别

    public Employee(String id, String name, String department, String position) {
        this.id = id;
        this.name = name;
        this.department = department;
        this.position = position;
    }

    // Setter and Getter
    public void setName(String name) {
        this.name = name;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setPosition(String position) {
        this.position = position;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getDepartment() {
        return department;
    }

    public String getPosition() {
        return position;
    }

    @Override
    public String toString() {
        return id + "," + name + "," + department + "," + position;
    }
}


