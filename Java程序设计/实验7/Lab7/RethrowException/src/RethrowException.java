public class RethrowException {

    public static void someMethod2() throws Exception {
        throw new Exception("An exception from someMethod2");
    }

    public static void someMethod() throws Exception {
        try {
            someMethod2();
        } catch (Exception e) {
            throw new Exception("An exception from someMethod", e);
        }
    }

}