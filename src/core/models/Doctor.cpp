#include "core/models/Doctor.h"

Doctor::Doctor()
    : Person(), specialty(""), licenseNumber(""), departmentId(""), yearsOfExperience(0) {}

Doctor::Doctor(const std::string& id,
               const std::string& fullName,
               const std::string& dateOfBirth,
               const std::string& gender,
               const std::string& phone,
               const std::string& address,
               const std::string& specialty,
               const std::string& licenseNumber,
               const std::string& departmentId,
               int yearsOfExperience)
    : Person(id, fullName, dateOfBirth, gender, phone, address),
      specialty(specialty),
      licenseNumber(licenseNumber),
      departmentId(departmentId),
      yearsOfExperience(yearsOfExperience) {}

std::string Doctor::getSpecialty() const { return specialty; }
void Doctor::setSpecialty(const std::string& specialty) { this->specialty = specialty; }

std::string Doctor::getLicenseNumber() const { return licenseNumber; }
void Doctor::setLicenseNumber(const std::string& licenseNumber) { this->licenseNumber = licenseNumber; }

std::string Doctor::getDepartmentId() const { return departmentId; }
void Doctor::setDepartmentId(const std::string& departmentId) { this->departmentId = departmentId; }

int Doctor::getYearsOfExperience() const { return yearsOfExperience; }
void Doctor::setYearsOfExperience(int years) { this->yearsOfExperience = years; }

std::string Doctor::getRole() const {
    return "Bac si";
}

void Doctor::displayInfo() const {
    Person::displayInfo();
    std::cout << "  -> Chuyen khoa: " << specialty
              << " | Khoa phong: " << departmentId
              << " | CCHN: " << licenseNumber
              << " | Kinh nghiem: " << yearsOfExperience << " nam" << std::endl;
}
