public class Main {
    public static void main(String[] args) {
        RethrowException rethrow = new RethrowException();
            try {
                rethrow.someMethod();
            } catch (Exception e) {
                e.printStackTrace();
            }
    }
}