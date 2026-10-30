#ifndef PRESCRIPTION_DETAIL_H
#define PRESCRIPTION_DETAIL_H

#include <string>

class PrescriptionDetail {
private:
    std::string medicineId;
    std::string medicineName;
    int quantity;
    double unitPrice;
    std::string dosage; // Vi du: 2 vien/ngay, sang 1 toi 1

public:
    PrescriptionDetail()
        : medicineId(""), medicineName(""), quantity(0), unitPrice(0.0), dosage("") {}

    PrescriptionDetail(const std::string& medicineId,
                       const std::string& medicineName,
                       int quantity,
                       double unitPrice,
                       const std::string& dosage)
        : medicineId(medicineId), medicineName(medicineName),
          quantity(quantity), unitPrice(unitPrice), dosage(dosage) {}

    std::string getMedicineId() const { return medicineId; }
    void setMedicineId(const std::string& id) { medicineId = id; }

    std::string getMedicineName() const { return medicineName; }
    void setMedicineName(const std::string& name) { medicineName = name; }

    int getQuantity() const { return quantity; }
    void setQuantity(int qty) { quantity = qty; }

    double getUnitPrice() const { return unitPrice; }
    void setUnitPrice(double price) { unitPrice = price; }

    std::string getDosage() const { return dosage; }
    void setDosage(const std::string& d) { dosage = d; }

    double getSubTotal() const {
        return quantity * unitPrice;
    }
};

#endif // PRESCRIPTION_DETAIL_H
