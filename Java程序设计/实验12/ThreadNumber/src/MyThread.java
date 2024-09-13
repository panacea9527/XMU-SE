class MyThread extends Thread {
    private String threadName;
    public MyThread(String name) {
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
        MyThread thread1 = new MyThread("Thread1");
        MyThread thread2 = new MyThread("Thread2");
        thread1.start();
        thread2.start();
    }
}

