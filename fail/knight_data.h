/*
* THIS IS THE BEGINNING OF
* unit_data.h
*/
#ifndef UNIT_DATA
#define UNIT_DATA

#include <string>
#include <vector>

/*
* Custom struct to hold data about a knight.
* Holds different data types and is very reusable and customizable.
*/
struct knight_data
{
    string name;
    int age;
    string month;
    string prefix;
    vector<string> equipments;
};

/*
* This enumeration holds the possible responses to the query.
* Answering with an integer corresponds to an entry in the menu.
* Makes code more readable, and can make quick changes to options.
*/
enum update_options
{
    UPDATE_NAME,
    UPDATE_AGE,
    UPDATE_MONTH,
    UPDATE_PREFIX,
    UPDATE_EQUIP,
    UPDATE_FINISH
};

/*
* List of options available at main menu.
*/
enum main_menu_options
{
    GENERATE,
    BATTLE,
    EXIT_MENU
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
* Potential knight names when automaking.
*/
enum knight_names
{
    GALAHAD,
    LANCELOT,
    GAWAIN,
    PERCIVAL,
    LIONEL,
    LYONESS,
    GARETH,
    BEDIVERE,
    BLEOBERIS,
    TAILE,
    LUCAN,
    PALAMEDES,
    LAMORAK,
    GANIS,
    SAFIR,
    PELLEAS,
    KAY,
    MARIS,
    DAGONET,
    BRUNOR,
    INCONNU,
    ALYMORE,
    MORDRED
};

/*
* The kingdom data type holds the name of the kingdom
* as well as all the knights that may exist in this kingdom
* within a vector;
*/
struct kingdom_data
{
    string name;
    vector<knight_data> knights;
};

/*
* Takes user inputted information and makes a knight datatype of it.
*/
knight_data read_knight();

/*
* Add a new equipment to the selected knight.
*/
void add_equipment(kingdom_data &kingdom, int index);

/*
* List equipment with their index, select which ones to remove.
*/
void remove_equipment(kingdom_data &kingdom, int index);

/*
* Lists all of a knights equipments;
*/
void write_equipment(const kingdom_data &kingdom, int index);

/*
* After the user provides initial information before the menu,
* Their information is all written in a greeting. Is also
* used when exiting, showing updated data thanks to referencing.
* Fetches the knight from the kingdom.
*/
void write_knight(const kingdom_data &kingdom, int index);

/*
* User creates a new knight in the kingdom,
* using the pre existing functions
*/
void add_knight(knight_data &kingdom);

/*
* Deletes the selected knight.
*/
void delete_knight(kingdom_data &kingdom, int index);

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
main_menu_options main_query();

/*
* Function that displays the menu options to the user.
* Uses the read_options enum type and returns it to the menu.
*/
update_options update_query(knight_data &knight, int index);

/*
* Menu function that has the do while loop to process for input to update
* different data entries of the knight.
*/
void update_knight(knight_data &knight);

/*
* Processes menu selection options for the main menu.
*/
void main_menu(kingdom_data &kingdom);

#endif
/*
* end of
* unit_data.h
*/