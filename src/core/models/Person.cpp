#include "core/models/Person.h"

Person::Person()
    : id(""), fullName(""), dateOfBirth(""), gender(""), phone(""), address("") {}

Person::Person(const std::string& id,
               const std::string& fullName,
               const std::string& dateOfBirth,
               const std::string& gender,
               const std::string& phone,
               const std::string& address)
    : id(id), fullName(fullName), dateOfBirth(dateOfBirth),
      gender(gender), phone(phone), address(address) {}

std::string Person::getId() const { return id; }
void Person::setId(const std::string& id) { this->id = id; }

std::string Person::getFullName() const { return fullName; }
void Person::setFullName(const std::string& fullName) { this->fullName = fullName; }

std::string Person::getDateOfBirth() const { return dateOfBirth; }
void Person::setDateOfBirth(const std::string& dateOfBirth) { this->dateOfBirth = dateOfBirth; }

std::string Person::getGender() const { return gender; }
void Person::setGender(const std::string& gender) { this->gender = gender; }

std::string Person::getPhone() const { return phone; }
void Person::setPhone(const std::string& phone) { this->phone = phone; }

std::string Person::getAddress() const { return address; }
void Person::setAddress(const std::string& address) { this->address = address; }

void Person::displayInfo() const {
    std::cout << "[" << getRole() << "] " << fullName
              << " | ID: " << id
              << " | NS: " << dateOfBirth
              << " | Gioi tinh: " << gender
              << " | SDT: " << phone
              << " | Dia chi: " << address << std::endl;
}
