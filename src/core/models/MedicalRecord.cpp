#include "core/models/MedicalRecord.h"

MedicalRecord::MedicalRecord()
    : recordId(""), patientId(""), doctorId(""), examDate(""),
      symptoms(""), diagnosis(""), serviceFee(0.0), consultationFee(150000.0) {}

MedicalRecord::MedicalRecord(const std::string& recordId,
                             const std::string& patientId,
                             const std::string& doctorId,
                             const std::string& examDate,
                             const std::string& symptoms,
                             const std::string& diagnosis,
                             double consultationFee,
                             double serviceFee)
    : recordId(recordId), patientId(patientId), doctorId(doctorId),
      examDate(examDate), symptoms(symptoms), diagnosis(diagnosis),
      serviceFee(serviceFee), consultationFee(consultationFee) {}

std::string MedicalRecord::getRecordId() const { return recordId; }
void MedicalRecord::setRecordId(const std::string& id) { this->recordId = id; }

std::string MedicalRecord::getPatientId() const { return patientId; }
void MedicalRecord::setPatientId(const std::string& id) { this->patientId = id; }

std::string MedicalRecord::getDoctorId() const { return doctorId; }
void MedicalRecord::setDoctorId(const std::string& id) { this->doctorId = id; }

std::string MedicalRecord::getExamDate() const { return examDate; }
void MedicalRecord::setExamDate(const std::string& date) { this->examDate = date; }

std::string MedicalRecord::getSymptoms() const { return symptoms; }
void MedicalRecord::setSymptoms(const std::string& symptoms) { this->symptoms = symptoms; }

std::string MedicalRecord::getDiagnosis() const { return diagnosis; }
void MedicalRecord::setDiagnosis(const std::string& diagnosis) { this->diagnosis = diagnosis; }

double MedicalRecord::getConsultationFee() const { return consultationFee; }
void MedicalRecord::setConsultationFee(double fee) { this->consultationFee = fee; }

double MedicalRecord::getServiceFee() const { return serviceFee; }
void MedicalRecord::setServiceFee(double fee) { this->serviceFee = fee; }

const std::vector<PrescriptionDetail>& MedicalRecord::getPrescriptions() const {
    return prescriptions;
}

void MedicalRecord::addPrescription(const PrescriptionDetail& item) {
    prescriptions.push_back(item);
}

void MedicalRecord::clearPrescriptions() {
    prescriptions.clear();
}

double MedicalRecord::calculatePrescriptionFee() const {
    double total = 0.0;
    for (const auto& item : prescriptions) {
        total += item.getSubTotal();
    }
    return total;
}

double MedicalRecord::calculateGrossTotal() const {
    return consultationFee + serviceFee + calculatePrescriptionFee();
}
