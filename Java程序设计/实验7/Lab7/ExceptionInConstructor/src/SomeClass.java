public class SomeClass {
    int num;
    public SomeClass(int num) throws Exception {
        if (num < 0) {
            throw new Exception("构造方法失败，输入的整数小于0");
        }
        else {
            System.out.println("构造方法成功");
            this.num=num;
        }
    }
}

