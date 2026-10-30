#include "core/services/PatientService.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cctype>

PatientService::PatientService(std::shared_ptr<IPatientDAO> dao) : patientDao(dao) {}

std::vector<Patient> PatientService::getAllPatients() {
    return patientDao->getAll();
}

std::optional<Patient> PatientService::findPatientById(const std::string& id) {
    return patientDao->getById(id);
}

bool PatientService::registerPatient(const Patient& patient) {
    if (patient.getId().empty() || patient.getFullName().empty()) {
        return false;
    }
    return patientDao->add(patient);
}

bool PatientService::updatePatientInfo(const Patient& patient) {
    return patientDao->update(patient);
}

bool PatientService::removePatient(const std::string& id) {
    return patientDao->remove(id);
}

std::vector<Patient> PatientService::searchPatients(const std::string& keyword) {
    return patientDao->searchByName(keyword);
}

std::vector<Patient> PatientService::getPatientsSortedByName() {
    auto list = patientDao->getAll();
    DSA::quickSort(list, [](const Patient& a, const Patient& b) {
        return a.getFullName() < b.getFullName();
    });
    return list;
}

std::optional<Patient> PatientService::searchPatientByIdBinary(const std::string& id) {
    auto list = patientDao->getAll();
    // Sort by ID first to apply binary search
    DSA::quickSort(list, [](const Patient& a, const Patient& b) {
        return a.getId() < b.getId();
    });

    int index = DSA::binarySearch(list, id, [](const Patient& p) {
        return p.getId();
    });

    if (index != -1) {
        return list[index];
    }
    return std::nullopt;
}

std::string PatientService::generateNextPatientId() {
    auto list = patientDao->getAll();
    int maxId = 0;
    for (const auto& p : list) {
        std::string id = p.getId();
        if (id.rfind("BN", 0) == 0) {
            std::string numStr = "";
            for (size_t i = 2; i < id.length(); ++i) {
                if (std::isdigit(id[i])) {
                    numStr += id[i];
                }
            }
            if (!numStr.empty()) {
                try {
                    int val = std::stoi(numStr);
                    if (val > maxId) maxId = val;
                } catch (...) {}
            }
        }
    }
    std::ostringstream ss;
    ss << "BN" << std::setw(3) << std::setfill('0') << (maxId + 1);
    return ss.str();
}
