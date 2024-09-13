public class HourlyCompensationModel implements CompensationModel {
    private double wage;
    private double hours;

    public HourlyCompensationModel(double wage, double hours) {
        this.wage = wage;
        this.hours = hours;
    }
    @Override
    public double earnings() {
        if (getHours() <= 40) { // 没有加班
            return getWage() * getHours();
        }
        else {
            return 40 * getWage() + (getHours() - 40) * getWage() * 1.5;
        }
    }

    public double getHours() {
        return hours;
    }

    public double getWage() {
        return wage;
    }
}
