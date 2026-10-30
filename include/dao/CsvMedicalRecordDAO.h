#ifndef CSV_MEDICAL_RECORD_DAO_H
#define CSV_MEDICAL_RECORD_DAO_H

#include "dao/IMedicalRecordDAO.h"
#include <string>

class CsvMedicalRecordDAO : public IMedicalRecordDAO {
private:
    std::string filePath;
    void ensureFileExists();
    std::string serializePrescriptions(const std::vector<PrescriptionDetail>& list);
    std::vector<PrescriptionDetail> deserializePrescriptions(const std::string& str);

public:
    explicit CsvMedicalRecordDAO(const std::string& filePath = "data/medical_records.csv");

    std::vector<MedicalRecord> getAll() override;
    std::optional<MedicalRecord> getById(const std::string& id) override;
    std::vector<MedicalRecord> getByPatientId(const std::string& patientId) override;
    bool add(const MedicalRecord& record) override;
    bool update(const MedicalRecord& record) override;
    bool remove(const std::string& id) override;
};

#endif // CSV_MEDICAL_RECORD_DAO_H
