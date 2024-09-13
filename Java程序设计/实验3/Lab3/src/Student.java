public class Student {
    private String studentId;
    private String name;
    private String className;
    private String phone;

    // 电话号码为空
    public Student(String studentId, String name, String className) {
        this.studentId = studentId;
        this.name = name;
        this.className = className;
        this.phone = "";
    }
    // 包含电话号码
    public Student(String studentId, String name, String className, String phone) {
        this.studentId = studentId;
        this.name = name;
        this.className = className;
        this.phone = phone;
    }
    public String getStudentId() {
        return studentId;
    }
    public String getName() {
        return name;
    }
    public String getClassName() {
        return className;
    }
    public String getPhone() {
        return phone;
    }
    public void setStudentId(String studentId) {
        this.studentId = studentId;
    }
    public void setName(String name) {
        this.name = name;
    }
    public void setClassName(String className) {
        this.className = className;
    }
    public void setPhone(String phone) {
        this.phone = phone;
    }
}

