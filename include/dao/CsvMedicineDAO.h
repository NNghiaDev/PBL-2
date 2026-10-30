#ifndef CSV_MEDICINE_DAO_H
#define CSV_MEDICINE_DAO_H

#include "dao/IMedicineDAO.h"
#include <string>

class CsvMedicineDAO : public IMedicineDAO {
private:
    std::string filePath;
    void ensureFileExists();

public:
    explicit CsvMedicineDAO(const std::string& filePath = "data/medicines.csv");

    std::vector<Medicine> getAll() override;
    std::optional<Medicine> getById(const std::string& id) override;
    bool add(const Medicine& medicine) override;
    bool update(const Medicine& medicine) override;
    bool remove(const std::string& id) override;
    std::vector<Medicine> searchByName(const std::string& keyword) override;
    bool updateStock(const std::string& id, int newQuantity) override;
};

#endif // CSV_MEDICINE_DAO_H
