public class Main {
    public static void main(String[] args) {
        Pair<String, Integer> pair1 = new Pair<>();
        pair1.setFirst("World");
        pair1.setSecond(123);
        System.out.println("Pair<String, Integer>.First is \"" + pair1.getFirst()+"\"");
        System.out.println("Pair<String, Integer>.Second is \"" + pair1.getSecond()+"\"");

        Pair<String, Pair<String, Integer> > pair2 = new Pair<>();
        pair2.setFirst("Hello");
        pair2.setSecond(pair1);
        System.out.println("Pair<String, Pair<String, Integer> >.First is \"" + pair2.getFirst()+"\"");
        System.out.println("Pair<String, Pair<String, Integer> >.Second.first is \"" + pair2.getSecond().getFirst()+"\"");
        System.out.println("Pair<String, Pair<String, Integer> >.Second.second is \"" + pair2.getSecond().getSecond()+"\"");
    }
}