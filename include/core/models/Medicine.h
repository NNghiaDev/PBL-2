#ifndef MEDICINE_H
#define MEDICINE_H

#include <string>

class Medicine {
private:
    std::string id;
    std::string name;
    std::string unit;          // Vien, Vi, Hop, Chai, Goi
    double price;              // Don gia VND
    int stockQuantity;         // So luong ton kho
    std::string usageNote;      // Cach dung (uong sau an,...)

public:
    Medicine();
    Medicine(const std::string& id,
             const std::string& name,
             const std::string& unit,
             double price,
             int stockQuantity,
             const std::string& usageNote);

    std::string getId() const;
    void setId(const std::string& id);

    std::string getName() const;
    void setName(const std::string& name);

    std::string getUnit() const;
    void setUnit(const std::string& unit);

    double getPrice() const;
    void setPrice(double price);

    int getStockQuantity() const;
    void setStockQuantity(int quantity);

    std::string getUsageNote() const;
    void setUsageNote(const std::string& note);

    bool deductStock(int quantity);
    void addStock(int quantity);
};

#endif // MEDICINE_H
