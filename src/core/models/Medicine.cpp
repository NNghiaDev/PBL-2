#include "core/models/Medicine.h"

Medicine::Medicine()
    : id(""), name(""), unit("Vien"), price(0.0), stockQuantity(0), usageNote("") {}

Medicine::Medicine(const std::string& id,
                   const std::string& name,
                   const std::string& unit,
                   double price,
                   int stockQuantity,
                   const std::string& usageNote)
    : id(id), name(name), unit(unit), price(price),
      stockQuantity(stockQuantity), usageNote(usageNote) {}

std::string Medicine::getId() const { return id; }
void Medicine::setId(const std::string& id) { this->id = id; }

std::string Medicine::getName() const { return name; }
void Medicine::setName(const std::string& name) { this->name = name; }

std::string Medicine::getUnit() const { return unit; }
void Medicine::setUnit(const std::string& unit) { this->unit = unit; }

double Medicine::getPrice() const { return price; }
void Medicine::setPrice(double price) { this->price = price; }

int Medicine::getStockQuantity() const { return stockQuantity; }
void Medicine::setStockQuantity(int quantity) { this->stockQuantity = quantity; }

std::string Medicine::getUsageNote() const { return usageNote; }
void Medicine::setUsageNote(const std::string& note) { this->usageNote = note; }

bool Medicine::deductStock(int quantity) {
    if (quantity <= 0 || quantity > stockQuantity) {
        return false;
    }
    stockQuantity -= quantity;
    return true;
}

void Medicine::addStock(int quantity) {
    if (quantity > 0) {
        stockQuantity += quantity;
    }
}
