import java.util.Random;

public class Main {
    public static void main(String[] args) {
        SharedArray sharedArray = new SharedArray(10000);
        int[] range1 = generateRandomRange(1, 10, 2500);
        int[] range2 = generateRandomRange(100, 1000, 2500);
        int[] range3 = generateRandomRange(2000, 3000, 2500);
        int[] range4 = generateRandomRange(4000, 5000, 2500);
        Thread thread1 = new Thread(new MyRunnable(sharedArray, range1, 0));
        Thread thread2 = new Thread(new MyRunnable(sharedArray, range2, 1));
        Thread thread3 = new Thread(new MyRunnable(sharedArray, range3, 2));
        Thread thread4 = new Thread(new MyRunnable(sharedArray, range4, 3));
        thread1.start();
        thread2.start();
        thread3.start();
        thread4.start();
        try {
            thread1.join();
            thread2.join();
            thread3.join();
            thread4.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        sharedArray.printArray();
    }

    private static int[] generateRandomRange(int start, int end, int size) {
        Random random = new Random();
        int[] range = new int[size];
        for (int i = 0; i < size; i++) {
            range[i] = random.nextInt(end - start + 1) + start;
        }
        return range;
    }
}
