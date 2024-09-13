class MyRunnable implements Runnable {
    private final SharedArray sharedArray;
    private final int[] numbers;
    private final int threadId;

    public MyRunnable(SharedArray sharedArray, int[] numbers, int threadId) {
        this.sharedArray = sharedArray;
        this.numbers = numbers;
        this.threadId = threadId;
    }

    @Override
    public void run() {
        for (int number : numbers) {
            sharedArray.writeNumber(number, threadId);
        }
    }
}