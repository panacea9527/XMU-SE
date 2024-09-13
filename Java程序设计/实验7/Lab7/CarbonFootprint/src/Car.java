import java.util.Map;

public class Car implements CarbonFootprint {
    private String name; // 汽车名称
    private String type; // 汽车类型
    private double mileage; // 行驶里程，单位为公里
    private static final Map<String, Double> efficiencyMap = Map.ofEntries(
            Map.entry("Petrol Car Large", 272.2385),
            Map.entry("Petrol Car Medium", 178.1885),
            Map.entry("Petrol Car Small", 140.7985),
            Map.entry("Petrol Hybrid Car Large", 152.4358),
            Map.entry("Petrol Hybrid Car Medium", 109.0384),
            Map.entry("Petrol Hybrid Car Small", 101.4989),
            Map.entry("Plug-in Hybrid Car Large", 70.82232),
            Map.entry("Plug-in Hybrid Car Medium", 61.44204),
            Map.entry("Plug-in Hybrid Car Small", 21.63065),
            Map.entry("Electric Car Average", 8.655)
    );

    public Car(String name, String type, double mileage) {
        this.name = name;
        this.type = type;
        this.mileage = mileage;
    }

    @Override
    public double getCarbonFootprint() {
        // 获取当前汽车类型的碳排放效率
        double efficiency = efficiencyMap.getOrDefault(type, 0.0);
        double carbonFootprintInGrams = efficiency * mileage;
        return carbonFootprintInGrams / 1_000_000;
    }

    public String getName() {
        return name;
    }
}
