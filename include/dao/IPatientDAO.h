#ifndef I_PATIENT_DAO_H
#define I_PATIENT_DAO_H

#include <vector>
#include <string>
#include <optional>
#include "core/models/Patient.h"

class IPatientDAO {
public:
    virtual ~IPatientDAO() = default;

    virtual std::vector<Patient> getAll() = 0;
    virtual std::optional<Patient> getById(const std::string& id) = 0;
    virtual bool add(const Patient& patient) = 0;
    virtual bool update(const Patient& patient) = 0;
    virtual bool remove(const std::string& id) = 0;
    virtual std::vector<Patient> searchByName(const std::string& keyword) = 0;
};

#endif // I_PATIENT_DAO_H
