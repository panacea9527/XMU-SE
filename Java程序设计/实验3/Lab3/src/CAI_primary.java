import java.security.SecureRandom;
import java.util.Scanner;

public class CAI_primary {
    private static final SecureRandom randomNumbers = new SecureRandom();
    private static final Scanner input = new Scanner(System.in);

    public static void main(String[] args) {
        while (true) {
            generateNewQuestion();
        }
    }

    private static void generateNewQuestion() {
        int num1 = 1 + randomNumbers.nextInt(9);
        int num2 = 1 + randomNumbers.nextInt(9);

        int Answer = num1 * num2;
        System.out.printf("How much is %d times %d?\n", num1, num2);

        int studentAnswer = input.nextInt();

        while (studentAnswer != Answer) {
            System.out.println("No. Please try again.");
            studentAnswer = input.nextInt();
        }

        System.out.println("Very good!");
    }

}
