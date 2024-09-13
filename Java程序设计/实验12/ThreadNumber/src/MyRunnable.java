class MyRunnable implements Runnable {
    private String threadName;
    public MyRunnable(String name) {
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
        Thread thread1 = new Thread(new MyRunnable("Thread1"));
        Thread thread2 = new Thread(new MyRunnable("Thread2"));
        thread1.start();
        thread2.start();
    }
}
