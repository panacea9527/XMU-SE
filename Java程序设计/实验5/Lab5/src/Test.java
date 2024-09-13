public class Test {
    public static void main(String[] args) {
        // 使用父类引用指向子类对象，体现多态
        Vehicle motor = new Motor();
        motor.run();

        Vehicle ship = new Ship();
        ship.run();

        Vehicle airplane = new Airplane();
        airplane.run();

        Motor bus = new Bus();
        bus.run();

        Motor car = new Car();
        car.run();
    }
}