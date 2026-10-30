#ifndef I_DOCTOR_DAO_H
#define I_DOCTOR_DAO_H

#include <vector>
#include <string>
#include <optional>
#include "core/models/Doctor.h"

class IDoctorDAO {
public:
    virtual ~IDoctorDAO() = default;

    virtual std::vector<Doctor> getAll() = 0;
    virtual std::optional<Doctor> getById(const std::string& id) = 0;
    virtual bool add(const Doctor& doctor) = 0;
    virtual bool update(const Doctor& doctor) = 0;
    virtual bool remove(const std::string& id) = 0;
    virtual std::vector<Doctor> getBySpecialty(const std::string& specialty) = 0;
};

#endif // I_DOCTOR_DAO_H
