import java.util.Random;
import java.util.concurrent.BlockingQueue;

class ProducerBQ implements Runnable {
    private final BlockingQueue<Integer> queue;
    private final Random random = new Random();

    public ProducerBQ(BlockingQueue<Integer> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        try {
            for (int i = 0; i < 10; i++) {
                int value = random.nextInt(10) + 1;
                queue.put(value);
                System.out.println("Produced: " + value);
                Thread.sleep(100);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

