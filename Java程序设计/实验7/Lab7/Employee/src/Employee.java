public class Employee {
    private  String firstName;
    private  String lastName;
    private  String socialSecurityNumber;

    private CompensationModel compensationModel;

    public Employee(String firstName, String lastName,
                    String socialSecurityNumber,CompensationModel compensationModel) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.socialSecurityNumber = socialSecurityNumber;
        this.compensationModel=compensationModel;
    }
    public double earnings() {
        return compensationModel.earnings();
    }
    public void setCompensationModel(CompensationModel compensationModel) {
        this.compensationModel = compensationModel;
    }

    public String getFirstName() {return firstName;}

    public String getLastName() {return lastName;}

    public String getSocialSecurityNumber() {return socialSecurityNumber;}

    @Override
    public String toString() {
        return String.format("%s %s%nsocial security number: %s",
                getFirstName(), getLastName(), getSocialSecurityNumber());
    }

}
