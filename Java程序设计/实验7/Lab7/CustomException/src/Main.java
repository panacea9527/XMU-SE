import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<Student> students = new ArrayList<>();

        System.out.println("请输入学生数量：");
        int studentCount = scanner.nextInt();

        for (int i = 0; i < studentCount; i++) {
            while (true) {
                try {
                    System.out.println("请输入学生姓名：");
                    String name = scanner.next();
                    System.out.println("请输入学生地址：");
                    String address = scanner.next();

                    Student student = new Student();
                    student.setName(name);
                    student.setAddress(address);

                    students.add(student);
                    break;
                } catch (IllegaNameException | IllegalAddressException e) {
                    System.out.println(e.getMessage() + "，请重新输入。");
                }
            }
        }

        for (Student student : students) {
            System.out.println("姓名：" + student.getName() + "，地址：" + student.getAddress());
        }

        scanner.close();
    }
}
