/*
* THIS IS THE BEGINNING OF
* knight_data.h
*/
#ifndef KNIGHT_DATA
#define KNIGHT_DATA

#include <string>
#include <vector>

/*
* This enumeration holds the possible responses to the query.
* Answering with an integer corresponds to an entry in the menu.
* Makes code more readable, and can make quick changes to options.
*/
enum knight_options
{
    UPDATE_NAME,
    UPDATE_PREFIX,
    UPDATE_EQUIP,
    UPDATE_FINISH
};

/*
* Options for adding, editing and removing equipment from a knight.
*/
enum equipment_options
{
    LIST_EQUIP,
    ADD_EQUIP,
    REMOVE_EQUIP,
    EXIT_EQUIP
};

/*
* List of options available at main menu.
*/
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

/*
* Battlefield options.
*/
enum battlefield_options
{
    AUTOMAKE,
    MANAGE,
    GRAPH,
    BATTLE,
    EXIT
};

/*
* List of all equipments a unit can have.
*/
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

/*
* An equipment has a name, some stats, and a slot it takes.
* A knight has three slots, so three total equipments.
* Each equipment has stats that are considered during simulation.
*/
struct equipment_data
{
    equipment_list item;
    float weight;
    string slot;
};

/*
* Custom struct to hold data about a knight.
* Holds different data types and is very reusable and customizable.
* Militia is the same but with a class, and no name or prefix.
*/
struct knight_data
{
    string name;
    string prefix;
    equipment_data weapon;
    equipment_data armour;
    equipment_data tool;
    float unit_weight;
};

struct militia_data
{
    equipment_data weapon;
    equipment_data armour;
    equipment_data tool;
    int unit_weight;
};

/*
* Holds knights and militia.
*/
struct army_data
{
    int size;
    vector<knight_data> knights;
    vector<militia_data> militia;
};

/*
* The kingdom data type holds the name of the kingdom
* as well as all the knights that may exist in this kingdom
* within a vector;
*/
struct kingdom_data
{
    string name;
    army_data army;
    color color;
};

/*
* Holds kingdoms for easier comparisons and simulations.
* Intended to only hold two kingdoms.
*/
struct battlefield_data
{
    vector<kingdom_data> kingdoms;
};

/*
* Automake functions for each tool type.
*/
equipment_list create_weapon();
equipment_list create_armour();
equipment_list create_tool();

/*
* Tediouslly assigns a unit (militia and knights) weight.
* This is the default weight assigned for each weapon.
* May need rework.
*/
int assign_unit_weight(army_data army, int index, bool knight);

/*
* Automatically makes new equips for a unit.
*/
void automake_equipment(kingdom_data &kingdom, int index, bool is_knight);

/*
* Takes user inputted information and makes a knight datatype of it.
*/
knight_data read_knight();

/*
* Add a new equipment to the selected knight.
*/
void add_equipment(kingdom_data &kingdom, int index);

/*
* to be removed.
*/
void remove_equipment(kingdom_data &kingdom, int index);

/*
* Lists all of a knights equipments;
*/
void write_equipment(const kingdom_data &kingdom, int index);

/*
* User creates a new knight in the kingdom,
* using the pre existing functions
*/
void add_knight(kingdom_data &kingdom);

/*
* Deletes the selected knight.
*/
void delete_knight(kingdom_data &kingdom, int index);

/*
* After the user provides initial information before the menu,
* Their information is all written in a greeting. Is also
* used when exiting, showing updated data thanks to referencing.
* Fetches the knight from the kingdom.
*/
void write_knight(const kingdom_data &kingdom, int index);

/*
* Coming soon
*/
void select_equipment(kingdom_data &kingdom);

/*
*Makes a new militia will all random details.
*/
void automake_militia(kingdom_data &kingdom);

/*
* Makes a new knight will all random details.
*/
void automake_knight(kingdom_data &kingdom);

/*
* The user will give their kingdom a custom name.
*/
string read_kingdom();

/*
* Tells the user every knight in the kingdom.
*/
void write_kingdom(const kingdom_data &kingdom);

/*
* Lists knights and their index, user enters index to select.
* Is used to find knight before editing, writing, or deleting.
*/
int select_knight(const kingdom_data &kingdom);

/*
* Displays list of options to user.
* List, add, or remove equipments from selected knight.
*/
equipment_options armoury_query(kingdom_data &kingdom, int index);

/*
* Handles user response to armoury options.
* List, add, or remove equipments from selected knight.
*/
void armoury_menu(kingdom_data &kingdom, int index);

/*
* Lists main menu options to user.
*/
kingdom_menu_options kingdom_query(kingdom_data &kingdom);

/*
* Function that displays the menu options to the user.
* Uses the read_options enum type and returns it to the menu.
*/
knight_options update_query(knight_data &knight, int index);

/*
* Finds the size of the army of the kingdom.
*/
void army_size(battlefield_data &battlefield);

/*
* Lists options to select for battfield menu.
*/
battlefield_options battle_query(battlefield_data &battlefield);

/*
* Menu function that has the do while loop to process for input to update
* different data entries of the knight.
*/
void update_knight(knight_data &knight);

/*
* Lists all names and prefixes of knights in given kingdom.
*/
void find_names(kingdom_data &kingdom);

/*
* Lists all equipments of knights and militia in given kingdom
*/
void find_equipment(kingdom_data &kingdom);

/*
* Processes menu selection options for the main menu.
*/
void kingdom_menu(kingdom_data &kingdom);

/*
* Fills a kingdom.army with random amount of militia,
* then finds a ratio with zero remainders of knights.
* Then assigns each new unit with random equipment.
*/
void automake_kingdom(battlefield_data &battlefield, int select, int amount);

/*
* Ensure there are two kingdoms, named,
* add added to the battlefield.
*/
void load_battlefield(battlefield_data &battlefield);

/*
* Finds the equipment weight vs equipment.
*/
float weight_adjustment(vector<float> &to_check);

/*
* Draws bars representing weapons.
*/
void make_bars(float x, float y, float w, float h, color color);

/*
* Makes bars for every units equipment and compares.
*/
void army_analysis(battlefield_data &battlefield);

/*
* Measures the screen, displays graphics to represent
* militia strength. Colour coded.
*/
void draw_army(battlefield_data &battlefield);

/*
* Refresh and render to screen.
*/
void execute_step(battlefield_data &battlefield, string ticker, int &ticker_counter);

/*
* Extra step every battle to update some trackers and the current army size.
*/
void battle_update(battlefield_data &battlefield);

/*
* Specific knight vs knight combat displaying names.
*/
void joust(battlefield_data &battlefield, knight_data knight_one, knight_data knight_two, int victor, bool pause);

/*
* Meat and potatoes procedure to check units against other units in battle.
* Will remove units until there is a clear victor.
* The losing kingdom is destroyed after the battle.
*/
void battle(battlefield_data &battlefield);

/*
* Select a kingdom, used to enter management menu.
*/
int select_kingdom(battlefield_data &battlefield);

/*
* Check which or both kingdoms to automake.
* Needs additional features.
*/
void automake_select(battlefield_data &battlefield);

/*
* User can manage kingdoms and battle them.
*/
void battle_menu(battlefield_data &battlefield);

#endif
/*
* end of
* knight_data.h
*/