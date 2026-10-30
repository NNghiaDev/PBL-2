#ifndef PHARMACY_SERVICE_H
#define PHARMACY_SERVICE_H

#include "dao/IMedicineDAO.h"
#include <memory>
#include <vector>
#include <string>

class PharmacyService {
private:
    std::shared_ptr<IMedicineDAO> medicineDao;

public:
    explicit PharmacyService(std::shared_ptr<IMedicineDAO> dao);

    std::vector<Medicine> getAllMedicines();
    std::optional<Medicine> findMedicineById(const std::string& id);
    bool addMedicine(const Medicine& medicine);
    bool updateMedicine(const Medicine& medicine);
    bool removeMedicine(const std::string& id);
    std::vector<Medicine> searchMedicines(const std::string& keyword);

    // Stock management
    bool dispenseMedicine(const std::string& id, int quantity);
    bool restockMedicine(const std::string& id, int quantity);

    // Tu dong sinh ma thuoc ke tiep (TH001, TH002, ...)
    std::string generateNextMedicineId();
};

#endif // PHARMACY_SERVICE_H
