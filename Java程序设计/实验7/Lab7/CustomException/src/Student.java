public class Student {
    private String name;
    private String address;

    public void setName(String name) throws IllegaNameException {
        if (name == null || name.length() < 2 || name.length() > 5){
            throw new IllegaNameException("姓名格式不合法");
        }
        this.name = name;
    }

    public void setAddress(String address) throws IllegalAddressException {
        //当地址中不含有“省”或者“市”关键字时抛出IllegalAddressException
        if (!address.contains("省") || !address.contains("市")){
            throw new IllegalAddressException("地址格式不合法");
        }
        this.address = address;
    }

    public String getName() {
        return name;
    }

    public String getAddress() {
        return address;
    }
}
