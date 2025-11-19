#pragma once
#include <vector>

class Inventory {
public:
    void addItem(const std::string& item);
    void removeItem(const std::string& item);
    bool hasItem(const std::string& item);
    void listItems() const;
    const std::vector<std::string>& getItems() const {
        return items;
    }

private:
    std::vector<std::string> items;
};
