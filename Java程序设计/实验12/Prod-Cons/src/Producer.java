import java.util.Random;

class Producer implements Runnable {
    private final CircularBuffer buffer;
    private final Random random = new Random();

    public Producer(CircularBuffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        try {
            for (int i = 0; i < 10; i++) {
                int value = random.nextInt(10) + 1;
                buffer.put(value);
                System.out.println("Produced: " + value);
                Thread.sleep(100);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}

