#include "core/services/PharmacyService.h"
#include <sstream>
#include <iomanip>
#include <cctype>

PharmacyService::PharmacyService(std::shared_ptr<IMedicineDAO> dao) : medicineDao(dao) {}

std::vector<Medicine> PharmacyService::getAllMedicines() {
    return medicineDao->getAll();
}

std::optional<Medicine> PharmacyService::findMedicineById(const std::string& id) {
    return medicineDao->getById(id);
}

bool PharmacyService::addMedicine(const Medicine& medicine) {
    if (medicine.getId().empty() || medicine.getName().empty() || medicine.getPrice() < 0) {
        return false;
    }
    return medicineDao->add(medicine);
}

bool PharmacyService::updateMedicine(const Medicine& medicine) {
    return medicineDao->update(medicine);
}

bool PharmacyService::removeMedicine(const std::string& id) {
    return medicineDao->remove(id);
}

std::vector<Medicine> PharmacyService::searchMedicines(const std::string& keyword) {
    return medicineDao->searchByName(keyword);
}

bool PharmacyService::dispenseMedicine(const std::string& id, int quantity) {
    auto opt = medicineDao->getById(id);
    if (!opt.has_value()) return false;

    Medicine m = opt.value();
    if (!m.deductStock(quantity)) return false;

    return medicineDao->update(m);
}

bool PharmacyService::restockMedicine(const std::string& id, int quantity) {
    auto opt = medicineDao->getById(id);
    if (!opt.has_value()) return false;

    Medicine m = opt.value();
    m.addStock(quantity);
    return medicineDao->update(m);
}

std::string PharmacyService::generateNextMedicineId() {
    auto list = medicineDao->getAll();
    int maxId = 0;
    for (const auto& m : list) {
        std::string id = m.getId();
        if (id.rfind("TH", 0) == 0) {
            std::string numStr = "";
            for (size_t i = 2; i < id.length(); ++i) {
                if (std::isdigit(id[i])) {
                    numStr += id[i];
                }
            }
            if (!numStr.empty()) {
                try {
                    int val = std::stoi(numStr);
                    if (val > maxId) maxId = val;
                } catch (...) {}
            }
        }
    }
    std::ostringstream ss;
    ss << "TH" << std::setw(3) << std::setfill('0') << (maxId + 1);
    return ss.str();
}
