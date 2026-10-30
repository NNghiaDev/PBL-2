#include "core/models/Patient.h"

Patient::Patient()
    : Person(), healthInsuranceId(""), bloodType("O"), emergencyContact(""), priorityLevel(3) {}

Patient::Patient(const std::string& id,
                 const std::string& fullName,
                 const std::string& dateOfBirth,
                 const std::string& gender,
                 const std::string& phone,
                 const std::string& address,
                 const std::string& healthInsuranceId,
                 const std::string& bloodType,
                 const std::string& emergencyContact,
                 int priorityLevel)
    : Person(id, fullName, dateOfBirth, gender, phone, address),
      healthInsuranceId(healthInsuranceId),
      bloodType(bloodType),
      emergencyContact(emergencyContact),
      priorityLevel(priorityLevel) {}

std::string Patient::getHealthInsuranceId() const { return healthInsuranceId; }
void Patient::setHealthInsuranceId(const std::string& insuranceId) { this->healthInsuranceId = insuranceId; }

std::string Patient::getBloodType() const { return bloodType; }
void Patient::setBloodType(const std::string& bloodType) { this->bloodType = bloodType; }

std::string Patient::getEmergencyContact() const { return emergencyContact; }
void Patient::setEmergencyContact(const std::string& emergencyContact) { this->emergencyContact = emergencyContact; }

int Patient::getPriorityLevel() const { return priorityLevel; }
void Patient::setPriorityLevel(int priorityLevel) { this->priorityLevel = priorityLevel; }

std::string Patient::getPriorityDescription() const {
    switch (priorityLevel) {
        case 1: return "Cap cuu (Khan cap)";
        case 2: return "Uu tien (Tre em/Nguoi gia/Thai phu)";
        case 3:
        default: return "Thong thuong";
    }
}

std::string Patient::getRole() const {
    return "Benh nhan";
}

void Patient::displayInfo() const {
    Person::displayInfo();
    std::cout << "  -> BHYT: " << healthInsuranceId
              << " | Nhom mau: " << bloodType
              << " | Nguoi than: " << emergencyContact
              << " | Muc uu tien: " << getPriorityDescription() << std::endl;
}
