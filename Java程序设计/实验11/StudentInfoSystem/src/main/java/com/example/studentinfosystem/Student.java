package com.example.studentinfosystem;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Student {
    private final StringProperty id;
    private final StringProperty name;
    private final StringProperty phone;
    private final StringProperty email;
    private final StringProperty photoPath;

    public Student(String id, String name, String phone, String email, String photoPath) {
        this.id = new SimpleStringProperty(id);
        this.name = new SimpleStringProperty(name);
        this.phone = new SimpleStringProperty(phone);
        this.email = new SimpleStringProperty(email);
        this.photoPath = new SimpleStringProperty(photoPath);
    }

    public String getId() {
        return id.get();
    }

    public void setId(String id) {
        this.id.set(id);
    }

    public StringProperty idProperty() {
        return id;
    }

    public String getName() {
        return name.get();
    }

    public void setName(String name) {
        this.name.set(name);
    }

    public StringProperty nameProperty() {
        return name;
    }

    public String getPhone() {
        return phone.get();
    }

    public void setPhone(String phone) {
        this.phone.set(phone);
    }

    public StringProperty phoneProperty() {
        return phone;
    }

    public String getEmail() {
        return email.get();
    }

    public void setEmail(String email) {
        this.email.set(email);
    }

    public StringProperty emailProperty() {
        return email;
    }

    public String getPhotoPath() {
        return photoPath.get();
    }

    public void setPhotoPath(String photoPath) {
        this.photoPath.set(photoPath);
    }

    public StringProperty photoPathProperty() {
        return photoPath;
    }

    @Override
    public String toString() {
        return id.get() + "," + name.get() + "," + phone.get() + "," + email.get() + "," + photoPath.get();
    }

    public static Student fromString(String str) {
        String[] parts = str.split(",");
        if (parts.length < 5) {
            throw new IllegalArgumentException("Invalid student data: " + str);
        }
        return new Student(parts[0], parts[1], parts[2], parts[3], parts[4]);
    }
}


