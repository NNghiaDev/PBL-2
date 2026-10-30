#include "dao/CsvPatientDAO.h"
#include "dao/CsvHelper.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

CsvPatientDAO::CsvPatientDAO(const std::string& filePath) : filePath(filePath) {
    ensureFileExists();
}

void CsvPatientDAO::ensureFileExists() {
    fs::path p(filePath);
    if (p.has_parent_path() && !fs::exists(p.parent_path())) {
        fs::create_directories(p.parent_path());
    }

    if (!fs::exists(p)) {
        std::ofstream out(filePath);
        if (out.is_open()) {
            out << "ID,FullName,DateOfBirth,Gender,Phone,Address,HealthInsuranceId,BloodType,EmergencyContact,PriorityLevel\n";
            // Insert seed data
            out << "BN001,Nguyen Van An,15/05/1985,Nam,0901234567,123 Le Duan Da Nang,DN849201928,O,0912345678,3\n";
            out << "BN002,Tran Thi Binh,20/11/1950,Nu,0987654321,45 Nguyen Thi Minh Khai Da Nang,DN849201999,A,0988888888,2\n";
            out << "BN003,Le Hoang Cuong,02/09/2000,Nam,0935123456,88 Bach Dang Da Nang,DN849202111,B,0935999888,1\n";
            out.close();
        }
    }
}

std::vector<Patient> CsvPatientDAO::getAll() {
    std::vector<Patient> list;
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
        if (cols.size() >= 10) {
            int priority = 3;
            try { priority = std::stoi(cols[9]); } catch (...) {}

            Patient p(cols[0], cols[1], cols[2], cols[3], cols[4],
                      cols[5], cols[6], cols[7], cols[8], priority);
            list.push_back(p);
        }
    }
    return list;
}

std::optional<Patient> CsvPatientDAO::getById(const std::string& id) {
    auto list = getAll();
    for (const auto& p : list) {
        if (p.getId() == id) {
            return p;
        }
    }
    return std::nullopt;
}

bool CsvPatientDAO::add(const Patient& patient) {
    auto list = getAll();
    for (const auto& p : list) {
        if (p.getId() == patient.getId()) {
            return false; // ID already exists
        }
    }
    list.push_back(patient);

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "ID,FullName,DateOfBirth,Gender,Phone,Address,HealthInsuranceId,BloodType,EmergencyContact,PriorityLevel\n";
    for (const auto& p : list) {
        out << CsvHelper::escapeCsvField(p.getId()) << ","
            << CsvHelper::escapeCsvField(p.getFullName()) << ","
            << CsvHelper::escapeCsvField(p.getDateOfBirth()) << ","
            << CsvHelper::escapeCsvField(p.getGender()) << ","
            << CsvHelper::escapeCsvField(p.getPhone()) << ","
            << CsvHelper::escapeCsvField(p.getAddress()) << ","
            << CsvHelper::escapeCsvField(p.getHealthInsuranceId()) << ","
            << CsvHelper::escapeCsvField(p.getBloodType()) << ","
            << CsvHelper::escapeCsvField(p.getEmergencyContact()) << ","
            << p.getPriorityLevel() << "\n";
    }
    return true;
}

bool CsvPatientDAO::update(const Patient& patient) {
    auto list = getAll();
    bool found = false;
    for (auto& p : list) {
        if (p.getId() == patient.getId()) {
            p = patient;
            found = true;
            break;
        }
    }
    if (!found) return false;

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "ID,FullName,DateOfBirth,Gender,Phone,Address,HealthInsuranceId,BloodType,EmergencyContact,PriorityLevel\n";
    for (const auto& p : list) {
        out << CsvHelper::escapeCsvField(p.getId()) << ","
            << CsvHelper::escapeCsvField(p.getFullName()) << ","
            << CsvHelper::escapeCsvField(p.getDateOfBirth()) << ","
            << CsvHelper::escapeCsvField(p.getGender()) << ","
            << CsvHelper::escapeCsvField(p.getPhone()) << ","
            << CsvHelper::escapeCsvField(p.getAddress()) << ","
            << CsvHelper::escapeCsvField(p.getHealthInsuranceId()) << ","
            << CsvHelper::escapeCsvField(p.getBloodType()) << ","
            << CsvHelper::escapeCsvField(p.getEmergencyContact()) << ","
            << p.getPriorityLevel() << "\n";
    }
    return true;
}

bool CsvPatientDAO::remove(const std::string& id) {
    auto list = getAll();
    auto it = std::remove_if(list.begin(), list.end(), [&](const Patient& p) {
        return p.getId() == id;
    });
    if (it == list.end()) return false;

    list.erase(it, list.end());

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "ID,FullName,DateOfBirth,Gender,Phone,Address,HealthInsuranceId,BloodType,EmergencyContact,PriorityLevel\n";
    for (const auto& p : list) {
        out << CsvHelper::escapeCsvField(p.getId()) << ","
            << CsvHelper::escapeCsvField(p.getFullName()) << ","
            << CsvHelper::escapeCsvField(p.getDateOfBirth()) << ","
            << CsvHelper::escapeCsvField(p.getGender()) << ","
            << CsvHelper::escapeCsvField(p.getPhone()) << ","
            << CsvHelper::escapeCsvField(p.getAddress()) << ","
            << CsvHelper::escapeCsvField(p.getHealthInsuranceId()) << ","
            << CsvHelper::escapeCsvField(p.getBloodType()) << ","
            << CsvHelper::escapeCsvField(p.getEmergencyContact()) << ","
            << p.getPriorityLevel() << "\n";
    }
    return true;
}

std::vector<Patient> CsvPatientDAO::searchByName(const std::string& keyword) {
    std::vector<Patient> res;
    auto list = getAll();
    std::string lowerKey = keyword;
    std::transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);

    for (const auto& p : list) {
        std::string name = p.getFullName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (name.find(lowerKey) != std::string::npos || p.getId().find(keyword) != std::string::npos) {
            res.push_back(p);
        }
    }
    return res;
}
