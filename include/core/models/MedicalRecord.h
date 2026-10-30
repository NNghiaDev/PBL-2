#ifndef MEDICAL_RECORD_H
#define MEDICAL_RECORD_H

#include <string>
#include <vector>
#include "core/models/PrescriptionDetail.h"

class MedicalRecord {
private:
    std::string recordId;
    std::string patientId;
    std::string doctorId;
    std::string examDate;          // DD/MM/YYYY HH:mm
    std::string symptoms;          // Trieu chung
    std::string diagnosis;         // Chuan doan benh
    std::vector<PrescriptionDetail> prescriptions;
    double serviceFee;             // Phi xet nghiem / chup chieu
    double consultationFee;        // Phi kham ban dau

public:
    MedicalRecord();
    MedicalRecord(const std::string& recordId,
                  const std::string& patientId,
                  const std::string& doctorId,
                  const std::string& examDate,
                  const std::string& symptoms,
                  const std::string& diagnosis,
                  double consultationFee = 150000.0,
                  double serviceFee = 0.0);

    std::string getRecordId() const;
    void setRecordId(const std::string& id);

    std::string getPatientId() const;
    void setPatientId(const std::string& id);

    std::string getDoctorId() const;
    void setDoctorId(const std::string& id);

    std::string getExamDate() const;
    void setExamDate(const std::string& date);

    std::string getSymptoms() const;
    void setSymptoms(const std::string& symptoms);

    std::string getDiagnosis() const;
    void setDiagnosis(const std::string& diagnosis);

    double getConsultationFee() const;
    void setConsultationFee(double fee);

    double getServiceFee() const;
    void setServiceFee(double fee);

    const std::vector<PrescriptionDetail>& getPrescriptions() const;
    void addPrescription(const PrescriptionDetail& item);
    void clearPrescriptions();

    double calculatePrescriptionFee() const;
    double calculateGrossTotal() const;
};

#endif // MEDICAL_RECORD_H
