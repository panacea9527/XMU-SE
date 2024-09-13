import java.util.ArrayList;
import java.util.List;

public class VehicleManager {
    private List<Vehicle> vehicles = new ArrayList<>();

    public void addVehicle(Vehicle vehicle) {
        vehicles.add(vehicle);
        System.out.println("创建成功");
        System.out.println(vehicle.getInformation());
        System.out.println();
    }

    public void listVehicles() {
        System.out.printf("目前有%d辆车，信息如下：\n", vehicles.size());
        for (int i = 0; i < vehicles.size(); i++) {
            System.out.println((i + 1) + "：" + vehicles.get(i).getInformation());
        }
        System.out.println();
    }

    public void searchVehicles(String type, String brand, String color, String year) {
        List<Vehicle> result = new ArrayList<>();
        for (Vehicle vehicle : vehicles) {
            boolean typeMatch = false;
            if (type.equalsIgnoreCase("小汽车")) {
                typeMatch = vehicle instanceof Car;
            } else if (type.equalsIgnoreCase("卡车")) {
                typeMatch = vehicle instanceof Truck;
            } else if (type.equalsIgnoreCase("null")) {
                typeMatch = true; // 如果类型条件为 "null"，忽略类型判断
            }

            boolean matches = typeMatch
                    && (brand.equalsIgnoreCase("null") || vehicle.brand.equalsIgnoreCase(brand))
                    && (color.equalsIgnoreCase("null") || vehicle.color.equalsIgnoreCase(color))
                    && (year.equalsIgnoreCase("null") || Integer.toString(vehicle.year).equals(year));
            if (matches) {
                result.add(vehicle);
            }
        }

        if (result.isEmpty()) {
            System.out.println("没有搜索到相应的交通工具\n");
        } else {
            System.out.printf("搜索到%d辆车，信息如下：\n", result.size());
            for (Vehicle vehicle : result) {
                System.out.println(vehicle.getInformation());
            }
            System.out.println();
        }
    }

}
