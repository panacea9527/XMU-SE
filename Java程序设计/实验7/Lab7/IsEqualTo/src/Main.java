public class Main {
    public static <T> boolean isEqualTo(T a, T b) {
        return a.equals(b);
    }

    public static void main(String[] args) {
        Object a = new Object();
        Object b = new Object();
        System.out.println(isEqualTo(1, 1));
        System.out.println(isEqualTo(1.0, 1));
        System.out.println(isEqualTo(1.0, 1.000000));
        System.out.println(isEqualTo(1.0, 2));
        System.out.println(isEqualTo(1.14, 1.14));
        System.out.println(isEqualTo(1.14, 2.34));
        System.out.println(isEqualTo("hello", "hello"));
        System.out.println(isEqualTo("hello", "hella"));
        System.out.println(isEqualTo(a, b));

    }
}
