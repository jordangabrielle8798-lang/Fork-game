#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>

//---------------------------------------------------------
// Room class
//---------------------------------------------------------
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

//------------------------------------------------------
// Inventory class
//------------------------------------------------------
class Inventory {
public:
    void addItem(const std::string& item);
    void removeItem(const std::string& item);
    void hasItem(const std::string& item);
    void listItems() const;
    const std::vector<std::string>& getItems() const {
        return items;
    }

private:
    std::vector<std::string> items;
};

//----------------------------------------------------------
// Inventory method implementations
//----------------------------------------------------------
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

//---------------------------------------------------------
// Player class
//---------------------------------------------------------
class Player {
public:
    std::shared_ptr<Room> currentRoom;

    // Function to move player
    void move(const std::string& direction);

    // Function for player to interact with the world
    void interact(const std::string& action);

    // Function ro repeat room description to player
    void look() const;

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

//----------------------------------------------------------
// Room class implementation
//----------------------------------------------------------
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

//---------------------------------------------------------
// Player method implementations
//---------------------------------------------------------
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
void Player::takeItem(const std::string& item) {
    inventory.addItem(item);
}

void Player::dropItem(const std::string& item) {
    inventory.removeItem(item);
}

void Player::showInventory() const {
    inventory.listItems();
}
};

//---------------------------------------------------------
// Command handler
//---------------------------------------------------------
void processCommand(Player& player, const std::string& input) {
    for (const auto& item : player.getInventoryItems()) {
        std::cout << "- " << item << "\n";
    }
    if (input == "help") {
        std::cout << "Commands: look, north, south, east, west, up, down, search, quit\n";
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
    } else if (input == "north" || input == "south" || input == "east" || input == "west" || input == "down" || input == "up") {
        player.move(input);
    } else {
        std::cout << "I don't understand that command.\n";
};

//---------------------------------------------------------
// Main game setup
//---------------------------------------------------------
int main() {
    // Create rooms
    auto foyer = std::make_shared<Room>("Foyer", "I've finally arrived at the house I heard about.\n"
        "It's said to be abandoned,\n"
        "but the door locked behind me when I got in here.\n"
        "I can go east, west and north.\n", false);
        foyer->addHiddenItem("Basement Key");
    auto westWingHall = std::make_shared<Room>("West Wing Hall", "A hall with expensive frames around old family photos.\n"
        "A relatively polished floor for the house's age.\n"
        "And a grandfather clock that's stopped at 12:00.\n"
        "But I swear it was ticking a second ago.\n"
        "I can go east, west and north.\n", false);
    auto library = std::make_shared<Room>("Library", "I'm in a dimly lit library.\n"
        "The ghost of a recently smoked cigar hangs in the air\n"
        "faint, but still just barely there. Aged spirits soaked\n"
        "into the grain of the floorboards. All combining into the smell\n"
        "of obsession. Whatever the obsession was,it clearly\n"
        "stained the house as well. I feel unwelcome.\n"
        "I can go south.\n", false);
    auto northWingHall = std::make_shared<Room>("North Wing Hall", "A grand hallway with dusty family portraits on the wall.\n"
        "I can go south and north.\n", false);
    auto office = std::make_shared<Room>("Office", "Placeholder Please Change.\n"
        "I can go east.\n", false);
    auto kitchen = std::make_shared<Room>("Kitchen", "You see a table with some stale bread.\n"
        "I can go south and east.\n", false);
    auto pantry = std::make_shared<Room>("Pantry", "you see a bunch of out of date food\n"
        "and a trap door in the floor.\n"
        "I can go down and west.\n", false);
    auto basement = std::make_shared<Room>("Basement", "Placeholder Text Please Change.\n"
        "I can go up.\n", true);

    // Connect rooms
    foyer->connect("north", northWingHall);
    foyer->connect("west", westWingHall);
    westWingHall->connect("east", foyer);
    westWingHall->connect("north", library);
    westWingHall->connect("west", office);
    library->connect("south", westWingHall);
    office->connect("east", westWingHall);
    northWingHall->connect("south", foyer);
    northWingHall->connect("north", kitchen);
    kitchen->connect("south", northWingHall);
    kitchen->connect("east", pantry);
    pantry->connect("west", kitchen);
    pantry->connect("down", basement);
    basement->connect("up", pantry);

    // Create player
    Player player;
    player.currentRoom = foyer;

    std::cout << "Welcome to Fork!\nType 'help' for a list of commands.\n";
    player.look();

    // Game loop
    while (true) {
        std::cout << "\n> ";
        std::string input;
        std::getline(std::cin, input);

        if (!input.empty()) {
            processCommand(player, input);
        }
    }
};
