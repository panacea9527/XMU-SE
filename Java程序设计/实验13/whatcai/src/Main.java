import java.util.*;

public class Main {
    public static void main(String[] args) {
        person p=new student();
        p.returnthis();
    }

}

class person{
    protected person returnthis(){
        System.out.println("fulei");
        return this;
    }
}

class student extends person {
    public student returnthis(){
        System.out.println("zilei");
        return this;
    }
}