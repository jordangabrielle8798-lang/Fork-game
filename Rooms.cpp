#include <vector>
#include <string>

#include "Rooms.h"

void Room::addHiddenItem(const std::string& item) {
    hiddenItems.push_back(item);
}

std::vector<std::string> Room::getHiddenItems() {
    return hiddenItems;
}

bool Room::hasHiddenItems() {
    return !hiddenItems.empty();
}

void Room::clearHiddenItems() {
    hiddenItems.clear();
}

bool Room::isSearched() {
    return searched;
}

void Room::setSearched(bool value) {
    searched = value;
};