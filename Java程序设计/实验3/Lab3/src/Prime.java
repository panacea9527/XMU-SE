public class Prime {
    public static boolean isPrime(int number) {
        if (number <= 1) {
            return false;
        }
        for (int i = 2; i <= number / 2; i++) {
            if (number % i == 0) {
                return false;
            }
        }
        return true;
    }
    public static boolean isPrimeOptimized(int number) {
        if (number <= 1) {
            return false;
        }
        for (int i = 2; i * i <= number; i++) {
            if (number % i == 0) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        long startTime, endTime;
        startTime = System.currentTimeMillis();
        for (int i = 2; i < 10000; i++) {
            if (isPrime(i)) {
                System.out.println(i);
            }
        }
        endTime = System.currentTimeMillis();
        System.out.println("未优化方法所用时间为: " + (endTime - startTime) + " ms。");
        startTime = System.currentTimeMillis();
        for (int i = 2; i < 10000; i++) {
            if (isPrimeOptimized(i)) {
            }
        }
        endTime = System.currentTimeMillis();
        System.out.println("优化后的方法所用时间为: " + (endTime - startTime) + " ms。");
    }
}
