#ifndef DOCTOR_H
#define DOCTOR_H

#include "core/models/Person.h"

class Doctor : public Person {
private:
    std::string specialty;       // Chuyên khoa (Noi khoa, Ngoai khoa, Nhi khoa,...)
    std::string licenseNumber;   // Số chứng chỉ hành nghề
    std::string departmentId;    // Mã khoa phòng
    int yearsOfExperience;       // Số năm kinh nghiệm

public:
    Doctor();
    Doctor(const std::string& id,
           const std::string& fullName,
           const std::string& dateOfBirth,
           const std::string& gender,
           const std::string& phone,
           const std::string& address,
           const std::string& specialty,
           const std::string& licenseNumber,
           const std::string& departmentId,
           int yearsOfExperience = 0);

    std::string getSpecialty() const;
    void setSpecialty(const std::string& specialty);

    std::string getLicenseNumber() const;
    void setLicenseNumber(const std::string& licenseNumber);

    std::string getDepartmentId() const;
    void setDepartmentId(const std::string& departmentId);

    int getYearsOfExperience() const;
    void setYearsOfExperience(int years);

    // Override polymorphic methods
    std::string getRole() const override;
    void displayInfo() const override;
};

#endif // DOCTOR_H
