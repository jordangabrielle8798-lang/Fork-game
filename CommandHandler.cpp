#include <string>
#include <iostream>

#include "CommandHandler.h"

void processCommand(Player& player, const std::string& input) {
    if (input == "help") {
        std::cout << "Commands: look, north, south, east, west, up, down, inventory, search, quit\n";
    } else if (input == "look") {
        player.look();
    } else if (input == "inventory") {
        std::cout << "I am carrying:\n";
        for (const auto& item : player.getInventoryItems()) {
            std::cout << "- " << item << "\n";
        }
    } else if (input == "quit") {
        std::cout << "Thanks for Playing!\n";
        exit(0);
    } else if (input == "north" || input == "south" || input == "east" || 
               input == "west" || input == "down" || input == "up") {
        player.move(input);
    } else {
        std::cout << "I don't understand that command.\n";
    }
}