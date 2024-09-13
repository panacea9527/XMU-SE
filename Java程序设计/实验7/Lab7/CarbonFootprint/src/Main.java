import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        // 创建 Bicycle 对象
        Bicycle bike1 = new Bicycle("丰田摩托车", "小型", 5000);
        Bicycle bike2 = new Bicycle("宝马摩托车", "中型", 7000);

        // 创建 Car 对象
        Car car1 = new Car("大型燃油轿车", "Petrol Car Large", 10000);
        Car car2 = new Car("家用轿车", "Petrol Car Medium", 15000);

        // 创建 Building 对象
        Building building1 = new Building("张三家庭",1000, 500, 300, 2, 100, 50, 5);
        Building building2 = new Building("李四家庭",2000, 1000, 600, 4, 200, 100, 10);

        // 将所有对象添加到 CarbonFootprint 列表中
        List<CarbonFootprint> items = new ArrayList<>();
        items.add(bike1);
        items.add(bike2);
        items.add(car1);
        items.add(car2);
        items.add(building1);
        items.add(building2);

        // 遍历列表并打印每个对象的碳足迹
        for (CarbonFootprint item : items) {
            System.out.print(item.getClass().getSimpleName() +" Carbon Footprint: " + item.getCarbonFootprint() + " tons CO2 produced by ");
            if (item instanceof Bicycle) {
                System.out.println( ((Bicycle) item).getName());
            } else if (item instanceof Car) {
                System.out.println( ((Car) item).getName());
            }
            else if(item instanceof Building) {
                System.out.println( ((Building) item).getName());
            }
            System.out.println();
        }
    }
}
