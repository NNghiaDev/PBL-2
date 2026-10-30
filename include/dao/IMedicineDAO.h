#ifndef I_MEDICINE_DAO_H
#define I_MEDICINE_DAO_H

#include <vector>
#include <string>
#include <optional>
#include "core/models/Medicine.h"

class IMedicineDAO {
public:
    virtual ~IMedicineDAO() = default;

    virtual std::vector<Medicine> getAll() = 0;
    virtual std::optional<Medicine> getById(const std::string& id) = 0;
    virtual bool add(const Medicine& medicine) = 0;
    virtual bool update(const Medicine& medicine) = 0;
    virtual bool remove(const std::string& id) = 0;
    virtual std::vector<Medicine> searchByName(const std::string& keyword) = 0;
    virtual bool updateStock(const std::string& id, int newQuantity) = 0;
};

#endif // I_MEDICINE_DAO_H
