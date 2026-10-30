#ifndef BILLING_SERVICE_H
#define BILLING_SERVICE_H

#include "dao/IInvoiceDAO.h"
#include "core/models/MedicalRecord.h"
#include "core/models/Patient.h"
#include <memory>
#include <vector>
#include <string>

class BillingService {
private:
    std::shared_ptr<IInvoiceDAO> invoiceDao;

public:
    explicit BillingService(std::shared_ptr<IInvoiceDAO> dao);

    std::vector<Invoice> getAllInvoices();
    std::optional<Invoice> findInvoiceById(const std::string& id);
    std::vector<Invoice> getInvoicesByPatient(const std::string& patientId);

    // Business flow: Generate invoice from MedicalRecord and Patient BHYT status
    Invoice generateInvoice(const std::string& invoiceId,
                            const MedicalRecord& record,
                            const Patient& patient,
                            const std::string& paymentDate);

    bool saveInvoice(const Invoice& invoice);
    bool processPayment(const std::string& invoiceId);

    // Financial reporting
    double calculateTotalRevenue() const;
    double calculatePendingRevenue() const;
};

#endif // BILLING_SERVICE_H
