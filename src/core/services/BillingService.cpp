#include "core/services/BillingService.h"

BillingService::BillingService(std::shared_ptr<IInvoiceDAO> dao) : invoiceDao(dao) {}

std::vector<Invoice> BillingService::getAllInvoices() {
    return invoiceDao->getAll();
}

std::optional<Invoice> BillingService::findInvoiceById(const std::string& id) {
    return invoiceDao->getById(id);
}

std::vector<Invoice> BillingService::getInvoicesByPatient(const std::string& patientId) {
    return invoiceDao->getByPatientId(patientId);
}

Invoice BillingService::generateInvoice(const std::string& invoiceId,
                                        const MedicalRecord& record,
                                        const Patient& patient,
                                        const std::string& paymentDate) {
    double consultationFee = record.getConsultationFee();
    double serviceFee = record.getServiceFee();
    double medicineFee = record.calculatePrescriptionFee();

    // Determine BHYT insurance discount ratio
    // If patient has valid BHYT, standard discount is 80% (0.8)
    double discountRatio = 0.0;
    if (!patient.getHealthInsuranceId().empty()) {
        discountRatio = 0.8; // 80% covered by health insurance
    }

    Invoice inv(invoiceId, record.getRecordId(), patient.getId(), paymentDate,
                consultationFee, serviceFee, medicineFee, discountRatio, false);
    return inv;
}

bool BillingService::saveInvoice(const Invoice& invoice) {
    if (invoice.getInvoiceId().empty()) return false;
    return invoiceDao->add(invoice);
}

bool BillingService::processPayment(const std::string& invoiceId) {
    auto opt = invoiceDao->getById(invoiceId);
    if (!opt.has_value()) return false;

    Invoice inv = opt.value();
    inv.setIsPaid(true);
    return invoiceDao->update(inv);
}

double BillingService::calculateTotalRevenue() const {
    double total = 0.0;
    auto list = invoiceDao->getAll();
    for (const auto& inv : list) {
        if (inv.getIsPaid()) {
            total += inv.getTotalAmount();
        }
    }
    return total;
}

double BillingService::calculatePendingRevenue() const {
    double pending = 0.0;
    auto list = invoiceDao->getAll();
    for (const auto& inv : list) {
        if (!inv.getIsPaid()) {
            pending += inv.getTotalAmount();
        }
    }
    return pending;
}
