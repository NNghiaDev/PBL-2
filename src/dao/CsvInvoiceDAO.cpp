#include "dao/CsvInvoiceDAO.h"
#include "dao/CsvHelper.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

CsvInvoiceDAO::CsvInvoiceDAO(const std::string& filePath) : filePath(filePath) {
    ensureFileExists();
}

void CsvInvoiceDAO::ensureFileExists() {
    fs::path p(filePath);
    if (p.has_parent_path() && !fs::exists(p.parent_path())) {
        fs::create_directories(p.parent_path());
    }

    if (!fs::exists(p)) {
        std::ofstream out(filePath);
        if (out.is_open()) {
            out << "InvoiceId,RecordId,PatientId,PaymentDate,ConsultationFee,ServiceFee,MedicineFee,DiscountRatio,TotalAmount,IsPaid\n";
            // Sample invoice: BHYT tra 80% (discountRatio 0.8), benh nhan tra 20%
            out << "HD001,BA001,BN001,30/10/2026 10:15,150000,50000,64000,0.8,52800,1\n";
            out.close();
        }
    }
}

std::vector<Invoice> CsvInvoiceDAO::getAll() {
    std::vector<Invoice> list;
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
            double consFee = 0.0, srvFee = 0.0, medFee = 0.0, discount = 0.0;
            bool isPaid = false;

            try { consFee = std::stod(cols[4]); } catch (...) {}
            try { srvFee = std::stod(cols[5]); } catch (...) {}
            try { medFee = std::stod(cols[6]); } catch (...) {}
            try { discount = std::stod(cols[7]); } catch (...) {}
            try { isPaid = (cols[9] == "1" || cols[9] == "true" || cols[9] == "TRUE"); } catch (...) {}

            Invoice inv(cols[0], cols[1], cols[2], cols[3],
                        consFee, srvFee, medFee, discount, isPaid);
            list.push_back(inv);
        }
    }
    return list;
}

std::optional<Invoice> CsvInvoiceDAO::getById(const std::string& id) {
    auto list = getAll();
    for (const auto& inv : list) {
        if (inv.getInvoiceId() == id) {
            return inv;
        }
    }
    return std::nullopt;
}

std::vector<Invoice> CsvInvoiceDAO::getByPatientId(const std::string& patientId) {
    std::vector<Invoice> res;
    auto list = getAll();
    for (const auto& inv : list) {
        if (inv.getPatientId() == patientId) {
            res.push_back(inv);
        }
    }
    return res;
}

bool CsvInvoiceDAO::add(const Invoice& invoice) {
    auto list = getAll();
    for (const auto& inv : list) {
        if (inv.getInvoiceId() == invoice.getInvoiceId()) {
            return false;
        }
    }
    list.push_back(invoice);

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "InvoiceId,RecordId,PatientId,PaymentDate,ConsultationFee,ServiceFee,MedicineFee,DiscountRatio,TotalAmount,IsPaid\n";
    for (const auto& inv : list) {
        out << CsvHelper::escapeCsvField(inv.getInvoiceId()) << ","
            << CsvHelper::escapeCsvField(inv.getRecordId()) << ","
            << CsvHelper::escapeCsvField(inv.getPatientId()) << ","
            << CsvHelper::escapeCsvField(inv.getPaymentDate()) << ","
            << inv.getConsultationFee() << ","
            << inv.getServiceFee() << ","
            << inv.getMedicineFee() << ","
            << inv.getDiscountRatio() << ","
            << inv.getTotalAmount() << ","
            << (inv.getIsPaid() ? "1" : "0") << "\n";
    }
    return true;
}

bool CsvInvoiceDAO::update(const Invoice& invoice) {
    auto list = getAll();
    bool found = false;
    for (auto& inv : list) {
        if (inv.getInvoiceId() == invoice.getInvoiceId()) {
            inv = invoice;
            found = true;
            break;
        }
    }
    if (!found) return false;

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "InvoiceId,RecordId,PatientId,PaymentDate,ConsultationFee,ServiceFee,MedicineFee,DiscountRatio,TotalAmount,IsPaid\n";
    for (const auto& inv : list) {
        out << CsvHelper::escapeCsvField(inv.getInvoiceId()) << ","
            << CsvHelper::escapeCsvField(inv.getRecordId()) << ","
            << CsvHelper::escapeCsvField(inv.getPatientId()) << ","
            << CsvHelper::escapeCsvField(inv.getPaymentDate()) << ","
            << inv.getConsultationFee() << ","
            << inv.getServiceFee() << ","
            << inv.getMedicineFee() << ","
            << inv.getDiscountRatio() << ","
            << inv.getTotalAmount() << ","
            << (inv.getIsPaid() ? "1" : "0") << "\n";
    }
    return true;
}

bool CsvInvoiceDAO::remove(const std::string& id) {
    auto list = getAll();
    auto it = std::remove_if(list.begin(), list.end(), [&](const Invoice& inv) {
        return inv.getInvoiceId() == id;
    });
    if (it == list.end()) return false;

    list.erase(it, list.end());

    std::ofstream out(filePath, std::ios::trunc);
    if (!out.is_open()) return false;

    out << "InvoiceId,RecordId,PatientId,PaymentDate,ConsultationFee,ServiceFee,MedicineFee,DiscountRatio,TotalAmount,IsPaid\n";
    for (const auto& inv : list) {
        out << CsvHelper::escapeCsvField(inv.getInvoiceId()) << ","
            << CsvHelper::escapeCsvField(inv.getRecordId()) << ","
            << CsvHelper::escapeCsvField(inv.getPatientId()) << ","
            << CsvHelper::escapeCsvField(inv.getPaymentDate()) << ","
            << inv.getConsultationFee() << ","
            << inv.getServiceFee() << ","
            << inv.getMedicineFee() << ","
            << inv.getDiscountRatio() << ","
            << inv.getTotalAmount() << ","
            << (inv.getIsPaid() ? "1" : "0") << "\n";
    }
    return true;
}
