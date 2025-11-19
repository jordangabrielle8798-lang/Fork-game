#include <algorithm>
#include <string>
#include <iostream>

#include "Inventory.h"

void Inventory::addItem(const std::string& item) {
    items.push_back(item);
}

void Inventory::removeItem(const std::string& item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

bool Inventory::hasItem(const std::string& item) {
    return std::find(items.begin(), items.end(), item) != items.end();
}

void Inventory::listItems() const {
    for (const auto& item : items) {
        std::cout << "- " << item << "\n";
    }
}