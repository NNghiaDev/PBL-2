#include "dao/CsvDoctorDAO.h"
#include "dao/CsvHelper.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

CsvDoctorDAO::CsvDoctorDAO(const std::string& filePath) : filePath(filePath) {
    ensureFileExists();
}

void CsvDoctorDAO::ensureFileExists() {
    fs::path p(filePath);
    if (p.has_parent_path() && !fs::exists(p.parent_path())) {
        fs::create_directories(p.parent_path());
    }

    if (!fs::exists(p)) {
        std::ofstream out(filePath);
        if (out.is_open()) {
            out << "ID,FullName,DateOfBirth,Gender,Phone,Address,Specialty,LicenseNumber,DepartmentId,YearsOfExperience\n";
            // Insert seed doctors
            out << "BS001,BS.CKII Tran Van Minh,10/03/1975,Nam,0913456789,Hai Chau Da Nang,Noi tong quat,CCHN-00123,KHOA_NOI,20\n";
            out << "BS002,ThS.BS Le Thi Hoa,25/08/1982,Nu,0905123987,Cam Le Da Nang,Nhi khoa,CCHN-00456,KHOA_NHI,14\n";
            out << "BS003,BS.CKI Vo Van Nam,12/12/1988,Nam,0932111222,Son Tra Da Nang,Cap cuu hoi suc,CCHN-00789,KHOA_CAPCUU,10\n";
            out.close();
        }
    }
}

std::vector<Doctor> CsvDoctorDAO::getAll() {
    std::vector<Doctor> list;
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
            int exp = 0;
            try { exp = std::stoi(cols[9]); } catch (...) {}

            Doctor d(cols[0], cols[1], cols[2], cols[3], cols[4],
                     cols[5], cols[6], cols[7], cols[8], exp);
            list.push_back(d);
        }
    }
    return list;
}

std::optional<Doctor> CsvDoctorDAO::getById(const std::string& id) {
    auto list = getAll();
    for (const auto& d : list) {
        if (d.getId() == id) {
            return d;
        }
    }
    return std::nullopt;
}

bool CsvDoctorDAO::add(const Doctor& doctor) {
    auto list = getAll();
    for (const auto& d : list) {
        if (d.getId() == doctor.getId()) {
            return false;
        }
    }
    list.push_back(doctor);

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "ID,FullName,DateOfBirth,Gender,Phone,Address,Specialty,LicenseNumber,DepartmentId,YearsOfExperience\n";
    for (const auto& d : list) {
        out << CsvHelper::escapeCsvField(d.getId()) << ","
            << CsvHelper::escapeCsvField(d.getFullName()) << ","
            << CsvHelper::escapeCsvField(d.getDateOfBirth()) << ","
            << CsvHelper::escapeCsvField(d.getGender()) << ","
            << CsvHelper::escapeCsvField(d.getPhone()) << ","
            << CsvHelper::escapeCsvField(d.getAddress()) << ","
            << CsvHelper::escapeCsvField(d.getSpecialty()) << ","
            << CsvHelper::escapeCsvField(d.getLicenseNumber()) << ","
            << CsvHelper::escapeCsvField(d.getDepartmentId()) << ","
            << d.getYearsOfExperience() << "\n";
    }
    return true;
}

bool CsvDoctorDAO::update(const Doctor& doctor) {
    auto list = getAll();
    bool found = false;
    for (auto& d : list) {
        if (d.getId() == doctor.getId()) {
            d = doctor;
            found = true;
            break;
        }
    }
    if (!found) return false;

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "ID,FullName,DateOfBirth,Gender,Phone,Address,Specialty,LicenseNumber,DepartmentId,YearsOfExperience\n";
    for (const auto& d : list) {
        out << CsvHelper::escapeCsvField(d.getId()) << ","
            << CsvHelper::escapeCsvField(d.getFullName()) << ","
            << CsvHelper::escapeCsvField(d.getDateOfBirth()) << ","
            << CsvHelper::escapeCsvField(d.getGender()) << ","
            << CsvHelper::escapeCsvField(d.getPhone()) << ","
            << CsvHelper::escapeCsvField(d.getAddress()) << ","
            << CsvHelper::escapeCsvField(d.getSpecialty()) << ","
            << CsvHelper::escapeCsvField(d.getLicenseNumber()) << ","
            << CsvHelper::escapeCsvField(d.getDepartmentId()) << ","
            << d.getYearsOfExperience() << "\n";
    }
    return true;
}

bool CsvDoctorDAO::remove(const std::string& id) {
    auto list = getAll();
    auto it = std::remove_if(list.begin(), list.end(), [&](const Doctor& d) {
        return d.getId() == id;
    });
    if (it == list.end()) return false;

    list.erase(it, list.end());

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "ID,FullName,DateOfBirth,Gender,Phone,Address,Specialty,LicenseNumber,DepartmentId,YearsOfExperience\n";
    for (const auto& d : list) {
        out << CsvHelper::escapeCsvField(d.getId()) << ","
            << CsvHelper::escapeCsvField(d.getFullName()) << ","
            << CsvHelper::escapeCsvField(d.getDateOfBirth()) << ","
            << CsvHelper::escapeCsvField(d.getGender()) << ","
            << CsvHelper::escapeCsvField(d.getPhone()) << ","
            << CsvHelper::escapeCsvField(d.getAddress()) << ","
            << CsvHelper::escapeCsvField(d.getSpecialty()) << ","
            << CsvHelper::escapeCsvField(d.getLicenseNumber()) << ","
            << CsvHelper::escapeCsvField(d.getDepartmentId()) << ","
            << d.getYearsOfExperience() << "\n";
    }
    return true;
}

std::vector<Doctor> CsvDoctorDAO::getBySpecialty(const std::string& specialty) {
    std::vector<Doctor> res;
    auto list = getAll();
    for (const auto& d : list) {
        if (d.getSpecialty().find(specialty) != std::string::npos) {
            res.push_back(d);
        }
    }
    return res;
}
