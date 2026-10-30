#ifndef CSV_PATIENT_DAO_H
#define CSV_PATIENT_DAO_H

#include "dao/IPatientDAO.h"
#include <string>

class CsvPatientDAO : public IPatientDAO {
private:
    std::string filePath;
    void ensureFileExists();

public:
    explicit CsvPatientDAO(const std::string& filePath = "data/patients.csv");

    std::vector<Patient> getAll() override;
    std::optional<Patient> getById(const std::string& id) override;
    bool add(const Patient& patient) override;
    bool update(const Patient& patient) override;
    bool remove(const std::string& id) override;
    std::vector<Patient> searchByName(const std::string& keyword) override;
};

#endif // CSV_PATIENT_DAO_H
