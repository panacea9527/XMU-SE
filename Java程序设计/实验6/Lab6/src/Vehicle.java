// 基类
abstract class Vehicle {
    String brand;
    String color;
    int year;

    public Vehicle(String brand, String color, int year) {
        if (brand == null || color == null) {
            throw new IllegalArgumentException("品牌和颜色不能为空");
        }
        if (year < 1886) {
            throw new IllegalArgumentException("出厂年份不应该早于1886年");
        }
        this.brand = brand;
        this.color = color;
        this.year = year;
    }

    abstract String getInformation();
}

// 派生类 - 小汽车
class Car extends Vehicle {
    int passengerCapacity;
    String carriage;

    public Car(String brand, String color, int passengerCapacity, int year, String carriage) {
        super(brand, color, year);
        if (passengerCapacity < 0) {
            throw new IllegalArgumentException("载客量不能为负数");
        }
        if (carriage == null) {
            throw new IllegalArgumentException("厢数不能为空");
        }
        this.passengerCapacity = passengerCapacity;
            this.carriage = carriage;
    }

    @Override
    String getInformation() {
        return String.format("小汽车，品牌：%s 颜色：%s 出厂年份：%d 载客量：%d人 厢数：%s", brand, color, year, passengerCapacity, carriage);
    }
}

// 派生类 - 卡车
class Truck extends Vehicle {
    double loadCapacity;

    public Truck(String brand, String color, double loadCapacity, int year) {
        super(brand, color, year);
        if (loadCapacity < 0) {
            throw new IllegalArgumentException("载重量不能为负数");
        }
        this.loadCapacity = loadCapacity;
    }

    @Override
    String getInformation() {
        return String.format("卡车，品牌：%s 颜色：%s 出厂年份：%d 载重量：%s吨", brand, color, year, loadCapacity);
    }

}
