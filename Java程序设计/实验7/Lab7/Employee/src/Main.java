public class Main {
    public static void main(String[] args) {
        // 创建各种 CompensationModel
        CompensationModel salariedModel = new SalariedCompensationModel(1000);
        CompensationModel hourlyModel = new HourlyCompensationModel(50, 40);
        CompensationModel commissionModel = new CommissionCompensationModel(5000, 0.1);
        CompensationModel basePlusCommissionModel = new BasePlusCommissionCompensationModel(5000, 0.1, 300);

        // 为每种 CompensationModel 创建一个 Employee 对象
        Employee salariedEmployee = new Employee("张","三","fjs123",salariedModel);
        Employee hourlyEmployee = new Employee("李","四","sds123",hourlyModel);
        Employee commissionEmployee = new Employee("王","五","scs123",commissionModel);
        Employee basePlusCommissionEmployee = new Employee("赵","六","gds123",basePlusCommissionModel);

        // 显示每一类员工的收入
        System.out.println("最初的薪资:");
        System.out.println("张三的薪资(周薪固定): " + salariedEmployee.earnings());
        System.out.println("李四的薪资(按时薪计酬): " + hourlyEmployee.earnings());
        System.out.println("王五的薪资(按佣金付酬): " + commissionEmployee.earnings());
        System.out.println("赵六的薪资(按加金付酬): " + basePlusCommissionEmployee.earnings());

        // 动态改变员工的 CompensationModel
        salariedEmployee.setCompensationModel(new HourlyCompensationModel(50, 50));
        hourlyEmployee.setCompensationModel(new CommissionCompensationModel(6000, 0.1));
        commissionEmployee.setCompensationModel(new BasePlusCommissionCompensationModel(6000, 0.2, 300));
        basePlusCommissionEmployee.setCompensationModel(new SalariedCompensationModel(1200));

        // 重新显示每个员工的收入
        System.out.println("\n修改薪酬计算方法后的薪资:");
        System.out.println("张三的薪资( 周薪固定 -> 按时薪计酬 ): " + salariedEmployee.earnings());
        System.out.println("李四的薪资( 按时薪计酬 -> 按佣金付酬 ) " + hourlyEmployee.earnings());
        System.out.println("王五的薪资( 按佣金付酬 -> 按加金付酬 ): " + commissionEmployee.earnings());
        System.out.println("赵六的薪资( 按加金付酬 -> 按时薪计酬): " + basePlusCommissionEmployee.earnings());
    }
}



