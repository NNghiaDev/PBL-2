#include "dao/CsvMedicineDAO.h"
#include "dao/CsvHelper.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

CsvMedicineDAO::CsvMedicineDAO(const std::string& filePath) : filePath(filePath) {
    ensureFileExists();
}

void CsvMedicineDAO::ensureFileExists() {
    fs::path p(filePath);
    if (p.has_parent_path() && !fs::exists(p.parent_path())) {
        fs::create_directories(p.parent_path());
    }

    if (!fs::exists(p)) {
        std::ofstream out(filePath);
        if (out.is_open()) {
            out << "ID,Name,Unit,Price,StockQuantity,UsageNote\n";
            // Insert seed medicines
            out << "TH001,Paracetamol 500mg,Vien,1500,500,Uong sau khi an no\n";
            out << "TH002,Amoxicillin 500mg,Vien,3500,250,Khang sinh - uong du lieu 5-7 ngay\n";
            out << "TH003,Panadol Extra,Vi (10 vien),18000,100,Giam dau ha sot nhanh\n";
            out << "TH004,Berberin 50mg,Lo (100 vien),45000,80,Dieu tri roi loan tieu hoa\n";
            out << "TH005,Siro Ho Prospan,Chai,85000,60,Uong 5ml/lan ngay 3 lan\n";
            out.close();
        }
    }
}

std::vector<Medicine> CsvMedicineDAO::getAll() {
    std::vector<Medicine> list;
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
        if (cols.size() >= 6) {
            double price = 0.0;
            int stock = 0;
            try { price = std::stod(cols[3]); } catch (...) {}
            try { stock = std::stoi(cols[4]); } catch (...) {}

            Medicine m(cols[0], cols[1], cols[2], price, stock, cols[5]);
            list.push_back(m);
        }
    }
    return list;
}

std::optional<Medicine> CsvMedicineDAO::getById(const std::string& id) {
    auto list = getAll();
    for (const auto& m : list) {
        if (m.getId() == id) {
            return m;
        }
    }
    return std::nullopt;
}

bool CsvMedicineDAO::add(const Medicine& medicine) {
    auto list = getAll();
    for (const auto& m : list) {
        if (m.getId() == medicine.getId()) {
            return false;
        }
    }
    list.push_back(medicine);

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "ID,Name,Unit,Price,StockQuantity,UsageNote\n";
    for (const auto& m : list) {
        out << CsvHelper::escapeCsvField(m.getId()) << ","
            << CsvHelper::escapeCsvField(m.getName()) << ","
            << CsvHelper::escapeCsvField(m.getUnit()) << ","
            << m.getPrice() << ","
            << m.getStockQuantity() << ","
            << CsvHelper::escapeCsvField(m.getUsageNote()) << "\n";
    }
    return true;
}

bool CsvMedicineDAO::update(const Medicine& medicine) {
    auto list = getAll();
    bool found = false;
    for (auto& m : list) {
        if (m.getId() == medicine.getId()) {
            m = medicine;
            found = true;
            break;
        }
    }
    if (!found) return false;

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "ID,Name,Unit,Price,StockQuantity,UsageNote\n";
    for (const auto& m : list) {
        out << CsvHelper::escapeCsvField(m.getId()) << ","
            << CsvHelper::escapeCsvField(m.getName()) << ","
            << CsvHelper::escapeCsvField(m.getUnit()) << ","
            << m.getPrice() << ","
            << m.getStockQuantity() << ","
            << CsvHelper::escapeCsvField(m.getUsageNote()) << "\n";
    }
    return true;
}

bool CsvMedicineDAO::remove(const std::string& id) {
    auto list = getAll();
    auto it = std::remove_if(list.begin(), list.end(), [&](const Medicine& m) {
        return m.getId() == id;
    });
    if (it == list.end()) return false;

    list.erase(it, list.end());

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "ID,Name,Unit,Price,StockQuantity,UsageNote\n";
    for (const auto& m : list) {
        out << CsvHelper::escapeCsvField(m.getId()) << ","
            << CsvHelper::escapeCsvField(m.getName()) << ","
            << CsvHelper::escapeCsvField(m.getUnit()) << ","
            << m.getPrice() << ","
            << m.getStockQuantity() << ","
            << CsvHelper::escapeCsvField(m.getUsageNote()) << "\n";
    }
    return true;
}

std::vector<Medicine> CsvMedicineDAO::searchByName(const std::string& keyword) {
    std::vector<Medicine> res;
    auto list = getAll();
    std::string lowerKey = keyword;
    std::transform(lowerKey.begin(), lowerKey.end(), lowerKey.begin(), ::tolower);

    for (const auto& m : list) {
        std::string name = m.getName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (name.find(lowerKey) != std::string::npos || m.getId().find(keyword) != std::string::npos) {
            res.push_back(m);
        }
    }
    return res;
}

bool CsvMedicineDAO::updateStock(const std::string& id, int newQuantity) {
    auto opt = getById(id);
    if (!opt.has_value()) return false;

    Medicine m = opt.value();
    m.setStockQuantity(newQuantity);
    return update(m);
}
