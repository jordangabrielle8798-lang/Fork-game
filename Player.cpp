#include <string>
#include <iostream>
#include "Player.h"

void Player::move(const std::string& direction) {
    auto nextRoom = currentRoom->getExit(direction);
    if (nextRoom) {
        if (nextRoom->locked) {
            std::cout << "The " << nextRoom->name << " is locked. I'll have to find a key.\n";
        } else {
        currentRoom = nextRoom;
        look();
        }
    } else {
        std::cout << "I can't go that way.\n";
    }
}
void Player::takeItem(const std::string& item) {
    inventory.addItem(item);
}

void Player::dropItem(const std::string& item) {
    inventory.removeItem(item);
}

void Player::showInventory() const {
    inventory.listItems();
}