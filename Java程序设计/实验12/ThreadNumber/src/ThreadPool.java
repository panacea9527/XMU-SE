import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class ThreadPool implements Runnable {
    private String threadName;
    public ThreadPool(String name) {
        this.threadName = name;
    }
    @Override
    public void run() {
        for (int i = 1; i <= 10; i++) {
            System.out.println(threadName + "-" + i);
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    public static void test() {
        ExecutorService executor = Executors.newFixedThreadPool(2);
        executor.execute(new ThreadPool("Thread1"));
        executor.execute(new ThreadPool("Thread2"));
        executor.shutdown();
    }
}
