import java.util.Map;

public class Bicycle implements CarbonFootprint {
    private String name;
    private String type; // 小型、中型、大型
    private double mileage; // 里程数，单位为公里
    private static final Map<String, Double> efficiencyMap = Map.of(
            "小型", 83.19,
            "中型", 101.08,
            "大型", 132.52);

    public Bicycle(String name, String type, double mileage) {
        this.name = name;
        this.type = type;
        this.mileage = mileage;
    }

    @Override
    public double getCarbonFootprint() {
        double efficiency = efficiencyMap.getOrDefault(type, 0.0);
        // 计算总碳排放量（克），然后将结果从克转换为吨
        double carbonFootprintInGrams = efficiency * mileage;
        return carbonFootprintInGrams / 1_000_000;
    }

    public String getName() {
        return name;
    }
}
