#ifndef I_MEDICAL_RECORD_DAO_H
#define I_MEDICAL_RECORD_DAO_H

#include <vector>
#include <string>
#include <optional>
#include "core/models/MedicalRecord.h"

class IMedicalRecordDAO {
public:
    virtual ~IMedicalRecordDAO() = default;

    virtual std::vector<MedicalRecord> getAll() = 0;
    virtual std::optional<MedicalRecord> getById(const std::string& id) = 0;
    virtual std::vector<MedicalRecord> getByPatientId(const std::string& patientId) = 0;
    virtual bool add(const MedicalRecord& record) = 0;
    virtual bool update(const MedicalRecord& record) = 0;
    virtual bool remove(const std::string& id) = 0;
};

#endif // I_MEDICAL_RECORD_DAO_H
