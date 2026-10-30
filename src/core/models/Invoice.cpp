#include "core/models/Invoice.h"

Invoice::Invoice()
    : invoiceId(""), recordId(""), patientId(""), paymentDate(""),
      consultationFee(0.0), serviceFee(0.0), medicineFee(0.0),
      discountRatio(0.0), totalAmount(0.0), isPaid(false) {}

Invoice::Invoice(const std::string& invoiceId,
                 const std::string& recordId,
                 const std::string& patientId,
                 const std::string& paymentDate,
                 double consultationFee,
                 double serviceFee,
                 double medicineFee,
                 double discountRatio,
                 bool isPaid)
    : invoiceId(invoiceId), recordId(recordId), patientId(patientId),
      paymentDate(paymentDate), consultationFee(consultationFee),
      serviceFee(serviceFee), medicineFee(medicineFee),
      discountRatio(discountRatio), isPaid(isPaid) {
    calculateTotal();
}

std::string Invoice::getInvoiceId() const { return invoiceId; }
void Invoice::setInvoiceId(const std::string& id) { this->invoiceId = id; }

std::string Invoice::getRecordId() const { return recordId; }
void Invoice::setRecordId(const std::string& id) { this->recordId = id; }

std::string Invoice::getPatientId() const { return patientId; }
void Invoice::setPatientId(const std::string& id) { this->patientId = id; }

std::string Invoice::getPaymentDate() const { return paymentDate; }
void Invoice::setPaymentDate(const std::string& date) { this->paymentDate = date; }

double Invoice::getConsultationFee() const { return consultationFee; }
void Invoice::setConsultationFee(double fee) {
    this->consultationFee = fee;
    calculateTotal();
}

double Invoice::getServiceFee() const { return serviceFee; }
void Invoice::setServiceFee(double fee) {
    this->serviceFee = fee;
    calculateTotal();
}

double Invoice::getMedicineFee() const { return medicineFee; }
void Invoice::setMedicineFee(double fee) {
    this->medicineFee = fee;
    calculateTotal();
}

double Invoice::getDiscountRatio() const { return discountRatio; }
void Invoice::setDiscountRatio(double ratio) {
    this->discountRatio = ratio;
    calculateTotal();
}

double Invoice::getTotalAmount() const { return totalAmount; }

void Invoice::calculateTotal() {
    double gross = consultationFee + serviceFee + medicineFee;
    double covered = gross * discountRatio;
    totalAmount = gross - covered;
    if (totalAmount < 0.0) totalAmount = 0.0;
}

bool Invoice::getIsPaid() const { return isPaid; }
void Invoice::setIsPaid(bool paid) { this->isPaid = paid; }
