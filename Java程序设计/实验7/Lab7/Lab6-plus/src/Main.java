import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        VehicleManager manager = new VehicleManager();
        Scanner scanner = new Scanner(System.in);
        boolean flag = true;

        while (flag) {
            System.out.println("请输入对应输入进行相应菜单操作：\n1. 新增车辆\n2. 查询车辆\n3. 列出所有车辆\n4. 结束程序");
            String choice = scanner.nextLine();
            switch (choice) {
                case "1" -> addVehicle(scanner, manager);
                case "2" -> searchVehicle(scanner, manager);
                case "3" -> manager.listVehicles();
                case "4" -> flag = false;
                default -> System.out.println("请输入1-4的整数\n");
            }
        }
        scanner.close();
    }

    private static void addVehicle(Scanner scanner, VehicleManager manager) {
        System.out.println("请输入车辆信息，示例：\n小汽车 丰田 红色 4 2007 2厢\n卡车 雷诺 红色 3.5 2008\n结束新增，请输入end");
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if ("end".equalsIgnoreCase(line)) {
                break;
            }
            String[] parts = line.split(" ");
            try {
                if (parts[0].equalsIgnoreCase("小汽车")) {
                    if (parts.length != 6) {
                        throw new IllegalArgumentException("小汽车的输入格式不正确，正确格式为：小汽车 品牌 颜色 载客量 年份 厢数");
                    }
                    try {
                        Car car = new Car(parts[1], parts[2], Integer.parseInt(parts[3]), Integer.parseInt(parts[4]), parts[5]);
                        manager.addVehicle(car);
                    } catch (NumberFormatException e) {
                        throw new IllegalArgumentException("小汽车的载客量或出厂年份必须是整数");
                    }
                } else if (parts[0].equalsIgnoreCase("卡车")) {
                    if (parts.length != 5) {
                        throw new IllegalArgumentException("卡车的输入格式不正确，正确格式为：卡车 品牌 颜色 载重 出厂年份");
                    }
                    try {
                        Truck truck = new Truck(parts[1], parts[2], Double.parseDouble(parts[3]), Integer.parseInt(parts[4]));
                        manager.addVehicle(truck);
                    } catch (NumberFormatException e) {
                        throw new IllegalArgumentException("卡车的载重或出厂年份必须能正确转换为数值");
                    }
                } else {
                    throw new IllegalArgumentException("第一个词应为小汽车或者卡车");
                }
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
                System.out.println("创建不成功\n");
            }
            System.out.println("请输入车辆信息，示例：\n小汽车 丰田 红色 4 2007 2厢\n卡车 雷诺 红色 3.5 2008\n结束新增，请输入end");
        }
    }

    private static void searchVehicle(Scanner scanner, VehicleManager manager) {
        System.out.println("请按照“类型 商标 颜色 出厂年”的顺序输入条件，若条件为空用“null”代替，2个示例：\n小汽车 丰田 红色 2007\nnull 丰田 null null\n输入end返回上级菜单");
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if ("end".equalsIgnoreCase(line)) {
                break;
            }

            String[] parts = line.split(" ");
            if (parts.length == 4) {
                if (!parts[0].equalsIgnoreCase("null") && !parts[0].equalsIgnoreCase("小汽车") && !parts[0].equalsIgnoreCase("卡车")) {
                    System.out.println("没有搜索到相应的交通工具\n");
                    System.out.println("请按照“类型 商标 颜色 出厂年”的顺序输入条件，若条件为空用“null”代替，2个示例：\n小汽车 丰田 红色 2007\nnull 丰田 null null\n输入end返回上级菜单");
                    continue;
                }
                manager.searchVehicles(parts[0], parts[1], parts[2], parts[3]);
            } else {
                System.out.println("输入格式错误，请按照示例重新输入\n");
            }
            System.out.println("请按照“类型 商标 颜色 出厂年”的顺序输入条件，若条件为空用“null”代替，2个示例：\n小汽车 丰田 红色 2007\nnull 丰田 null null\n输入end返回上级菜单");
        }
    }
}
