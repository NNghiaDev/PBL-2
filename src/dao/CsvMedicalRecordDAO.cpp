#include "dao/CsvMedicalRecordDAO.h"
#include "dao/CsvHelper.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

CsvMedicalRecordDAO::CsvMedicalRecordDAO(const std::string& filePath) : filePath(filePath) {
    ensureFileExists();
}

void CsvMedicalRecordDAO::ensureFileExists() {
    fs::path p(filePath);
    if (p.has_parent_path() && !fs::exists(p.parent_path())) {
        fs::create_directories(p.parent_path());
    }

    if (!fs::exists(p)) {
        std::ofstream out(filePath);
        if (out.is_open()) {
            out << "RecordId,PatientId,DoctorId,ExamDate,Symptoms,Diagnosis,ConsultationFee,ServiceFee,Prescriptions\n";
            // Insert sample medical record
            out << "BA001,BN001,BS001,30/10/2026 09:30,Sot nhe dau dau,Viem hong cap,150000,50000,TH001|Paracetamol 500mg|10|1500|2 vien moi ngay;TH002|Amoxicillin 500mg|14|3500|Sang 1 vien toi 1 vien\n";
            out.close();
        }
    }
}

std::string CsvMedicalRecordDAO::serializePrescriptions(const std::vector<PrescriptionDetail>& list) {
    std::string res;
    for (size_t i = 0; i < list.size(); ++i) {
        const auto& p = list[i];
        res += p.getMedicineId() + "|" + p.getMedicineName() + "|" +
               std::to_string(p.getQuantity()) + "|" +
               std::to_string(p.getUnitPrice()) + "|" +
               p.getDosage();
        if (i + 1 < list.size()) {
            res += ";";
        }
    }
    return res;
}

std::vector<PrescriptionDetail> CsvMedicalRecordDAO::deserializePrescriptions(const std::string& str) {
    std::vector<PrescriptionDetail> list;
    if (str.empty()) return list;

    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, ';')) {
        if (item.empty()) continue;
        std::stringstream itemSs(item);
        std::string part;
        std::vector<std::string> parts;
        while (std::getline(itemSs, part, '|')) {
            parts.push_back(part);
        }
        if (parts.size() >= 5) {
            int qty = 0;
            double price = 0.0;
            try { qty = std::stoi(parts[2]); } catch (...) {}
            try { price = std::stod(parts[3]); } catch (...) {}

            list.emplace_back(parts[0], parts[1], qty, price, parts[4]);
        }
    }
    return list;
}

std::vector<MedicalRecord> CsvMedicalRecordDAO::getAll() {
    std::vector<MedicalRecord> list;
    std::ifstream in(filePath);
    if (!in.is_open()) return list;

    std::string line;
    bool isHeader = true;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        if (isHeader) {
            isHeader = false;
            continue;
        }

        auto cols = CsvHelper::parseCsvLine(line);
        if (cols.size() >= 8) {
            double consFee = 0.0;
            double srvFee = 0.0;
            try { consFee = std::stod(cols[6]); } catch (...) {}
            try { srvFee = std::stod(cols[7]); } catch (...) {}

            MedicalRecord rec(cols[0], cols[1], cols[2], cols[3], cols[4], cols[5], consFee, srvFee);
            if (cols.size() >= 9) {
                auto prescs = deserializePrescriptions(cols[8]);
                for (const auto& p : prescs) {
                    rec.addPrescription(p);
                }
            }
            list.push_back(rec);
        }
    }
    return list;
}

std::optional<MedicalRecord> CsvMedicalRecordDAO::getById(const std::string& id) {
    auto list = getAll();
    for (const auto& r : list) {
        if (r.getRecordId() == id) {
            return r;
        }
    }
    return std::nullopt;
}

std::vector<MedicalRecord> CsvMedicalRecordDAO::getByPatientId(const std::string& patientId) {
    std::vector<MedicalRecord> res;
    auto list = getAll();
    for (const auto& r : list) {
        if (r.getPatientId() == patientId) {
            res.push_back(r);
        }
    }
    return res;
}

bool CsvMedicalRecordDAO::add(const MedicalRecord& record) {
    auto list = getAll();
    for (const auto& r : list) {
        if (r.getRecordId() == record.getRecordId()) {
            return false;
        }
    }
    list.push_back(record);

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "RecordId,PatientId,DoctorId,ExamDate,Symptoms,Diagnosis,ConsultationFee,ServiceFee,Prescriptions\n";
    for (const auto& r : list) {
        out << CsvHelper::escapeCsvField(r.getRecordId()) << ","
            << CsvHelper::escapeCsvField(r.getPatientId()) << ","
            << CsvHelper::escapeCsvField(r.getDoctorId()) << ","
            << CsvHelper::escapeCsvField(r.getExamDate()) << ","
            << CsvHelper::escapeCsvField(r.getSymptoms()) << ","
            << CsvHelper::escapeCsvField(r.getDiagnosis()) << ","
            << r.getConsultationFee() << ","
            << r.getServiceFee() << ","
            << CsvHelper::escapeCsvField(serializePrescriptions(r.getPrescriptions())) << "\n";
    }
    return true;
}

bool CsvMedicalRecordDAO::update(const MedicalRecord& record) {
    auto list = getAll();
    bool found = false;
    for (auto& r : list) {
        if (r.getRecordId() == record.getRecordId()) {
            r = record;
            found = true;
            break;
        }
    }
    if (!found) return false;

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "RecordId,PatientId,DoctorId,ExamDate,Symptoms,Diagnosis,ConsultationFee,ServiceFee,Prescriptions\n";
    for (const auto& r : list) {
        out << CsvHelper::escapeCsvField(r.getRecordId()) << ","
            << CsvHelper::escapeCsvField(r.getPatientId()) << ","
            << CsvHelper::escapeCsvField(r.getDoctorId()) << ","
            << CsvHelper::escapeCsvField(r.getExamDate()) << ","
            << CsvHelper::escapeCsvField(r.getSymptoms()) << ","
            << CsvHelper::escapeCsvField(r.getDiagnosis()) << ","
            << r.getConsultationFee() << ","
            << r.getServiceFee() << ","
            << CsvHelper::escapeCsvField(serializePrescriptions(r.getPrescriptions())) << "\n";
    }
    return true;
}

bool CsvMedicalRecordDAO::remove(const std::string& id) {
    auto list = getAll();
    auto it = std::remove_if(list.begin(), list.end(), [&](const MedicalRecord& r) {
        return r.getRecordId() == id;
    });
    if (it == list.end()) return false;

    list.erase(it, list.end());

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "RecordId,PatientId,DoctorId,ExamDate,Symptoms,Diagnosis,ConsultationFee,ServiceFee,Prescriptions\n";
    for (const auto& r : list) {
        out << CsvHelper::escapeCsvField(r.getRecordId()) << ","
            << CsvHelper::escapeCsvField(r.getPatientId()) << ","
            << CsvHelper::escapeCsvField(r.getDoctorId()) << ","
            << CsvHelper::escapeCsvField(r.getExamDate()) << ","
            << CsvHelper::escapeCsvField(r.getSymptoms()) << ","
            << CsvHelper::escapeCsvField(r.getDiagnosis()) << ","
            << r.getConsultationFee() << ","
            << r.getServiceFee() << ","
            << CsvHelper::escapeCsvField(serializePrescriptions(r.getPrescriptions())) << "\n";
    }
    return true;
}
