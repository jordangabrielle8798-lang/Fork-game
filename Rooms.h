#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>

class Room {
public:
    std::string name;
    std::string description;
    std::map<std::string, std::shared_ptr<Room>> exits;
    bool locked;
    std::vector<std::string> hiddenItems;
    bool searched;

    Room(std::string n, std::string d, bool isLocked = false)
        : name(std::move(n)), description(std::move(d)), locked(isLocked), searched(false) {}

    void connect(const std::string& direction, const std::shared_ptr<Room>& target) {
        exits[direction] = target;
    }

    std::shared_ptr<Room> getExit(const std::string& direction) const {
        auto it = exits.find(direction);
        if (it != exits.end()) return it->second;
        return nullptr;
    }
    void addHiddenItem(const std::string& item);
    std::vector<std::string> getHiddenItems();
    bool hasHiddenItems();
    void clearHiddenItems(); // Remove room items after searching
    bool isSearched();
    void setSearched(bool value);
};