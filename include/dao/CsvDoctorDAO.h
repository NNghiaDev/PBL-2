#ifndef CSV_DOCTOR_DAO_H
#define CSV_DOCTOR_DAO_H

#include "dao/IDoctorDAO.h"
#include <string>

class CsvDoctorDAO : public IDoctorDAO {
private:
    std::string filePath;
    void ensureFileExists();

public:
    explicit CsvDoctorDAO(const std::string& filePath = "data/doctors.csv");

    std::vector<Doctor> getAll() override;
    std::optional<Doctor> getById(const std::string& id) override;
    bool add(const Doctor& doctor) override;
    bool update(const Doctor& doctor) override;
    bool remove(const std::string& id) override;
    std::vector<Doctor> getBySpecialty(const std::string& specialty) override;
};

#endif // CSV_DOCTOR_DAO_H
