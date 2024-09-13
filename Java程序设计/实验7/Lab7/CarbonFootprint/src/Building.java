public class Building implements CarbonFootprint {
    private String name;
    private double electricity; // 单位: kWh
    private double naturalGas; // 单位: kWh
    private double heatingOil; // 单位: 公升
    private double coal; // 单位: 吨
    private double liquefiedGas; // 单位: 公升
    private double propane; // 单位: 公升
    private double woodChips; // 单位: 吨

    // 系数，单位转换为吨 CO2
    private static final double CO2_ELECTRICITY = 0.0005572;
    private static final double CO2_NATURAL_GAS = 0.00018293;
    private static final double CO2_HeatingOil = 0.00254016;
    private static final double CO2_COAL = 2.90495;
    private static final double CO2_LIQUEFIED_GAS = 0.00155713;
    private static final double CO2_PROPANE = 0.00154358;
    private static final double CO2_WOOD_CHIPS = 0.05156192;

    public Building(String name,double electricity, double naturalGas, double heatingOil, double coal, double liquefiedGas, double propane, double woodChips) {
        this.electricity = electricity;
        this.naturalGas = naturalGas;
        this.heatingOil = heatingOil;
        this.coal = coal;
        this.liquefiedGas = liquefiedGas;
        this.propane = propane;
        this.woodChips = woodChips;
        this.name=name;
    }

    @Override
    public double getCarbonFootprint() {
        // 计算每种能源的碳足迹总和
        double totalCarbonFootprint =
                (electricity * CO2_ELECTRICITY) +
                        (naturalGas * CO2_NATURAL_GAS) +
                        (heatingOil * CO2_HeatingOil) +
                        (coal * CO2_COAL) +
                        (liquefiedGas * CO2_LIQUEFIED_GAS) +
                        (propane * CO2_PROPANE) +
                        (woodChips * CO2_WOOD_CHIPS);

        return totalCarbonFootprint; // 返回的是吨 CO2
    }

    public String getName() {
        return name;
    }
}

