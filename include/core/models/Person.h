#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class Person {
protected:
    std::string id;
    std::string fullName;
    std::string dateOfBirth; // DD/MM/YYYY
    std::string gender;      // Nam / Nữ
    std::string phone;
    std::string address;

public:
    Person();
    Person(const std::string& id,
           const std::string& fullName,
           const std::string& dateOfBirth,
           const std::string& gender,
           const std::string& phone,
           const std::string& address);
    virtual ~Person() = default;

    // Getters & Setters
    std::string getId() const;
    void setId(const std::string& id);

    std::string getFullName() const;
    void setFullName(const std::string& fullName);

    std::string getDateOfBirth() const;
    void setDateOfBirth(const std::string& dateOfBirth);

    std::string getGender() const;
    void setGender(const std::string& gender);

    std::string getPhone() const;
    void setPhone(const std::string& phone);

    std::string getAddress() const;
    void setAddress(const std::string& address);

    // Polymorphic methods
    virtual std::string getRole() const = 0;
    virtual void displayInfo() const;
};

#endif // PERSON_H
