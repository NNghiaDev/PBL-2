#ifndef INVOICE_H
#define INVOICE_H

#include <string>

class Invoice {
private:
    std::string invoiceId;
    std::string recordId;
    std::string patientId;
    std::string paymentDate;
    double consultationFee;
    double serviceFee;
    double medicineFee;
    double discountRatio; // Ti le BHYT chi tra: vd 0.8 (80%) -> benh nhan tra 20%
    double totalAmount;   // So tien benh nhan phai thanh toan thuc te
    bool isPaid;

public:
    Invoice();
    Invoice(const std::string& invoiceId,
            const std::string& recordId,
            const std::string& patientId,
            const std::string& paymentDate,
            double consultationFee,
            double serviceFee,
            double medicineFee,
            double discountRatio = 0.0,
            bool isPaid = false);

    std::string getInvoiceId() const;
    void setInvoiceId(const std::string& id);

    std::string getRecordId() const;
    void setRecordId(const std::string& id);

    std::string getPatientId() const;
    void setPatientId(const std::string& id);

    std::string getPaymentDate() const;
    void setPaymentDate(const std::string& date);

    double getConsultationFee() const;
    void setConsultationFee(double fee);

    double getServiceFee() const;
    void setServiceFee(double fee);

    double getMedicineFee() const;
    void setMedicineFee(double fee);

    double getDiscountRatio() const;
    void setDiscountRatio(double ratio);

    double getTotalAmount() const;
    void calculateTotal();

    bool getIsPaid() const;
    void setIsPaid(bool paid);
};

#endif // INVOICE_H
