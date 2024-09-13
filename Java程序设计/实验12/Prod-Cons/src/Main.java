import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class Main {
    public static void main(String[] args) {
        System.out.println("Using wait() and notify():");
        CircularBuffer buffer = new CircularBuffer(4);
        Thread producerThread = new Thread(new Producer(buffer));
        Thread consumerThread = new Thread(new Consumer(buffer));
        producerThread.start();
        consumerThread.start();
        try {
            producerThread.join();
            consumerThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Using BlockingQueue:");
        BlockingQueue<Integer> blockingQueue = new ArrayBlockingQueue<>(4);
        Thread producerThreadBQ = new Thread(new ProducerBQ(blockingQueue));
        Thread consumerThreadBQ = new Thread(new ConsumerBQ(blockingQueue));
        producerThreadBQ.start();
        consumerThreadBQ.start();
        try {
            producerThreadBQ.join();
            consumerThreadBQ.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

