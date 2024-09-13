class Vehicle {
    void run() {
        System.out.println("这是交通工具run方法");
    }
}

class Motor extends Vehicle {
    @Override
    void run() {
        System.out.println("这是汽车run方法");
    }
}

class Ship extends Vehicle {
    @Override
    void run() {
        System.out.println("这是船run方法");
    }
}

class Airplane extends Vehicle {
    @Override
    void run() {
        System.out.println("这是飞机run方法");
    }
}

class Bus extends Motor {
    @Override
    void run() {
        System.out.println("这是公共汽车run方法");
    }
}

class Car extends Motor {
    @Override
    void run() {
        System.out.println("这是轿车run方法");
    }
}
