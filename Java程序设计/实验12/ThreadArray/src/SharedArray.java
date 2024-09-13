import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class SharedArray {
    private final int[] array;
    private int currentIndex = 0;
    private final Lock lock = new ReentrantLock();
    private final Condition[] conditions = new Condition[4];
    private int currentThread = 0;
    public SharedArray(int size) {
        array = new int[size];
        for (int i = 0; i < 4; i++) {
            conditions[i] = lock.newCondition();
        }
    }

    public void writeNumber(int number, int threadId) {
        lock.lock();
        try {
            while (currentThread != threadId) {
                conditions[threadId].await();
            }
            if (currentIndex < array.length) {
                array[currentIndex++] = number;
            }
            currentThread = (currentThread + 1) % 4;
            conditions[currentThread].signalAll();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        } finally {
            lock.unlock();
        }
    }

    public void printArray() {
        for (int i = 0; i < currentIndex; i++) {
            System.out.print(array[i] + " ");
        }
        System.out.println();
    }
}