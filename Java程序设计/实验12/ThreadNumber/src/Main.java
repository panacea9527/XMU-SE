public class Main {
    public static void main(String[] args) {
        System.out.println("----继承Thread----");
        MyThread.test();
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("----实现Runnable接口，用Thread方法启动线程----");
        MyRunnable.test();
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("----用线程池管理----");
        ThreadPool.test();
    }
}