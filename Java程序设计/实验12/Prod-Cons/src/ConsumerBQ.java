import java.util.concurrent.BlockingQueue;

class ConsumerBQ implements Runnable {
    private final BlockingQueue<Integer> queue;

    public ConsumerBQ(BlockingQueue<Integer> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        try {
            for (int i = 0; i < 10; i++) {
                int value = queue.take();
                System.out.println("Consumed: " + value);
                Thread.sleep(150);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
