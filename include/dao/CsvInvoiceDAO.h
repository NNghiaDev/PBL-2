#ifndef CSV_INVOICE_DAO_H
#define CSV_INVOICE_DAO_H

#include "dao/IInvoiceDAO.h"
#include <string>

class CsvInvoiceDAO : public IInvoiceDAO {
private:
    std::string filePath;
    void ensureFileExists();

public:
    explicit CsvInvoiceDAO(const std::string& filePath = "data/invoices.csv");

    std::vector<Invoice> getAll() override;
    std::optional<Invoice> getById(const std::string& id) override;
    std::vector<Invoice> getByPatientId(const std::string& patientId) override;
    bool add(const Invoice& invoice) override;
    bool update(const Invoice& invoice) override;
    bool remove(const std::string& id) override;
};

#endif // CSV_INVOICE_DAO_H
