import java.util.Random;
import java.util.Scanner;

public class Test {
    private static final Scanner scanner = new Scanner(System.in);
    private static final Random random = new Random();

    public static void main(String[] args) {
        Student[] students = new Student[2];
        for (int i = 0; i < students.length; i++) {
            System.out.printf("Enter information for student %d (ID, Name, Class, [Phone]):\n", i + 1);
            System.out.print("Student ID: ");
            String studentId = scanner.nextLine().trim();
            System.out.print("Name: ");
            String name = scanner.nextLine().trim();
            System.out.print("Class: ");
            String className = scanner.nextLine().trim();
            System.out.print("Phone (press ENTER if none): ");
            String phone = scanner.nextLine().trim();
            if (phone.isEmpty()) {
                students[i] = new Student(studentId, name, className);
            } else {
                students[i] = new Student(studentId, name, className, phone);
            }
        }
        Course[] courses = new Course[2];
        for (int i = 0; i < courses.length; i++) {
            System.out.printf("Enter information for course %d (CourseID CourseName):\n", i + 1);
            System.out.print("courseId: ");
            String courseId = scanner.nextLine().trim();
            System.out.print("courseName: ");
            String courseName = scanner.nextLine().trim();
            courses[i] = new Course(courseId, courseName);
        }

        // 为每个学生随机选择一门课程并分配成绩
        for (Student student : students) {
            selectCourse(student, courses);
        }
        scanner.close();
    }

    private static void selectCourse(Student student, Course[] courses) {
        int courseIndex = random.nextInt(courses.length);
        Course selectedCourse = courses[courseIndex];
        int grade = random.nextInt(101);
        System.out.printf("%s selected %s with score: %d\n", student.getName(), selectedCourse.getCourseName(), grade);
    }
}
