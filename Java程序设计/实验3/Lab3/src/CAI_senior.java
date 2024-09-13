import java.security.SecureRandom;
import java.util.Scanner;

public class CAI_senior {

    private static final SecureRandom randomNumbers = new SecureRandom();
    private static final Scanner input = new Scanner(System.in);
    private static int correctAnswers = 0;
    private static int totalAttempts = 0;

    public static void main(String[] args) {
        while (true) {
            for (int i = 0; i < 10; i++) {
                generateNewQuestion();
            }
            displayPerformance();
            resetForNewStudent();
        }
    }

    private static void generateNewQuestion() {
        int num1 = 1 + randomNumbers.nextInt(9);
        int num2 = 1 + randomNumbers.nextInt(9);

        int correctAnswer = num1 * num2;
        System.out.printf("How much is %d times %d?\n", num1, num2);

        int studentAnswer = input.nextInt();
        totalAttempts++;

        while (studentAnswer != correctAnswer) {
            provideFeedback(false);
            studentAnswer = input.nextInt();
            totalAttempts++;
        }

        provideFeedback(true);
        correctAnswers++;
    }

    private static void provideFeedback(boolean isCorrect) {
        int responseIndex = 1 + randomNumbers.nextInt(4);
        if (isCorrect) {
            switch (responseIndex) {
                case 1:
                    System.out.println("Very good!");
                    break;
                case 2:
                    System.out.println("Excellent!");
                    break;
                case 3:
                    System.out.println("Nice work!");
                    break;
                case 4:
                    System.out.println("Keep up the good work!");
                    break;
            }
        } else {
            switch (responseIndex) {
                case 1:
                    System.out.println("No. Please try again.");
                    break;
                case 2:
                    System.out.println("Wrong. Try once more.");
                    break;
                case 3:
                    System.out.println("Don't give up!");
                    break;
                case 4:
                    System.out.println("No. Keep trying.");
                    break;
            }
        }
    }

    private static void displayPerformance() {
        double correctRate = ((double) correctAnswers / totalAttempts) * 100;
        System.out.printf("Correct rate: %.2f%%\n", correctRate);
        if (correctRate < 75) {
            System.out.println("Please ask your teacher for extra help.");
        } else {
            System.out.println("Congratulations, you are ready to go to the next level!");
        }
    }

    private static void resetForNewStudent() {
        System.out.println("\nNew student can start answering questions.\n");
        //重置变量
        correctAnswers = 0;
        totalAttempts = 0;
    }
}

