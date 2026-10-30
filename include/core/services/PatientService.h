#ifndef PATIENT_SERVICE_H
#define PATIENT_SERVICE_H

#include "dao/IPatientDAO.h"
#include "core/dsa/Algorithms.hpp"
#include <memory>
#include <vector>
#include <string>

class PatientService {
private:
    std::shared_ptr<IPatientDAO> patientDao;

public:
    explicit PatientService(std::shared_ptr<IPatientDAO> dao);

    std::vector<Patient> getAllPatients();
    std::optional<Patient> findPatientById(const std::string& id);
    bool registerPatient(const Patient& patient);
    bool updatePatientInfo(const Patient& patient);
    bool removePatient(const std::string& id);
    std::vector<Patient> searchPatients(const std::string& keyword);

    // DSA Integration: Sort patients by FullName using QuickSort
    std::vector<Patient> getPatientsSortedByName();

    // DSA Integration: Sort patients by ID and lookup using BinarySearch
    std::optional<Patient> searchPatientByIdBinary(const std::string& id);

    // Tu dong sinh ma benh nhan ke tiep (BN001, BN002, ...)
    std::string generateNextPatientId();
};

#endif // PATIENT_SERVICE_H
