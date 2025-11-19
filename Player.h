#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "Rooms.h"
#include "Inventory.h"

class Player {
public:
    std::shared_ptr<Room> currentRoom;

    // Function to move player
    void move(const std::string& direction);

    // Function for player to interact with the world
    void interact(const std::string& action);

    // Function ro repeat room description to player
    void look() const {
    std::cout << currentRoom->description;
    }

    // Function to show inventory contents to player
    void takeItem(const std::string& item);
    void dropItem(const std::string& item);
    void showInventory() const;
    const std::vector<std::string>& getInventoryItems() const {
        return inventory.getItems();
    }

private:
    Inventory inventory;
};
