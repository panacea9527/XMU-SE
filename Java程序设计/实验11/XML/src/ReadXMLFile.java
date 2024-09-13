import org.w3c.dom.*;
import javax.xml.parsers.*;
import java.io.File;

public class ReadXMLFile {
    public static void main(String[] args) {
        try {
            // 创建一个DocumentBuilderFactory对象
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            // 创建一个DocumentBuilder对象
            DocumentBuilder builder = factory.newDocumentBuilder();
            // 解析XML文件并获取Document对象
            File xmlFile = new File("Student.xml");
            Document document = builder.parse(xmlFile);
            // 规范化XML结构
            document.getDocumentElement().normalize();

            Element root = document.getDocumentElement();
            System.out.println("根元素: " + root.getNodeName());
            NodeList nodeList = document.getElementsByTagName("student");
            for (int i = 0; i < nodeList.getLength(); i++) {
                Node node = nodeList.item(i);
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    Element student = (Element) node;
                    String id = student.getElementsByTagName("id").item(0).getTextContent();
                    String name = student.getElementsByTagName("name").item(0).getTextContent();
                    String phone = student.getElementsByTagName("phone").item(0).getTextContent();
                    String email = student.getElementsByTagName("email").item(0).getTextContent();

                    System.out.println("学生ID: " + id);
                    System.out.println("姓名: " + name);
                    System.out.println("电话: " + phone);
                    System.out.println("邮箱: " + email);
                    System.out.println("----------------------");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
