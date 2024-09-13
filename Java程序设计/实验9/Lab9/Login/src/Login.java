import java.util.Scanner;

public class Login {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // 读取和验证用户名
        String username = "";
        while (true) {
            System.out.println("请输入用户名（字母、数字、下划线组成，首字母不能为数字）:");
            try {
                username = scanner.nextLine();
                if (!validateUsername(username)) {
                    throw new IllegalArgumentException("错误：无效的用户名。");
                }
                break;
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
            }
        }

        // 密码
        String password = "";
        while (true) {
            System.out.println("请输入密码（至少8位，包含字母、数字、下划线）:");
            try {
                password = scanner.nextLine();
                if (!validatePassword(password)) {
                    throw new IllegalArgumentException("错误：无效的密码。");
                }
                break;
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
            }
        }

        // 邮箱
        String email = "";
        while (true) {
            System.out.println("请输入邮箱地址:");
            try {
                email = scanner.nextLine();
                if (!validateEmail(email)) {
                    throw new IllegalArgumentException("错误：无效的邮箱地址。");
                }
                break;
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
            }
        }

        scanner.close();
        System.out.println("所有输入都已成功验证。");
    }

    private static boolean validateUsername(String username) {
        String usernamePattern = "^[A-Za-z_][A-Za-z0-9_]*$";
        return username.matches(usernamePattern);
    }

    private static boolean validatePassword(String password) {
        String passwordPattern = "^\\w{8,}$";
        return password.matches(passwordPattern);
    }

    private static boolean validateEmail(String email) {
        String emailPattern = "^[^@\\s]+@[^@\\s]+\\.[^@\\s]+(?:\\.[^@\\s]+)*$";
        return email.matches(emailPattern);
    }
}
