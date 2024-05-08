#include "splashkit.h"
#include "read_inputs.h"
#include <vector>

// List of names for automaking knights;
vector<string> knight_names =
{
    "Galahad", "Lancelot", "Gawain", "Percival", "Lionel", "Lyoness", "Gareth", "Bedivere", "Bleoberis", "Taile", "Lucan", "Palamedes", "Lamorak", "Ganis", "Safir", "Pelleas", "Kay", "Maris", "Dagonet", "Brunor", "Inconnu", "Alymore", "Mordred", "Solaire", "Logan", "Laurentius", "Rickert", "Petrus", "Ingward", "Griggs", "Vamos", "Vince", "Nico", "Lautrec", "Andre", "Oswald", "Shiva", "Domhnall", "Siegmeyer", "Patches", "Chester", "Gough", "Artorias"
};

// Random prefix for knight;
vector<string> knight_prefixes = 
{
    "Sir", "Captain", "Sargeant", "Commander", "Lord", "Holy", "Esteemed", "Brave", "Noble", "Invincible", "Champion", "Guard", "Handsome", "Stubborn", "Dragon", "Hero", "Warrior", "Tenacious", "Bear", "Twisted", "Abysswalker", "Hawkeye", "Sunlight", "Hyena", "Smith", "Knight", "Fair", "Cleric"
};

/*
* Equipment matchups. Sword vs spear, sword vs lamellar etc.
* Equip starts at 1, stats are added based on matchup later.
*/
float equipment_matchups[16][16] = 
{
    {1, 1.1, 1.3, 1.2, 1.5, 1.6, 1.3, 2, 1.5, 1, 0.8, 0.6, 0.7, 0.8, 1, 0.5},
    {0.9, 1, 1.3, 1.2, 1.5, 1.6, 1.3, 2, 1.6, 1.2, 1, 0.8, 1, 0.9, 1, 0.6},
    {0.7, 0.7, 1, 0.7, 1.5, 1.6, 1, 2, 1.5, 1, 1, 1, 0.5, 0.9, 1, 2},
    {0.8, 0.8, 1.3, 1, 1.5, 16, 13, 0, 0, 1, 1.5, 1.5, 1, 1, 1, 0.5},
    {0.5, 0.5, 0.5, 0.5, 1, 2, 1.5, 2, 2, 1.5, 1, 0.9, 0, 0.9, 1, 0.9},
    {0.4, 0.4, 0.4, 0.4, 0, 1, 0.5, 2, 2, 1.5, 1.2, 1, 1, 1.1, 1, 1},
    {0.7, 0.7, 1, 0, 0.7, 1.5, 1, 2, 1.5, 1, 1 ,1, 0.5, 0.9, 1, 1.5},
    {0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0.5, 0.5, 0.4, 0.5, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0.8, 1, 1, 0.54, 0.5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0.8, 1, 0.5, 0.5, 0.5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1.2, 1, 1, 0.5, 1, 0.8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1.3, 1, 1.5, 1, 2, 1, 1.5, 1, 1, 1, 1, 1, 1, 1, 1, 1.5},
    {1.2, 1.1, 1.1, 1, 0.9, 1.1, 0.9, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1.5, 0.4, 0, 1.5, 1.1, 1, 0.5, 1, 1, 1, 1, 1, 0.5, 1, 1, 1}
};

// Options available to the update knight;
enum knight_options
{
    UPDATE_NAME,
    UPDATE_PREFIX,
    UPDATE_EQUIP,
    UPDATE_FINISH
};

// Options available in the armoury menu;
enum equipment_options
{
    LIST_EQUIP,
    ADD_EQUIP,
    REMOVE_EQUIP,
    EXIT_EQUIP
};

// Options available to the main menu;
enum kingdom_menu_options
{
    RENAME_KINGDOM,
    ARMOURY,
    LIST_DETAIL,
    LIST_ONE,
    LIST_NAMES,
    LIST_EQUIPMENT,
    EXIT_MAIN
};

// Ootions for battlefield menu;
enum battlefield_options
{
    AUTOMAKE,
    MANAGE,
    GRAPH,
    BATTLE,
    EXIT
};

//List of equipment a unit can have;
enum equipment_list
{
    SWORD,
    AXE,
    SPEAR,
    MACE,
    BOW,
    CROSSBOW,
    JAVELIN,
    CLOTH,
    LEATHER,
    MAIL,
    LAMELLAR,
    PLATE,
    SHIELD,
    VISOR,
    STANDARD,
    HORSE
};

// Equipment list strings for cout;
vector<string> equipment_list_strings = 
{
    "Sword", "Axe", "Spear", "Mace", "Bow", "Crossbow", "Javelin", "Cloth", "Leather", "Mail", "Lamellar", "Plate", "Shield", "Visor", "Standard", "Horse"
};

// Data type of equipment;
struct equipment_data
{
    equipment_list item;
    float weight;
    string slot;
};

// Data type of all the knights data;
struct knight_data
{
    string name;
    string prefix;
    equipment_data weapon;
    equipment_data armour;
    equipment_data tool;
    float unit_weight;
};

// Lesser unit type, the militia;
struct militia_data
{
    equipment_data weapon;
    equipment_data armour;
    equipment_data tool;
    int unit_weight;
};

// Holds knights and militia;
struct army_data
{
    int size;
    vector<knight_data> knights;
    vector<militia_data> militia;
};

// Data type for all the kingdoms data;
struct kingdom_data
{
    string name;
    army_data army;
    color color;
};

// Holds two kingdoms;
struct battlefield_data
{
    vector<kingdom_data> kingdoms;
};

// Make a weapon;
equipment_list create_weapon()
{
    int random = rnd(0, 7);
    return static_cast<equipment_list>(random);
}

// Make an armour set;
equipment_list create_armour()
{
    int random = rnd(7, 12);
    return static_cast<equipment_list>(random);
}

// Make a tool;
equipment_list create_tool()
{
    int random = rnd(12, 16);
    return static_cast<equipment_list>(random);
}

// Check equipment, give default weight;
int assign_unit_weight(army_data army, int index, bool knight)
{
    float weight;
    
    if (knight == true)
    {
        // Weapon weight;
        if (army.knights[index].weapon.item == 0 or 1 or 3)
        {
            army.knights[index].weapon.weight = 1;
        } else
        {
            army.knights[index].weapon.weight = 2;
        }

        // Armour weight;
        if (army.knights[index].armour.item == 7) {army.knights[index].armour.weight = 1;}
        else if (army.knights[index].armour.item == 8) {army.knights[index].armour.weight = 2;}
        else if (army.knights[index].armour.item == 9) {army.knights[index].armour.weight = 3;}
        else if (army.knights[index].armour.item == 10) {army.knights[index].armour.weight = 4;}
        else {army.knights[index].armour.weight = 5;}

        // Misc item weight;
        if (army.knights[index].tool.item == 15)
        {
            army.knights[index].tool.weight = 3;
        } else
        {
            army.knights[index].tool.weight = 1;
        }

        weight = army.knights[index].weapon.weight + army.knights[index].armour.weight + army.knights[index].tool.weight;
        // Knight bonus;
        weight = weight * 3; //Subject to change;
    } else
    {
        // Weapon weight;
        if (army.militia[index].weapon.item == 0 or 1 or 3)
        {
            army.militia[index].weapon.weight = 1;
        } else
        {
            army.militia[index].weapon.weight = 2;
        }

        // Armour weight;
        if (army.militia[index].armour.item == 7) {army.militia[index].armour.weight = 1;}
        else if (army.militia[index].armour.item == 8) {army.militia[index].armour.weight = 2;}
        else if (army.militia[index].armour.item == 9) {army.militia[index].armour.weight = 3;}
        else if (army.militia[index].armour.item == 10) {army.militia[index].armour.weight = 4;}
        else {army.militia[index].armour.weight = 5;}

        // Misc item weight;
        if (army.militia[index].tool.item == 15)
        {
            army.militia[index].tool.weight = 3;
        } else
        {
            army.militia[index].tool.weight = 1;
        }

        weight = army.militia[index].weapon.weight + army.militia[index].armour.weight + army.militia[index].tool.weight;
    }
    return weight;
}

// Rnd to generate an equipment set for unit;
void automake_equipment(kingdom_data &kingdom, int index, bool is_knight)
{
    if (is_knight == true)
    {
        kingdom.army.knights[index].weapon.item = create_weapon();
        kingdom.army.knights[index].armour.item = create_armour();
        kingdom.army.knights[index].tool.item = create_tool();
        kingdom.army.knights[index].unit_weight = assign_unit_weight(kingdom.army, index, true);
    } else
    {
        kingdom.army.militia[index].weapon.item = create_weapon();
        kingdom.army.militia[index].armour.item = create_armour();
        kingdom.army.militia[index].tool.item = create_tool();
        kingdom.army.militia[index].unit_weight = assign_unit_weight(kingdom.army, index, false);
    }
}

// Adds a new knight to the kingdom;
knight_data read_knight()
{
    knight_data result;

    result.name = read_string("Enter a name: ");
    result.prefix = read_string("Enter a knightly prefix: ");
    // ask to automake equiment or customise;
    write_line("To give this knight some equipment, go to the armoury and select them.");

    return result;
}

// rework for army.knights;
void add_equipment(kingdom_data &kingdom, int index)
{
    bool more;
    more = true;

    while (more == true)
    {
        write_line("Enter a new equipment: ");
        more = read_boolean("Do you want to add more equipment, yes or no.");
    }
}

// REMOVAL;
void remove_equipment(kingdom_data &kingdom, int index)
{
    write_line("to be removed");
}

// List of all equipment a knight has;
void write_equipment(const kingdom_data &kingdom, int index)
{
    int find_item;

    // Find weapon;
    find_item = kingdom.army.knights[index].weapon.item;
    write("They have a " + equipment_list_strings[find_item]);

    // Find armour;
    find_item = kingdom.army.knights[index].armour.item;
    write(", a " + equipment_list_strings[find_item] + " set of armour");

    // Find tool;
    find_item = kingdom.army.knights[index].tool.item;
    write_line(", and a " + equipment_list_strings[find_item]);
}

// rework for army.knights;
void add_knight(kingdom_data &kingdom)
{
    knight_data new_knight;
    new_knight = read_knight();
    kingdom.army.knights.push_back(new_knight);
}

// Deletes a knight from specified index in the vector;
void delete_knight(kingdom_data &kingdom, int index)
{
    if (index >= 0 and index < kingdom.army.knights.size())
    {
        int last_index;
        last_index = kingdom.army.knights.size() - 1;
        kingdom.army.knights[index] = kingdom.army.knights[last_index];
        kingdom.army.knights.pop_back();
    } else
    {
        write_line("!ERROR! Invalid index provided! Try again.");
    }
}

// Display message about a knight and all their details;
void write_knight(const kingdom_data &kingdom, int index)
{
    if (index >= 0 and index < kingdom.army.knights.size())
    {
        write_line("");
        write_line("This knight is called " + kingdom.army.knights[index].prefix + " " + kingdom.army.knights[index].name + " of " + kingdom.name + ".");
        write_equipment(kingdom, index);
    } else
    {
        write_line("!ERROR! Invalid index provided! Try again."); // error for poor index of knight;
    }
}

// Manually assign equipment set for a knight;
void select_equipment(kingdom_data &kingdom)
{
    //for manual;
}

// Rnd to generate a new militia unit;
void automake_militia(kingdom_data &kingdom)
{
    militia_data new_militia;
    kingdom.army.militia.push_back(new_militia);
}

// Rnd to generate a new knight;
void automake_knight(battlefield_data &battlefield, int kingdom)
{
    knight_data new_knight;
    string name;
    string prefix;
    name = knight_names[rnd(0, knight_names.size())];
    prefix = knight_prefixes[rnd(0, knight_prefixes.size())];
    if (prefix != "Sir") {prefix = knight_prefixes[rnd(0, knight_prefixes.size())];}
    if (prefix != "Sir") {prefix = knight_prefixes[rnd(0, knight_prefixes.size())];}
    if (prefix != "Sir") {prefix = knight_prefixes[rnd(0, knight_prefixes.size())];}
    new_knight.name = name;
    new_knight.prefix = prefix;
    battlefield.kingdoms[kingdom].army.knights.push_back(new_knight);
}

// Give or change the kingdom a name;
string read_kingdom()
{
    string result;
    result = read_string("Give the kingdom a new name: ");
    return result;
}

// Display all knights in the kingdom;
void write_kingdom(const kingdom_data &kingdom)
{
    write_line("+++All Knights of " + kingdom.name + "+++");
    for(int index = 0; index < kingdom.army.knights.size(); index++)
    {
        write_knight(kingdom, index);
    }
    if (kingdom.army.knights.size() == 0) {write_line("*cricket noises*");}
    write_line("+++All Knights of " + kingdom.name + "+++");
    write_line("Press the enter key to continue...");
    read_line();
}

// Display knights and index, user selects by index input;
int select_knight(const kingdom_data &kingdom)
{
    int output;
    
    if (kingdom.army.knights.size() > 0)
    {
        for (int index = 0; index < kingdom.army.knights.size();index++)
        {
            write_line(std::to_string(index + 1) + ". " + kingdom.army.knights[index].name);
        }
        output = read_integer("Which knight will you select: ");

        while (output > kingdom.army.knights.size())
        {
            write_line("Invalid choice, try again.");
            output = read_integer("Which knight will you select: ");
        }
        return output - 1;
    } else
    {
        // error if there are no knights;
        write_line("There are no knights in the kingdom!");
        return (output = -1);
    }
}

// Armoury options: list, add or remove equipment from the knight;
equipment_options armoury_query(kingdom_data &kingdom, int index)
{
    int result;

    write_line("");
    write_line("///" + kingdom.name +" Armoury Menu///");
    write_line(kingdom.army.knights[index].name + " has entered the armoury to change equipment.");
    write_line("1: List all equipment");
    write_line("2: Add new equipment");
    write_line("3: Remove equipment");
    write_line("4: Exit");
    write_line("///" + kingdom.name +" Armoury Menu///");
    result = read_integer("Select an option: ");

    return static_cast<equipment_options>(result - 1);
}

// Edit equipments of knight;
void armoury_menu(kingdom_data &kingdom, int index)
{
    equipment_options option;

    do
    {
        
        option = armoury_query(kingdom, index);

        switch(option)
        {
            case LIST_EQUIP:
                write_equipment(kingdom, index);
                write_line("Press the enter key to continue...");
                read_line();
                break;
            
            case ADD_EQUIP:
                add_equipment(kingdom, index);
                break;

            case REMOVE_EQUIP:
                remove_equipment(kingdom, index);
                break;

            case EXIT_EQUIP:
                break;

            default:
                write_line("Invalid choice, try again.");
        }
    } while (option != EXIT_EQUIP);
}

// Main menu options, the top most level menu;
kingdom_menu_options kingdom_query(kingdom_data &kingdom)
{
    int result;

    write_line("");
    write_line("===Welcome to the kingdom of " + kingdom.name + " Main Menu===");
    write_line("1: Change kingdom name");
    write_line("2: Enter the armour to adjust units");
    write_line("3: List of all knights in detail");
    write_line("4: List knights and select one two view");
    write_line("5: List names and titles of knights");
    write_line("6: List of all equipment in use");
    write_line("7: Return to battlefield menu");
    write_line("===Welcome to the kingdom of " + kingdom.name + " Main Menu===");
    result = read_integer("Select an option: ");

    return static_cast<kingdom_menu_options>(result - 1);
}

// List of options to customize and update and existing knight;
knight_options update_query(kingdom_data &kingdom, int index)
{
    int result;

    write_line("");
    write_line("===" + kingdom.name +" Barracks Menu===");
    write_line(kingdom.army.knights[index].name + " has entered the barracks to update their details.");
    write_line("1: Update name");
    write_line("2: Update prefix");
    write_line("3: View loadout");
    write_line("4: Exit");
    write_line("===" + kingdom.name +" Barracks Menu===");
    result = read_integer("Select an option: ");

    return static_cast<knight_options>(result - 1);
}

void army_size(battlefield_data &battlefield)
{
    battlefield.kingdoms[0].army.size = battlefield.kingdoms[0].army.knights.size() + battlefield.kingdoms[0].army.militia.size();
    battlefield.kingdoms[1].army.size = battlefield.kingdoms[1].army.knights.size() + battlefield.kingdoms[1].army.militia.size();
}

// Battlefield menu display and selection;
battlefield_options battle_query(battlefield_data &battlefield)
{
    int result;
    army_size(battlefield);
    write_line(battlefield.kingdoms[0].name + " has " + std::to_string(battlefield.kingdoms[0].army.size) + " troops");
    write_line("and");
    write_line(battlefield.kingdoms[1].name + " has " + std::to_string(battlefield.kingdoms[1].army.size) + " troops");
    write_line("####Battlefield Menu####");
    write_line("1: Automake two kingdoms entirely");
    write_line("2: Enter kingdom management mode");
    write_line("3: Update window with graph");
    write_line("4: Enter battle mode");
    write_line("5: Exit program");
    write_line("####Battlefield Menu####");
    result = read_integer("Select option: ");

    return static_cast<battlefield_options>(result - 1);
}

// Run menu loop for user to make changes to their knight;
void update_knight(kingdom_data &kingdom, int index)
{
    knight_options option;

    do
    {
        
        option = update_query(kingdom, index);

        switch(option)
        {
            case UPDATE_NAME:
                kingdom.army.knights[index].name = read_string("Enter a new name: ");
                break;

            case UPDATE_PREFIX:
                kingdom.army.knights[index].prefix = read_string("Enter a new prefix or title: ");
                break;

            case UPDATE_EQUIP:
                write_line("coming soon");
                //armoury_menu(kingdom, index);
                break;

            case UPDATE_FINISH:
                break;

            default:
                write_line("Invalid choice, try again.");
        }
    } while (option != UPDATE_FINISH);
}

// See the amount of names in use;
void find_names(kingdom_data &kingdom)
{
    vector<int> names;
    vector<int> prefixes;
    int knights_amount = 0;
    // Init arrays;
    for (int x = 0; x < knight_names.size(); x++)
    {
        names.push_back(0);
    }
    for (int y = 0; y < knight_prefixes.size(); y++)
    {
        prefixes.push_back(0);
    }

    // If knight name matches, count up for that name.[]
    for (int i = 0; i < kingdom.army.knights.size(); i++)
    {
        knights_amount++;
        // Names;
        for (int n = 0; n < knight_names.size(); n++)
        if (kingdom.army.knights[i].name == knight_names[n])
        {
            names[n]++;
        }
        // Prefixes;
        for (int p = 0; p < knight_prefixes.size(); p++)
        if (kingdom.army.knights[i].prefix == knight_prefixes[p])
        {
            prefixes[p]++;
        }
    }

    // List names and how many times they appear;
    for (int l = 0; l < knight_names.size(); l++)
    {
        write_line(knight_names[l] + " appears " + std::to_string(names[l]) + " times.");
    }
    write_line("Press the enter key to continue...");
    read_line();
    // Prefixes;
    for (int e = 0; e < knight_prefixes.size(); e++)
    {
        write_line(knight_prefixes[e] + " appears " + std::to_string(prefixes[e]) + " times.");
    }

    write_line("");
    write_line("There are " + std::to_string(knights_amount) + " knights in " + kingdom.name);
}

// See the amount of equipments in use;
void find_equipment(kingdom_data &kingdom)
{
    vector<int> equipments;
    int count;
    count = 16;
    while (equipments.size() < count)
    {
        equipments.push_back(0);
    }

    for (int j = 0; j < equipments.size(); j++)
    {
        for (int i = 0; i < kingdom.army.knights.size(); i++)
        {
            if (kingdom.army.knights[i].weapon.item == j)
            {
                equipments[j]++;
            }
            if (kingdom.army.knights[i].armour.item == j)
            {
                equipments[j]++;
            }
            if (kingdom.army.knights[i].tool.item == j)
            {
                equipments[j]++;
            }
        }
    }

    for (int h = 0; h < equipments.size(); h++)
    {
        write_line(std::to_string(h) + " equipment index was found with " + std::to_string(equipments[h]) + " knights.");
    }
}

// Display options menu to the user first entering the program. This is the topmost menu;
void kingdom_menu(battlefield_data &battlefield, int kingdom)
{
    kingdom_menu_options option;
    int query;
    write_line("");
    write_line(battlefield.kingdoms[kingdom].name + " has " + std::to_string(battlefield.kingdoms[kingdom].army.size) + " troops.");

    do
    {
        
        option = kingdom_query(battlefield.kingdoms[kingdom]);

        switch(option)
        {
            case RENAME_KINGDOM: // Rename the kingdom;
                battlefield.kingdoms[kingdom].name = read_kingdom();
                break;

            case ARMOURY:
                write_line("coming soon");
                break;
            
            case LIST_DETAIL: // All knights and their exact loadout;
                write_kingdom(battlefield.kingdoms[kingdom]);
                break;

            case LIST_ONE:
                query = select_knight(battlefield.kingdoms[kingdom]);
                if (query >= 0 )
                {
                    write_knight(battlefield.kingdoms[kingdom], query);
                    write_line("Press the enter key to continue...");
                    read_line();
                }
                break;

            case LIST_NAMES: // Lists names and prefixes for all knights;
                find_names(battlefield.kingdoms[kingdom]);
                break;

            case LIST_EQUIPMENT: // Equipment of all knights and militia;
                find_equipment(battlefield.kingdoms[kingdom]);
                break;

            case EXIT_MAIN:
                break;

            default:
                write_line("Invalid choice, try again.");
        }
    } while (option != EXIT_MAIN);
}

// Automakes a single kingdom selected;
void automake_kingdom(battlefield_data &battlefield, int select, int amount)
{
    int random;
    int counter;
    int kingdom;
    int ratio;
    bool divisible = false;
    kingdom = 0;
    counter = 0;
    random = 0;

    if (select == 2)
    {
        /*
        * Essentially caps the maximum militia at 16 500.
        * This is done to make smaller armies feel more common.
        * A knight for every x militia determined by random.
        * Use rounding to find an even number. No fractions.
        */
        if (amount != 0)
        {
            random = amount;
            ratio = amount / 10;
        } else {random = rnd(10000, 50000);}
            
        if (random < 10000)
        {
            random = random * 0.5;
            ratio = rnd(20, 50);
        }
        else if (random > 10000 and random < 20000)
        {
            random = random * 0.4;
            ratio = rnd(50, 120);
        }
        else if (random > 20000 and random < 30000)
        {
            random = random * 0.3;
            ratio = rnd(130, 300);
        } else
        {
            random = random * 0.25;
            ratio = rnd(500, 800);
        }
        

        // Check if ratio of knights to militia is no remainders, as to avoid a decimal;
        while (divisible == false)
        {
            if (random % ratio == 0){divisible = true;}
            else {random--;}
        }

        // msg;
        write_line("Generating units, may take a few seconds...");

        // Generate units;
        while (kingdom < 2)
        {
            while (counter < random)
            {
                automake_militia(battlefield.kingdoms[kingdom]);
                automake_equipment(battlefield.kingdoms[kingdom], counter, false);
                counter++;
            }
            counter = 0;
            while (counter < ratio)
            {
                automake_knight(battlefield, kingdom);
                automake_equipment(battlefield.kingdoms[kingdom], counter, true);
                counter++;
            }
            counter = 0;
            kingdom++;
        }
    }
}

// Create two kingdoms, name them, and add them to the battlefield;
void load_battlefield(battlefield_data &battlefield)
{
    kingdom_data kingdom_one;
    kingdom_data kingdom_two;

    kingdom_one.name = read_kingdom();
    kingdom_two.name = read_kingdom();

    // Assign random colours;
    kingdom_one.color = random_rgb_color(255);
    kingdom_two.color = random_rgb_color(255);

    battlefield.kingdoms.push_back(kingdom_one);
    battlefield.kingdoms.push_back(kingdom_two);
}

// Analyses weights. Compares a units equipment and changes its weight vs the enemy units equipment;
void weight_adjustment(vector<float> &to_check)
{
    const int size = 16; // Size of array x and y, is fixed and known;
    int chk = 0;

    // Side one;
    while (chk < 3)
    {
        for (int x = 0; x < size; x++)
        {
            if (to_check[chk] == x)
            {
                for (int y = 0; y < size; y++)
                {
                    if (y == to_check[3]) {to_check[6] = to_check[6] + equipment_matchups[x][y];}
                    else if (y == to_check[4]) {to_check[6] = to_check[6] + equipment_matchups[x][y];}
                    else {to_check[6] = to_check[6] + equipment_matchups[x][y];}
                }
            }
        }
        chk++;
    }
    // Side two;
    while (chk < 6)
    {
        for (int x = 0; x < size; x++)
        {
            if (to_check[chk] == x)
            {
                for (int y = 0; y < size; y++)
                {
                    if (y == to_check[0]) {to_check[7] = to_check[7] + equipment_matchups[x][y];}
                    else if (y == to_check[1]) {to_check[7] = to_check[7] + equipment_matchups[x][y];}
                    else {to_check[7] = to_check[7] + equipment_matchups[x][y];}
                }
            }
        }
        chk++;
    }
}

// Make bar and outline;
void make_bars(float x, float y, float w, float h, color color)
{
    fill_rectangle(color, x, y, w, h);
    draw_rectangle(COLOR_BLACK, x, y, w, h);
}

// Find how many armours per weapon;
int count_armours(const kingdom_data &kingdom, int weapon, int armour, bool is_knight)
{
    int amount = 0;
    armour = armour + 7;

    if (is_knight == false)
    {
        for (int i = 0; i < kingdom.army.militia.size(); i++)
        {
            if (kingdom.army.militia[i].weapon.item == weapon)
            {
                if (kingdom.army.militia[i].armour.item == armour)
                {
                    amount++;
                }
            }
        }
    } else
    {
        for (int i = 0; i < kingdom.army.knights.size(); i++)
        {
            if (kingdom.army.knights[i].weapon.item == weapon)
            {
                if (kingdom.army.knights[i].armour.item == armour)
                {
                    amount++;
                }
            }
        }
    }
    return amount;
}

// Finds the weapon count of each army;
void count_equipments(const kingdom_data &kingdom, vector<int> &gear)
{
    // Find equipment;
    for (int one = 0; one < kingdom.army.militia.size(); one++)
    {
        // Find weapon;
        if (kingdom.army.militia[one].weapon.item == 0)
        {gear[0]++;}
        else if (kingdom.army.militia[one].weapon.item == 1)
        {gear[1]++;}
        else if (kingdom.army.militia[one].weapon.item == 2)
        {gear[2]++;}
        else if (kingdom.army.militia[one].weapon.item == 3)
        {gear[3]++;}
        else if (kingdom.army.militia[one].weapon.item == 4)
        {gear[4]++;}
        else if (kingdom.army.militia[one].weapon.item == 5)
        {gear[5]++;}
        else if (kingdom.army.militia[one].weapon.item == 6)
        {gear[6]++;}
        if (kingdom.army.militia[one].tool.item == 15)
        {gear[7]++;}
    }
    for (int two = 0; two < kingdom.army.knights.size(); two++)
    {
        // Find weapon;
        if (kingdom.army.knights[two].weapon.item == 0)
        {gear[0]++;}
        else if (kingdom.army.knights[two].weapon.item == 1)
        {gear[1]++;}
        else if (kingdom.army.knights[two].weapon.item == 2)
        {gear[2]++;}
        else if (kingdom.army.knights[two].weapon.item == 3)
        {gear[3]++;}
        else if (kingdom.army.knights[two].weapon.item == 4)
        {gear[4]++;}
        else if (kingdom.army.knights[two].weapon.item == 5)
        {gear[5]++;}
        else if (kingdom.army.knights[two].weapon.item == 6)
        {gear[6]++;}
        if (kingdom.army.knights[two].tool.item == 15)
        {gear[7]++;}
    }
}

// Pre battle graphing option;
void army_analysis(battlefield_data &battlefield)
{
    open_window("Army Analysis", 1400, 800);
    clear_screen(COLOR_GRAY);

    float x, y, h, t, l, horses;
    float w;
    vector<int> gear;
    vector<color> colors;
    int g, k;
    g = 0;
    k = 0;
    // Init gear, one for each equipment to count;
    while (g < 9)
    {
        gear.push_back(0);
        g++;
    }
    colors.push_back(COLOR_WHEAT);
    colors.push_back(COLOR_SADDLE_BROWN);
    colors.push_back(COLOR_STEEL_BLUE);
    colors.push_back(COLOR_TAN);
    colors.push_back(COLOR_SILVER);

    draw_text("Arms and armour of " + battlefield.kingdoms[0].name + " and " + battlefield.kingdoms[1].name, COLOR_BLACK, "arial", 30, 5, 10);

    // Find all equipment;
    while (k < 2)
    {
        // Fill gear vector and armour 2d array;
        count_equipments(battlefield.kingdoms[k], gear);
        // Array contains which weapons contains how many armours;
        int militia_matrix[7][5];
        int knight_matrix[7][5];
        int new_matrix[7][5];
        // Matrix x aka weapon;
        for (int x = 0; x < 7; x++)
        {
            // Matrix y aka armour;
            for (int y = 0; y < 5; y++)
            {
                militia_matrix[x][y] = count_armours(battlefield.kingdoms[k], x, y, false);
                knight_matrix[x][y] = count_armours(battlefield.kingdoms[k], x, y, true);
            }
        }

        for (int x = 0; x < 7; x++)
        {
            // Matrix y aka armour;
            for (int y = 0; y < 5; y++)
            {
                new_matrix[x][y] = militia_matrix[x][y] + knight_matrix[x][y];
            }
        }

        // Bars per weapon, each weapon has amours ratios;
        x = 0;
        y = 70;
        if (k == 1) {y = y + (y / 2) + 5;}
        w = screen_width();
        h = (screen_height() / 35);
        draw_text(battlefield.kingdoms[k].name + " Swordsmen: " + std::to_string(gear[0]), COLOR_BLACK, "arial", 12, 5, y - 13);
        make_bars(x, y, w, h, COLOR_BLACK);
        // Extra tool tips;
        vector<string> text;
        text.push_back("Cloth");
        text.push_back("Leather");
        text.push_back("Mail");
        text.push_back("Lamellar");
        text.push_back("Plate");
        // Fill in armour ratios;
        int armour = w;
        for (int m = 0; m < 5; m++)
        {
            t = new_matrix[0][0] + new_matrix[0][1] + new_matrix[0][2] + new_matrix[0][3] + new_matrix[0][4];
            l = new_matrix[0][m] / t;
            make_bars(armour - (w * l), y, (w * l), h, colors[m]);
            if (l > 0.05)
            {
                draw_text(text[m], COLOR_BLACK, "arial", 11, armour - (w * l) + 3, y + 3);
            }
            armour = armour - (w * l);
        }
        armour = w;
        y = y + h * 4;
        draw_text(battlefield.kingdoms[k].name + " Axemen: " + std::to_string(gear[1]), COLOR_BLACK, "arial", 12, 5, y - 13);
        make_bars(x, y, w, h, COLOR_BLACK);
        for (int m = 0; m < 5; m++)
        {
            t = new_matrix[1][0] + new_matrix[1][1] + new_matrix[1][2] + new_matrix[1][3] + new_matrix[1][4];
            l = new_matrix[1][m] / t;
            make_bars(armour - (w * l), y, (w * l), h, colors[m]);
            armour = armour - (w * l);
        }
        armour = w;
        y = y + h * 4;
        draw_text(battlefield.kingdoms[k].name + " Spearmen: " + std::to_string(gear[2]), COLOR_BLACK, "arial", 12, 5, y - 13);
        make_bars(x, y, w, h, COLOR_BLACK);
        for (int m = 0; m < 5; m++)
        {
            t = new_matrix[2][0] + new_matrix[2][1] + new_matrix[2][2] + new_matrix[2][3] + new_matrix[2][4];
            l = new_matrix[2][m] / t;
            make_bars(armour - (w * l), y, (w * l), h, colors[m]);
            armour = armour - (w * l);
        }
        armour = w;
        y = y + h * 4;
        draw_text(battlefield.kingdoms[k].name + " Macemen: " + std::to_string(gear[3]), COLOR_BLACK, "arial", 12, 5, y - 13);
        make_bars(x, y, w, h, COLOR_BLACK);
        for (int m = 0; m < 5; m++)
        {
            t = new_matrix[3][0] + new_matrix[3][1] + new_matrix[3][2] + new_matrix[3][3] + new_matrix[3][4];
            l = new_matrix[3][m] / t;
            make_bars(armour - (w * l), y, (w * l), h, colors[m]);
            armour = armour - (w * l);
        }
        armour = w;
        y = y + h * 4;
        draw_text(battlefield.kingdoms[k].name + " Archers: " + std::to_string(gear[4]), COLOR_BLACK, "arial", 12, 5, y - 13);
        make_bars(x, y, w, h, COLOR_BLACK);
        for (int m = 0; m < 5; m++)
        {
            t = new_matrix[4][0] + new_matrix[4][1] + new_matrix[4][2] + new_matrix[4][3] + new_matrix[4][4];
            l = new_matrix[4][m] / t;
            make_bars(armour - (w * l), y, (w * l), h, colors[m]);
            armour = armour - (w * l);
        }
        armour = w;
        y = y + h * 4;
        draw_text(battlefield.kingdoms[k].name + " Crossbowmen: " + std::to_string(gear[5]), COLOR_BLACK, "arial", 12, 5, y - 13);
        make_bars(x, y, w, h, COLOR_BLACK);
        for (int m = 0; m < 5; m++)
        {
            t = new_matrix[5][0] + new_matrix[5][1] + new_matrix[5][2] + new_matrix[5][3] + new_matrix[5][4];
            l = new_matrix[5][m] / t;
            make_bars(armour - (w * l), y, (w * l), h, colors[m]);
            armour = armour - (w * l);
        }
        armour = w;
        y = y + h * 4;
        draw_text(battlefield.kingdoms[k].name + " Javelin Throwers: " + std::to_string(gear[6]), COLOR_BLACK, "arial", 12, 5, y - 13);
        make_bars(x, y, w, h, COLOR_BLACK);
        for (int m = 0; m < 5; m++)
        {
            t = new_matrix[6][0] + new_matrix[6][1] + new_matrix[6][2] + new_matrix[6][3] + new_matrix[6][4];
            l = new_matrix[6][m] / t;
            make_bars(armour - (w * l), y, (w * l), h, colors[m]);
            armour = armour - (w * l);
        }
        armour = 0;
        horses = 0;
        y = y + h * 4;
        draw_text(battlefield.kingdoms[k].name + " Cavalry: " + std::to_string(gear[7]), COLOR_BLACK, "arial", 12, 5, y - 13);
        make_bars(x, y, w, h, COLOR_PERU);
        for (int i = 0; i < battlefield.kingdoms[k].army.knights.size(); i++)
        {
            if (battlefield.kingdoms[k].army.knights[i].tool.item == 15)
            {
                horses++;
            }
        }
        make_bars(x, y, (w * (horses / gear[7])), h, COLOR_GOLD);
        if (horses / gear[7] > 0.03)
        {
            draw_text("Knights", COLOR_BLACK, "arial", 11, x + 3, y + 3);
        }
        
        // Clean gear vector;
        for (int i = 0; i < gear.size(); i++) {gear[i] = 0;}

        k++;
    }
    
    refresh_screen(60);
    write_line("Press the enter key to exit and close Army Analysis screen...");
    read_line();
    close_window("Army Analysis");
}

// Finds size of unit for bar size;
int bar_size(kingdom_data &kingdom, int weap_i)
{
    int i;
    int weapons = 0;
    for (i = 0; i < kingdom.army.militia.size(); i++)
    {
        if (kingdom.army.militia[i].weapon.item == weap_i)
        {
            weapons++;
        }
    }
    return weapons;
}

// Global vector for kill ticker feed, more convenient/lazy to be global than local;
vector<string> kills = {"", "", "", "", ""};


// Draw bars, graphs, and other visuals;
void draw_army(battlefield_data &battlefield, string ticker, int &ticker_counter)
{
    double size;
    int x;
    int y;
    double rect_h;
    int rect_w;
    //int diff;
    double one_size,two_size, knight_one, knight_two, knight_size;
    color color_one, color_two;
    color_one = battlefield.kingdoms[0].color;
    color_two = battlefield.kingdoms[1].color;

    one_size = battlefield.kingdoms[0].army.militia.size() + battlefield.kingdoms[0].army.knights.size();
    two_size = battlefield.kingdoms[1].army.militia.size() + battlefield.kingdoms[1].army.knights.size();

    // Top most total units bar that fills the screen and just represents the ratio;
    rect_h = 100;
    rect_w = screen_width();
    x = 0;
    y = 50;
    draw_text("War of " + battlefield.kingdoms[0].name + " and " + battlefield.kingdoms[1].name, COLOR_BLACK, "arial", 30, 5, 10);
    fill_rectangle(color_one, x, y, rect_w, rect_h);
    draw_rectangle(COLOR_BLACK, x, y, rect_w, rect_h);
    size = ( two_size / (one_size + two_size));
    rect_w = (screen_width() * size);
    fill_rectangle(color_two, x, y, rect_w, rect_h);
    draw_rectangle(COLOR_BLACK, x, y, rect_w, rect_h);

    // Detail indicating the winning side;
    if (one_size > two_size) {draw_text("<<<", COLOR_BLACK, "arial", 25, rect_w, (y + (rect_h / 2.6)));}
    else {draw_text(">>>", COLOR_BLACK, "arial", 25, (rect_w - 44), (y + (rect_h / 2.6)));}

    rect_h = 20;
    rect_w = screen_width();

    // Top-middle weapon charts;
    // Index 0;
    one_size = bar_size(battlefield.kingdoms[0], 0);
    two_size = bar_size(battlefield.kingdoms[1], 0);
    size = ( two_size / (one_size + two_size));
    y = screen_height() / 3.5;
    make_bars(x, y, rect_w, rect_h, color_one);
    rect_w = (screen_width() * size);
    make_bars(x, y, rect_w, rect_h, color_two);
    draw_text("Swords", COLOR_BLACK, "arial", 12, 5, y - 13);
    // Index 1;
    one_size = bar_size(battlefield.kingdoms[0], 1);
    two_size = bar_size(battlefield.kingdoms[1], 1);
    size = ( two_size / (one_size + two_size));
    y = y + 38;
    rect_w = screen_width();
    make_bars(x, y, rect_w, rect_h, color_one);
    rect_w = (screen_width() * size);
    make_bars(x, y, rect_w, rect_h, color_two);
    draw_text("Axes", COLOR_BLACK, "arial", 12, 5, y - 13);
    // Index 2;
    one_size = bar_size(battlefield.kingdoms[0], 2);
    two_size = bar_size(battlefield.kingdoms[1], 2);
    size = ( two_size / (one_size + two_size));
    y = y + 38;
    rect_w = screen_width();
    make_bars(x, y, rect_w, rect_h, color_one);
    rect_w = (screen_width() * size);
    make_bars(x, y, rect_w, rect_h, color_two);
    draw_text("Spears", COLOR_BLACK, "arial", 12, 5, y - 13);
    // Index 3;
    one_size = bar_size(battlefield.kingdoms[0], 3);
    two_size = bar_size(battlefield.kingdoms[1], 3);
    size = ( two_size / (one_size + two_size));
    y = y + 38;
    rect_w = screen_width();
    make_bars(x, y, rect_w, rect_h, color_one);
    rect_w = (screen_width() * size);
    make_bars(x, y, rect_w, rect_h, color_two);
    draw_text("Maces", COLOR_BLACK, "arial", 12, 5, y - 13);
    // Index 4;
    one_size = bar_size(battlefield.kingdoms[0], 4);
    two_size = bar_size(battlefield.kingdoms[1], 4);
    size = ( two_size / (one_size + two_size));
    y = y + 38;
    rect_w = screen_width();
    make_bars(x, y, rect_w, rect_h, color_one);
    rect_w = (screen_width() * size);
    make_bars(x, y, rect_w, rect_h, color_two);
    draw_text("Bows", COLOR_BLACK, "arial", 12, 5, y - 13);
    // Index 5;
    one_size = bar_size(battlefield.kingdoms[0], 5);
    two_size = bar_size(battlefield.kingdoms[1], 5);
    size = ( two_size / (one_size + two_size));
    y = y + 38;
    rect_w = screen_width();
    make_bars(x, y, rect_w, rect_h, color_one);
    rect_w = (screen_width() * size);
    make_bars(x, y, rect_w, rect_h, color_two);
    draw_text("Crossbows", COLOR_BLACK, "arial", 12, 5, y - 13);
    // Index 6;
    one_size = bar_size(battlefield.kingdoms[0], 6);
    two_size = bar_size(battlefield.kingdoms[1], 6);
    size = ( two_size / (one_size + two_size));
    y = y + 38;
    rect_w = screen_width();
    make_bars(x, y, rect_w, rect_h, color_one);
    rect_w = (screen_width() * size);
    make_bars(x, y, rect_w, rect_h, color_two);
    draw_text("Javelins", COLOR_BLACK, "arial", 12, 5, y - 13);

    // Bottom left militia and knights amounts;
    rect_h = 40;
    y = screen_width() / 2.6;
    x = 0;

    // Side one;
    one_size = battlefield.kingdoms[0].army.militia.size();
    two_size = battlefield.kingdoms[1].army.militia.size();
    size = ( one_size / (one_size + two_size));
    knight_one = battlefield.kingdoms[0].army.knights.size();
    knight_two = battlefield.kingdoms[1].army.knights.size();
    knight_size = ( knight_one / (knight_one + knight_two));

    rect_w = (screen_width() / 2) * (knight_size);
    draw_text(battlefield.kingdoms[0].name + "'s Knights " + std::to_string(battlefield.kingdoms[0].army.knights.size()), COLOR_BLACK, "arial", 16, 5, y - 18);
    fill_rectangle(color_one, x, y, (rect_w / 2), rect_h);
    draw_rectangle(COLOR_BLACK, x, y, (rect_w / 2), rect_h);
    y = y + 65;
    rect_w = (screen_width() / 2) * (size);
    draw_text(battlefield.kingdoms[0].name + "'s Militia " + std::to_string(battlefield.kingdoms[0].army.militia.size()), COLOR_BLACK, "arial", 16, 5, y - 18);
    fill_rectangle(color_one, x, y, rect_w, rect_h);
    draw_rectangle(COLOR_BLACK, x, y, rect_w, rect_h);

    // Side two;
    one_size = battlefield.kingdoms[0].army.militia.size();
    two_size = battlefield.kingdoms[1].army.militia.size();
    size = ( two_size / (one_size + two_size));
    knight_one = battlefield.kingdoms[0].army.knights.size();
    knight_two = battlefield.kingdoms[1].army.knights.size();
    knight_size = ( knight_two / (knight_one + knight_two));

    y = y + 65;
    rect_w = (screen_width() / 2) * (knight_size);
    draw_text(battlefield.kingdoms[1].name + "'s Militia " + std::to_string(battlefield.kingdoms[1].army.militia.size()), COLOR_BLACK, "arial", 16, 5, y - 18);
    fill_rectangle(color_two, x, y, rect_w, rect_h);
    draw_rectangle(COLOR_BLACK, x, y, rect_w, rect_h);
    y = y + 65;
    rect_w = (screen_width() / 2) * (size);
    draw_text(battlefield.kingdoms[1].name + "'s Knights " + std::to_string(battlefield.kingdoms[1].army.knights.size()), COLOR_BLACK, "arial", 16, 5, y - 18);
    fill_rectangle(color_two, x, y, (rect_w / 2), rect_h);
    draw_rectangle(COLOR_BLACK, x, y, (rect_w / 2), rect_h);

    // Bottom right kill feed;
    color black80, black60, black40, black20;
    const double zero = 0;
    black80 = rgba_color(zero, zero, zero, 0.8);
    black60 = rgba_color(zero, zero, zero, 0.6);
    black40 = rgba_color(zero, zero, zero, 0.4);
    black20 = rgba_color(zero, zero, zero, 0.2);

    switch (ticker_counter)
    {
        case 0:
            kills[0] = ticker;
            draw_text(kills[0], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 50);
            if (kills[4].length() > 1)
            {draw_text(kills[4], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 100);
            draw_text(kills[3], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 150);
            draw_text(kills[2], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 200);
            draw_text(kills[1], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 250);}
            ticker_counter++;
            break;
        case 1:
            kills[1] = ticker;
            draw_text(kills[1], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 50);
            draw_text(kills[0], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 100);
            if (kills[4].length() > 1)
            {draw_text(kills[4], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 150);
            draw_text(kills[3], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 200);
            draw_text(kills[2], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 250);}
            ticker_counter++;
            break;
        case 2:
            kills[2] = ticker;
            draw_text(kills[2], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 50);
            draw_text(kills[1], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 100);
            draw_text(kills[0], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 150);
            if (kills[4].length() > 1)
            {draw_text(kills[4], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 200);
            draw_text(kills[3], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 250);}
            ticker_counter++;
            break;
        case 3:
            kills[3] = ticker;
            draw_text(kills[3], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 50);
            draw_text(kills[2], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 100);
            draw_text(kills[1], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 150);
            draw_text(kills[0], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 200);
            if (kills[4].length() > 1)
            {draw_text(kills[4], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 250);}
            ticker_counter++;
            break;
        case 4:
            kills[4] = ticker;
            draw_text(kills[4], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 50);
            draw_text(kills[3], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 100);
            draw_text(kills[2], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 150);
            draw_text(kills[1], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 200);
            draw_text(kills[0], COLOR_BLACK, "arial", 22, screen_width() / 2 , screen_height() - 250);
            ticker_counter = 0;
            break;

        default:
            write_line("ticker counter switch default");
            break;
    }
}

// execute step;
void execute_step(battlefield_data &battlefield, string ticker, int &ticker_counter)
{
    clear_screen(COLOR_GRAY);
    draw_army(battlefield, ticker, ticker_counter);
    refresh_screen(60);
}

/*
* Global battle tracker.
* Side one and two militia,
* side one and two knights,
* side one and two casualties.
* Index 6 holds ratio of militia to knights.
* Index 7 holds the amount of militia combats.
*/
vector<int> trackers =
{
    0, 0, 0, 0, 0, 0, 0, 0
};

// Re-check army size and update trackers;
void battle_update(battlefield_data &battlefield)
{
    // Update the army.size;
    army_size(battlefield);
    // Update militia and knights;
    trackers[0] = battlefield.kingdoms[0].army.size - battlefield.kingdoms[0].army.knights.size();
    trackers[2] = battlefield.kingdoms[0].army.size - battlefield.kingdoms[0].army.militia.size();
    trackers[1] = battlefield.kingdoms[1].army.size - battlefield.kingdoms[1].army.knights.size();
    trackers[3] = battlefield.kingdoms[1].army.size - battlefield.kingdoms[1].army.militia.size();
}

// Knight vs Knight;
void joust(battlefield_data &battlefield, knight_data knight_one, knight_data knight_two, int victor, bool pause, string &ticker)
{
    write_line(knight_one.prefix + " " + knight_one.name + " of " + battlefield.kingdoms[0].name + " vs " + knight_two.prefix + " " + knight_two.name + " of " + battlefield.kingdoms[1].name);
    if (pause == true)
    {
        write_line("Press the enter key to continue...");
        read_line();
    }
    if (victor == 0)
    {
        ticker = knight_one.prefix + " " + knight_one.name + " has slain " + knight_two.prefix + " " + knight_two.name + "!";
        write_line(knight_one.prefix + " " + knight_one.name + " has slain " + knight_two.prefix + " " + knight_two.name + "!");
    }
    else
    {
        ticker = knight_two.prefix + " " + knight_two.name + " has slain " + knight_one.prefix + " " + knight_one.name + "!";
        write_line(knight_two.prefix + " " + knight_two.name + " has slain " + knight_one.prefix + " " + knight_one.name + "!");
    }
    
}

// Battle test;
void battle(battlefield_data &battlefield)
{
    vector<float> equipment;
    string ticker;
    int combatent_one;
    int combatent_two;
    int casualties_one = 0;
    int casualties_two = 0;
    int r;
    int ticker_counter = 0;
    bool pause;
    bool window = false;
    pause = true;

    // Init vector;
    for (int e = 0; e < 8; e++)
    {
        equipment.push_back(0);
    }

    if (battlefield.kingdoms[0].army.size > 0 and battlefield.kingdoms[1].army.size > 0)
    {
        
        // Init tracker vector to zeros;
        for (int t = 0; t < trackers.size(); t++){trackers[t] = 0;}
        // Init size;
        army_size(battlefield);
        trackers[6] = battlefield.kingdoms[0].army.militia.size() / battlefield.kingdoms[0].army.knights.size();

        // Ready to start the battle;
        write_line("");
        write_line("*** README");
        write_line("You may choose to have pauses between battle steps in which case you must continue each clash manually.");
        write_line("If you have used automake, the numbers can be so large that manual is too slow and not recommended.");
        write_line("Please consider carefully. Pauses enabled can take a long time.");
        pause = read_boolean("Would you like to enable pausing? Y/N: ");
        write_line("");
        write_line("=====THE BATTLE BEGINS=====");
        for (int i = 0; battlefield.kingdoms[0].army.size > 0 or battlefield.kingdoms[1].army.size > 0; i++)
        {
            // Pre-fight updates;
            battle_update(battlefield);

            // Find militia combatent;
            combatent_one = rnd(0, (trackers[0] + 1));
            combatent_two = rnd(0, (trackers[1] + 1));

            // Weight step;
            assign_unit_weight(battlefield.kingdoms[0].army, combatent_one, false);
            assign_unit_weight(battlefield.kingdoms[1].army, combatent_two, false);
            // Adds equipments to vector and loops through it adjusting unit_weight.
            equipment[0] = battlefield.kingdoms[0].army.militia[combatent_one].weapon.item;
            equipment[1] = battlefield.kingdoms[0].army.militia[combatent_one].armour.item;
            equipment[2] = battlefield.kingdoms[0].army.militia[combatent_one].tool.item;
            equipment[3] = battlefield.kingdoms[1].army.militia[combatent_two].weapon.item;
            equipment[4] = battlefield.kingdoms[1].army.militia[combatent_two].armour.item;
            equipment[5] = battlefield.kingdoms[1].army.militia[combatent_two].tool.item;
            equipment[6] = 0;
            equipment[7] = 0;
            weight_adjustment(equipment);
            battlefield.kingdoms[0].army.militia[combatent_one].unit_weight = equipment[6];
            battlefield.kingdoms[1].army.militia[combatent_two].unit_weight = equipment[7];

            // Battle step;
            // If equal match, 50/50;
            if (battlefield.kingdoms[0].army.militia[combatent_one].unit_weight == battlefield.kingdoms[1].army.militia[combatent_two].unit_weight)
            {
                r = rnd();
                battlefield.kingdoms[r].army.militia[combatent_one] = battlefield.kingdoms[r].army.militia[battlefield.kingdoms[0].army.militia.size() - 1];
                battlefield.kingdoms[r].army.militia.pop_back();
                if (r == 0) {trackers[4]++;}
                else {trackers[5]++;}
            // If difference in weight;
            } else if (battlefield.kingdoms[0].army.militia[combatent_one].unit_weight < battlefield.kingdoms[1].army.militia[combatent_two].unit_weight)
            {
                battlefield.kingdoms[0].army.militia[combatent_one] = battlefield.kingdoms[0].army.militia[battlefield.kingdoms[0].army.militia.size() - 1];
                battlefield.kingdoms[0].army.militia.pop_back();
                trackers[4]++;
            } else
            {
                battlefield.kingdoms[1].army.militia[combatent_one] = battlefield.kingdoms[1].army.militia[battlefield.kingdoms[1].army.militia.size() - 1];
                battlefield.kingdoms[1].army.militia.pop_back();
                trackers[5]++;
            }
            
            // Visualiser;
            if (window == false)
            {
                open_window("Kingdom Battle", 1400, 800);
                window = true;
            }
            trackers[7]++;
            // Once a certain amount of militia have battled, knights take a turn to battle;
            if (trackers[7] == trackers[6])
            {
                write_line("---a rank of militia clash---");
                write_line(std::to_string(trackers[4]) + " militia were killed by " + battlefield.kingdoms[0].name + " this round.");
                write_line(std::to_string(trackers[5]) + " militia were killed by " + battlefield.kingdoms[1].name + " this round.");
                casualties_one = casualties_one + trackers[4];
                casualties_two = casualties_two + trackers[5];
                trackers[4] = 0;
                trackers[5] = 0;
                trackers[7] = 0;
                if (pause == true)
                {
                    write_line("Press the enter key to continue...");
                    read_line();
                }
                if (battlefield.kingdoms[0].army.knights.size() > 0 and battlefield.kingdoms[1].army.knights.size() > 0)
                {
                    // As above for knights;
                    combatent_one = rnd(0, (trackers[2]));
                    combatent_two = rnd(0, (trackers[3]));

                    // Weight step;
                    assign_unit_weight(battlefield.kingdoms[0].army, combatent_one, true);
                    assign_unit_weight(battlefield.kingdoms[1].army, combatent_two, true);
                    // Adds equipments to vector and loops through it adjusting unit_weight.
                    equipment[0] = battlefield.kingdoms[0].army.knights[combatent_one].weapon.item;
                    equipment[1] = battlefield.kingdoms[0].army.knights[combatent_one].armour.item;
                    equipment[2] = battlefield.kingdoms[0].army.knights[combatent_one].tool.item;
                    equipment[3] = battlefield.kingdoms[1].army.knights[combatent_two].weapon.item;
                    equipment[4] = battlefield.kingdoms[1].army.knights[combatent_two].armour.item;
                    equipment[5] = battlefield.kingdoms[1].army.knights[combatent_two].tool.item;
                    equipment[6] = 0;
                    equipment[7] = 0;
                    weight_adjustment(equipment);
                    battlefield.kingdoms[0].army.knights[combatent_one].unit_weight = equipment[6];
                    battlefield.kingdoms[1].army.knights[combatent_two].unit_weight = equipment[7];

                    // Battle step;
                    write_line("====two knights approach to duel====");
                    if (battlefield.kingdoms[0].army.knights[combatent_one].unit_weight == battlefield.kingdoms[1].army.knights[combatent_two].unit_weight)
                    {
                        r = rnd();
                        joust(battlefield, battlefield.kingdoms[0].army.knights[combatent_one], battlefield.kingdoms[1].army.knights[combatent_one] , r, pause, ticker);
                        battlefield.kingdoms[r].army.knights[combatent_one] = battlefield.kingdoms[r].army.knights[battlefield.kingdoms[0].army.knights.size() - 1];
                        battlefield.kingdoms[r].army.knights.pop_back();
                        if (r == 0) {casualties_one++;}
                        else {casualties_two++;}
                    } else if (battlefield.kingdoms[0].army.knights[combatent_one].unit_weight < battlefield.kingdoms[1].army.knights[combatent_two].unit_weight)
                    {
                        joust(battlefield, battlefield.kingdoms[0].army.knights[combatent_one], battlefield.kingdoms[1].army.knights[combatent_one] , 1, pause, ticker);
                        battlefield.kingdoms[0].army.knights[combatent_one] = battlefield.kingdoms[0].army.knights[battlefield.kingdoms[0].army.knights.size() - 1];
                        battlefield.kingdoms[0].army.knights.pop_back();
                        casualties_one++;
                    } else
                    {
                        joust(battlefield, battlefield.kingdoms[0].army.knights[combatent_one], battlefield.kingdoms[1].army.knights[combatent_one] , 0, pause, ticker);
                        battlefield.kingdoms[1].army.knights[combatent_one] = battlefield.kingdoms[1].army.knights[battlefield.kingdoms[1].army.knights.size() - 1];
                        battlefield.kingdoms[1].army.knights.pop_back();
                        casualties_two++;
                    }
                }
                execute_step(battlefield, ticker, ticker_counter);
                // If size is great enough to overwhelm;
                if (battlefield.kingdoms[0].army.size > (battlefield.kingdoms[1].army.size * 3.5))
                {
                    write_line(battlefield.kingdoms[0].name + " is overwhelming the enemy!");
                    break;
                }
                else if (battlefield.kingdoms[1].army.size > (battlefield.kingdoms[0].army.size * 3.5))
                {
                    write_line(battlefield.kingdoms[1].name + " is overwhelming the enemy!");
                    break;
                }
            }
        }
        // End combat;
        write_line("-----------------------");
        write_line("And the battle is won!");
        write_line(battlefield.kingdoms[0].name + " lost " + std::to_string(casualties_one) + " troops in combat.");
        write_line(battlefield.kingdoms[1].name + " lost " + std::to_string(casualties_two) + " troops in combat.");
        if (casualties_one < casualties_two) {write_line(battlefield.kingdoms[0].name + "'s army goes on to conquer the lands of " + battlefield.kingdoms[1].name);}
        else {write_line(battlefield.kingdoms[1].name + "'s army goes on to conquer the lands of " + battlefield.kingdoms[0].name);}
        // Clear battlefield and load new;
        bool restart = read_boolean("Would you like to delete your kingdoms and replace them with new ones? Y/N: ");
        if (restart == true)
        {
            battlefield.kingdoms.pop_back();
            battlefield.kingdoms.pop_back();
            load_battlefield(battlefield);
        }
        close_window("Kingdom Battle");
    } else {write_line("No armies to battle! Try again.");}
}

// Selects a single kingdom;
int select_kingdom(battlefield_data &battlefield)
{      
    int select;
    
    select = read_integer("Select a kingdom, either 0 or 1: ");

    while (select != 0 and select != 1)
    {
        select = read_integer("Invalid choice, try again: ");
    }
    return select;
}

// Select to automake either kingdom, or both;
void automake_select(battlefield_data &battlefield)
{
    int select = 0;
    int amount = 0;
    bool both;
    bool quant;

    both = read_boolean("Yes or Y to select only one kingdom to automake, No or N to automake both: ");
    quant = read_boolean("Yes or Y to customize unit quantity, No or N for random: ");
    if (both == true)
    {
        if (quant == true)
        {
            write_line("*** README");
            write_line("How much militia would you like? Knights mount is based on militia amount.");
            write_line("Militia amount is reduced based on input, 5000 will results in 2500 per kingdom.");
            amount = read_integer("Enter the amount of militia: ");
        }
        write_line("Automaking... this can take a few seconds!");
        select = select_kingdom(battlefield);
        automake_kingdom(battlefield, select, amount);
    } else
    {
        select = 2;
        if (quant == true)
        {
            amount = read_integer("How many militia will this kingdom have? Knight amount is based on militia amount: ");
        }
        write_line("Automaking... this can take a few seconds!");
        automake_kingdom(battlefield, select, amount);
    }
    write_line("Automake menu complete, returning...");
}

// Battlefield menu to replace the old main menu;
void battle_menu(battlefield_data &battlefield)
{
    int select;
    select = 0;
    battlefield_options option;
    do
    {
        option = battle_query(battlefield);

        switch(option)
        {
            case AUTOMAKE:
                automake_select(battlefield);
                break;

            case MANAGE:
                select = select_kingdom(battlefield);
                kingdom_menu(battlefield, select);
                break;

            case GRAPH:
                army_analysis(battlefield);
                break;

            case BATTLE:
                battle(battlefield);
                break;

            case EXIT:
                break;

            default:
                write_line("battlefield query has caused an error");
                break;
        }
    } while(option != EXIT);
}
