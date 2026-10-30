#ifndef PATIENT_H
#define PATIENT_H

#include "core/models/Person.h"

class Patient : public Person {
private:
    std::string healthInsuranceId; // Mã BHYT
    std::string bloodType;         // Nhóm máu (A, B, AB, O)
    std::string emergencyContact;  // Số điện thoại người thân
    int priorityLevel;             // 1: Cấp cứu, 2: Ưu tiên, 3: Bình thường

public:
    Patient();
    Patient(const std::string& id,
            const std::string& fullName,
            const std::string& dateOfBirth,
            const std::string& gender,
            const std::string& phone,
            const std::string& address,
            const std::string& healthInsuranceId,
            const std::string& bloodType,
            const std::string& emergencyContact,
            int priorityLevel = 3);

    std::string getHealthInsuranceId() const;
    void setHealthInsuranceId(const std::string& insuranceId);

    std::string getBloodType() const;
    void setBloodType(const std::string& bloodType);

    std::string getEmergencyContact() const;
    void setEmergencyContact(const std::string& emergencyContact);

    int getPriorityLevel() const;
    void setPriorityLevel(int priorityLevel);

    std::string getPriorityDescription() const;

    // Override polymorphic methods
    std::string getRole() const override;
    void displayInfo() const override;

    // Comparison for Priority Queue: level 1 is highest priority
    bool operator<(const Patient& other) const {
        return this->priorityLevel > other.priorityLevel; // smaller number = higher priority
    }
};

#endif // PATIENT_H
