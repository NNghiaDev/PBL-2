#ifndef MEDICAL_RECORD_SERVICE_H
#define MEDICAL_RECORD_SERVICE_H

#include "dao/IMedicalRecordDAO.h"
#include "core/services/PharmacyService.h"
#include <memory>
#include <vector>
#include <string>

class MedicalRecordService {
private:
    std::shared_ptr<IMedicalRecordDAO> recordDao;
    std::shared_ptr<PharmacyService> pharmacyService;

public:
    MedicalRecordService(std::shared_ptr<IMedicalRecordDAO> dao,
                         std::shared_ptr<PharmacyService> pharmService);

    std::vector<MedicalRecord> getAllRecords();
    std::optional<MedicalRecord> findRecordById(const std::string& id);
    std::vector<MedicalRecord> getRecordsByPatientId(const std::string& patientId);

    // Business flow: create record and automatically deduct pharmacy stock
    bool createMedicalRecord(const MedicalRecord& record);
    bool updateMedicalRecord(const MedicalRecord& record);
    bool removeMedicalRecord(const std::string& id);

    // Tu dong sinh ma benh an ke tiep (vd: BA001, BA002, ...)
    std::string generateNextRecordId();
};

#endif // MEDICAL_RECORD_SERVICE_H
