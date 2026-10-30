#ifndef DOCTOR_SERVICE_H
#define DOCTOR_SERVICE_H

#include "dao/IDoctorDAO.h"
#include <memory>
#include <vector>
#include <string>

class DoctorService {
private:
    std::shared_ptr<IDoctorDAO> doctorDao;

public:
    explicit DoctorService(std::shared_ptr<IDoctorDAO> dao);

    std::vector<Doctor> getAllDoctors();
    std::optional<Doctor> findDoctorById(const std::string& id);
    bool registerDoctor(const Doctor& doctor);
    bool updateDoctorInfo(const Doctor& doctor);
    bool removeDoctor(const std::string& id);
    std::vector<Doctor> getDoctorsBySpecialty(const std::string& specialty);

    // Tu dong sinh ma bac si ke tiep (BS001, BS002, ...)
    std::string generateNextDoctorId();
};

#endif // DOCTOR_SERVICE_H
