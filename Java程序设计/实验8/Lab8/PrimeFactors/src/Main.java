import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入一个整数：");

        int number = scanner.nextInt();
        if (isPrime(number)) {
            System.out.println(number + " 是质数。");
        } else {
            System.out.println(number + " 不是质数，它的质因子有：" + getPrimeFactors(number));
        }
        scanner.close();
    }

    private static boolean isPrime(int num) {
        if (num <= 1) {
            return false;
        }
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    private static Set<Integer> getPrimeFactors(int number) {
        Set<Integer> factors = new HashSet<>();
        while (number % 2 == 0) {
            factors.add(2);
            number /= 2;
        }
        for (int i = 3; i <= Math.sqrt(number); i += 2) {
            while (number % i == 0) {
                factors.add(i);
                number /= i;
            }
        }
        if (number > 2) {
            factors.add(number);
        }
        return factors;
    }
}