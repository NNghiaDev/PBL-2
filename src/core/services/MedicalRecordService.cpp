#include "core/services/MedicalRecordService.h"
#include <sstream>
#include <iomanip>
#include <cctype>

MedicalRecordService::MedicalRecordService(std::shared_ptr<IMedicalRecordDAO> dao,
                                           std::shared_ptr<PharmacyService> pharmService)
    : recordDao(dao), pharmacyService(pharmService) {}

std::vector<MedicalRecord> MedicalRecordService::getAllRecords() {
    return recordDao->getAll();
}

std::optional<MedicalRecord> MedicalRecordService::findRecordById(const std::string& id) {
    return recordDao->getById(id);
}

std::vector<MedicalRecord> MedicalRecordService::getRecordsByPatientId(const std::string& patientId) {
    return recordDao->getByPatientId(patientId);
}

bool MedicalRecordService::createMedicalRecord(const MedicalRecord& record) {
    if (record.getRecordId().empty() || record.getPatientId().empty() || record.getDoctorId().empty()) {
        return false;
    }

    // Deduct stock for all prescribed medicines
    if (pharmacyService) {
        for (const auto& item : record.getPrescriptions()) {
            pharmacyService->dispenseMedicine(item.getMedicineId(), item.getQuantity());
        }
    }

    return recordDao->add(record);
}

bool MedicalRecordService::updateMedicalRecord(const MedicalRecord& record) {
    return recordDao->update(record);
}

bool MedicalRecordService::removeMedicalRecord(const std::string& id) {
    return recordDao->remove(id);
}

std::string MedicalRecordService::generateNextRecordId() {
    auto list = recordDao->getAll();
    int maxId = 0;
    for (const auto& r : list) {
        std::string id = r.getRecordId();
        if (id.rfind("BA", 0) == 0) {
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
    ss << "BA" << std::setw(3) << std::setfill('0') << (maxId + 1);
    return ss.str();
}
