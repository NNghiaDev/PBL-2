#ifndef I_INVOICE_DAO_H
#define I_INVOICE_DAO_H

#include <vector>
#include <string>
#include <optional>
#include "core/models/Invoice.h"

class IInvoiceDAO {
public:
    virtual ~IInvoiceDAO() = default;

    virtual std::vector<Invoice> getAll() = 0;
    virtual std::optional<Invoice> getById(const std::string& id) = 0;
    virtual std::vector<Invoice> getByPatientId(const std::string& patientId) = 0;
    virtual bool add(const Invoice& invoice) = 0;
    virtual bool update(const Invoice& invoice) = 0;
    virtual bool remove(const std::string& id) = 0;
};

#endif // I_INVOICE_DAO_H
