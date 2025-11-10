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
    bool hasItem(const std::string& item);
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
   // }
    } else if (input == "quit") {
        std::cout << "Thanks for Playing!\n";
        exit(0);
    } else if (input == "north" || input == "south" || input == "east" || input == "west" || input == "down" ||
         input == "up") {
        player.move(input);
    } else {
        std::cout << "I don't understand that command.\n";
    }
}

//---------------------------------------------------------
// Main game setup
//---------------------------------------------------------
int main() {
    // Create rooms
    auto foyer = std::make_shared<Room>("Foyer", "I've finally arrived at the house I heard about.\n"
        "It's said to be abandoned,\n"
        "but the door locked behind me when I got in here.\n"
        "There is a grand staircase in fromt of me leading up\n"
        "and dimly lit candles all around me.\n"
        "I can go east, west, north and up.\n", false);
    auto observatory = std::make_shared<Room>("Observatory",
    	"I'm in a massive two floor observatory that\n"
    	"reaches up to the stars above the mansion.\n"
    	"I'd imagine the view through the telescope\n"
    	"would be astounding if it weren't so cloudy outside\n"
    	"I can go west and up.\n", false);
    auto observatory2F = std::make_shared<Room>("Observatory Second Floor",
    	"I'm on the second floor of the observatory.\n"
    	"I just wish the clouds were such that I could see\n"
    	"through the telescope.\n"
    	"This grand room seems as though it's seen\n"
    	"plenty of use in its time.\n"
    	"I can go west and down.\n", false);
    auto upperLanding = std::make_shared<Room>("Second Floor Landing", "I'm on the Second Floor Landing.\n"
    	"The grand staircase is behind me, and there's\n"
    	"a massive portrait of who I can only assume to\n"
    	"be the estate's previous owner above the door in\n"
    	"front of me.\n"
    	"I can go east, west and north.", false);
    auto masterBedroom =std::make_shared<Room>("Master Bedroom\n",
    	"I'm in a luxurious master bedroom with a massive bed.\n"
    	"There's a huge dresser overflowing with clothes\n"
    	"against the wall.\n"
    	"I can go south", false);
    auto westWingHall = std::make_shared<Room>("West Wing Hall", "I'm in the West Wing Hall.\n"
    	"A hall with expensive frames around old family photos.\n"
        "A relatively polished floor for the house's age.\n"
        "And a grandfather clock that's stopped at 12:00.\n"
        "But I swear it was ticking a second ago.\n"
        "I can go east, west and north.\n", false);
        auto westWingHallExt = std::make_shared<Room>("West Wing Hall Extension", "Im in the west wing hall extension.\n"
        "There are plenty of shelves on the wall with little\n"
        "trinkets on them lining the walls among\n"
        "the family portraits.\n"
        "I can go east, west, north and south.\n", false);
    auto upperHall = std::make_shared<Room>("Second Floor Hall", "I'm in the second floor hall.\n"
    	 "The wallpaper is peeling at the edges, revealing\n"
    "layers of older patterns beneath—decades of attempts\n"
    "to cover up whatever came before.\n"
    "Yet despite the decay, there's not a speck of dust.\n"
    "Someone, or something, has been keeping this place clean.\n"
    "I can go east, west and north.\n", false);
    auto bathroom = std::make_shared<Room>("Bathroom", "I'm in what seems to be the only bathroom\n"
    	"in the whole mansion. The shower itself is\n"
    	"larger than my kitchen, and there's floor to\n"
    	"ceiling mirrors lining the walls."
    	"the towels still smell of fresh laundry.\n"
    	"I can go south", false);
    auto upperHallExt = std::make_shared<Room>("Upper Hall Extension", "I'm in the second floor hall extension.\n"
    	"The same cleanliness persists as on the other side\n"
    	"of the hall, except tjere are more family portraits\n"
    	"here than trinkets.\n"
    	"I can go east and north\n", false);
    auto guestBedroom = std::make_shared<Room>("Guest Bedroom", "I'm in the guest bedroom.\n"
    	"The queen bed in here feels luxuriously soft,\n"
    	"The bedding is also absolutely prestine like\n"
    	"somebody once did, or possibly still does care\n"
    	"for this place.\n"
    	"I can go south", false);
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
    auto kitchen = std::make_shared<Room>("Kitchen", "You see a table with a stale loaf of bread in the center.\n"
    	"It seems squatters have gotten in and made themselves\n"
    	"a meal recently...\n"
    	"It's still warm.\n"
        "I can go south and east.\n", false);
    auto pantry = std::make_shared<Room>("Pantry", "you see a bunch of out of date food\n"
        "and a trap door in the floor.\n"
        "I can go down and west.\n", false);
    auto basement = std::make_shared<Room>("Basement", "I'm in a dimly lit basement.\n"
    	"It smells of mold and rot down here but I can see a light to the east.\n"
    	"I think the rot smell may be coming from the north.\n"
        "I can go east, north and up.\n", false);

    // Connect rooms
    foyer->connect("north", northWingHall);
    foyer->connect("west", westWingHall);
    foyer->connect("up", upperLanding);
    foyer->connect("east", observatory);
    observatory->connect("west", foyer);
    observatory->connect("up", observatory2F);
    observatory2F->connect("down", observatory);
    observatory2F->connect("west", upperLanding);
    upperLanding->connect("down", foyer);
    upperLanding->connect("east", observatory2F);
    upperLanding->connect("north", masterBedroom);
    upperLanding->connect("west", upperHall);
    upperHall->connect("east", upperLanding);
    upperHall->connect("west", upperHallExt);
    upperHall->connect("north", bathroom);
    bathroom->connect("south", upperHall);
    upperHallExt->connect("east", upperHall);
    upperHallExt->connect("north", guestBedroom);
    guestBedroom->connect("south", upperHallExt);
    masterBedroom->connect("south", upperLanding);
    westWingHall->connect("east", foyer);
    westWingHall->connect("north", library);
    westWingHall->connect("west", westWingHallExt);
    westWingHallExt->connect("east", westWingHall);
    westWingHallExt->connect("west", office);
    library->connect("south", westWingHall);
    office->connect("east", westWingHallExt);
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