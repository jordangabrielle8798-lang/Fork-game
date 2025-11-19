#include <iostream>
#include <string>
#include <memory>


#include "Rooms.h"
#include "Inventory.h"
#include "Player.h"
#include "CommandHandler.h"

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
        auto bathroom1F = std::make_shared<Room>("First Floor Bathroom", "I'm in the first floor bathroom\n"
        "placeholder please change!\n"
        "I can go south", false);

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
    westWingHallExt->connect("north", bathroom1F);
    bathroom1F->connect("south", westWingHall);
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
