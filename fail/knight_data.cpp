/*
* THIS IS THE BEGINNING OF
* knight_data.cpp
*/
#include "splashkit.h"
#include "read_inputs.h"

#include <vector>

// Data type of all the knights data;
struct knight_data
{
    string name;
    int age;
    string month;
    string prefix;
    vector<string> equipments;
};

// Options available to the update knight;
enum update_options
{
    UPDATE_NAME,
    UPDATE_AGE,
    UPDATE_MONTH,
    UPDATE_PREFIX,
    UPDATE_EQUIP,
    UPDATE_FINISH
};

// Options available to the main menu;
enum main_menu_options
{
    GENERATE,
    BATTLE,
    EXIT_MENU
};

// Options available in the armoury menu;
enum equipment_options
{
    LIST_EQUIP,
    ADD_EQUIP,
    REMOVE_EQUIP,
    EXIT_EQUIP
};

// Make knight name vector;
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

// Data type for all the kingdoms data;
struct kingdom_data
{
    string name;
    vector<knight_data> knights;
};

// Adds a new knight to the kingdom;
knight_data read_knight()
{
    knight_data result;

    result.name = read_string("Enter a name: ");
    result.age = read_integer("Enter an age: ");
    result.month = read_string("Enter a month of birth: ");
    result.prefix = read_string("Enter a knightly prefix: ");
    write_line("To give this knight some equipment, go to the armoury and select them.");

    return result;
}

// Adds equipment to knights inventory (vector);
void add_equipment(kingdom_data &kingdom, int index)
{
    bool more;
    more = true;

    while (more == true)
    {
        kingdom.knights[index].equipments.push_back(read_string("Enter a new equipment: "));
        more = read_boolean("Do you want to add more equipment, yes or no.");
    }
}

/* 
* Lists equipment with indexes and then removes the specified
* equipment based on user input.
*/
void remove_equipment(kingdom_data &kingdom, int index)
{
    int selection;
    bool more;
    more = true;

    if (kingdom.knights[index].equipments.size() == 0)
    {
        write_line("This knight has no equipment to remove!");
        return;
    }
    while (more == true)
    {
        for (int equip = 0; equip < kingdom.knights[index].equipments.size(); equip++)
        {
            write_line(std::to_string(equip + 1) + ". " + kingdom.knights[index].equipments[equip]);
        }
        selection = read_integer("Select equipment to remove: ");
        while (selection <= 0 or selection > kingdom.knights[index].equipments.size())
        {
            selection = read_integer("Invalid selection, try again: ");
        }
        int last_index;
        last_index = kingdom.knights[index].equipments.size() - 1;
        kingdom.knights[index].equipments[selection - 1] = kingdom.knights[index].equipments[last_index];
        kingdom.knights[index].equipments.pop_back();
        more = read_boolean("Do you want to continue removing equipments, yes or no.");
        if (kingdom.knights[index].equipments.size() == 0 and more == true)
        {
            write_line("This knight has no equipment to remove!");
            return;
        }
    }
}

// List of all equipment a knight has. Nested statements to make a neat sentence;
void write_equipment(const kingdom_data &kingdom, int index)
{
    if (kingdom.knights[index].equipments.size() == 0)
    {
        write_line(kingdom.knights[index].prefix + " " + kingdom.knights[index].name + " has no equipment.");
    } else
    {
        write(kingdom.knights[index].prefix + " " + kingdom.knights[index].name + " has the following equipment: ");
        for (int equip = 0; equip < kingdom.knights[index].equipments.size(); equip++)
        {
            if (equip < kingdom.knights[index].equipments.size() - 1)
            {
                write(kingdom.knights[index].equipments[equip] + ", ");
            } else
            {
                write_line("and " + kingdom.knights[index].equipments[equip] + ".");
            }
        }
    }
}

// Display message about a knight and all their details;
void write_knight(const kingdom_data &kingdom, int index)
{
    if (index >= 0 and index < kingdom.knights.size())
    {
        write_line("");
        write_line("This knight is called " + kingdom.knights[index].prefix + " " + kingdom.knights[index].name + " of " + kingdom.name + ".");
        write_line("They are " + std::to_string(kingdom.knights[index].age) + " years old, and were born in the month of " + kingdom.knights[index].month + ".");
        write_equipment(kingdom, index);
    } else
    {
        write_line("!ERROR! Invalid index provided! Try again."); // error for poor index of knight;
    }
}

// Add a new knight to the kingdom;
void add_knight(kingdom_data &kingdom)
{
    knight_data new_knight;
    new_knight = read_knight();
    kingdom.knights.push_back(new_knight);
}

// Deletes a knight from specified index in the vector;
void delete_knight(kingdom_data &kingdom, int index)
{
    if (index >= 0 and index < kingdom.knights.size())
    {
        int last_index;
        last_index = kingdom.knights.size() - 1;
        kingdom.knights[index] = kingdom.knights[last_index];
        kingdom.knights.pop_back();
    } else
    {
        write_line("!ERROR! Invalid index provided! Try again.");
    }
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
    for(int index = 0; index < kingdom.knights.size(); index++)
    {
        write_knight(kingdom, index);
    }
    if (kingdom.knights.size() == 0) write_line("*cricket noises*");
    write_line("+++All Knights of " + kingdom.name + "+++");
    write_line("Press the enter key to continue...");
    read_line();
}

// Display knights and index, user selects by index input;
int select_knight(const kingdom_data &kingdom)
{
    int output;
    
    if (kingdom.knights.size() > 0)
    {
        for (int index = 0; index < kingdom.knights.size();index++)
        {
            write_line(std::to_string(index + 1) + ". " + kingdom.knights[index].name);
        }
        output = read_integer("Which knight will you select: ");

        while (output > kingdom.knights.size())
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
    write_line(kingdom.knights[index].name + " has entered the armoury to change equipment.");
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
main_menu_options main_query()
{
    int result;

    write_line("***");
    write_line("1: Generate");
    write_line("2: Battle");
    write_line("3: Exit program");
    write_line("***");
    result = read_integer("Select an option: ");

    return static_cast<main_menu_options>(result - 1);
}

// List of options to customize and update and existing knight;
update_options update_query(kingdom_data &kingdom, int index)
{
    int result;

    write_line("");
    write_line("===" + kingdom.name +" Barracks Menu===");
    write_line(kingdom.knights[index].name + " has entered the barracks to update their details.");
    write_line("1: Update name");
    write_line("2: Update age");
    write_line("3: Update month of birth");
    write_line("4: Update prefix or title");
    write_line("5: Enter Armoury and change equipments");
    write_line("6: Exit");
    write_line("===" + kingdom.name +" Barracks Menu===");
    result = read_integer("Select an option: ");

    return static_cast<update_options>(result - 1);
}

// Run menu loop for user to make changes to their knight;
void update_knight(kingdom_data &kingdom, int index)
{
    update_options option;

    do
    {
        
        option = update_query(kingdom, index);

        switch(option)
        {
            case UPDATE_NAME:
                kingdom.knights[index].name = read_string("Enter a new name: ");
                break;
            
            case UPDATE_AGE:
                kingdom.knights[index].age = read_integer("Enter a new age: ");
                break;

            case UPDATE_MONTH:
                kingdom.knights[index].month = read_string("Enter a new birth month: ");
                break;

            case UPDATE_PREFIX:
                kingdom.knights[index].prefix = read_string("Enter a new prefix or title: ");
                break;

            case UPDATE_EQUIP:
                armoury_menu(kingdom, index);
                break;

            case UPDATE_FINISH:
                break;

            default:
                write_line("Invalid choice, try again.");
        }
    } while (option != UPDATE_FINISH);
}

// Assign weight;
// int weight(kingdom_data &kingdom, const equipment_type equipment)
// {
//     ;
// }

// Generate;
// void generate_knights(kingdom_data &kingdom)
// {
//     int amount;
//     int name;
//     int weapon;
//     int armour;
//     int misc;
//     int equipment_slot;

//     knight_data new_knight;

//     amount = 2; //rnd(50, 100);
//     name = rnd(0, 21);
//     weapon = rnd(0, 6);
//     armour = rnd(0, 4);
//     misc = rnd(0, 3);

//     while (kingdom.knights.size() < amount)
//     {
//         //name
//         new_knight.name = static_cast<knight_names>(name);

//         //weapon
//         if (weapon <= 3)
//         {
//             new_knight.equipment[equipment_slot].slot = MELEE_WEAPON;
//         } else 
//         {
//             new_knight.equipment[equipment_slot].slot = RANGED_WEAPON;
//         }
//         new_knight.equipment[equipment_slot].type = static_cast<equipment_type>(weapon);
        
//         //armour

//         //misc


//         kingdom.knights.push_back(new_knight);
//     }
// }

// Display options menu to the user first entering the program. This is the topmost menu;
void main_menu(kingdom_data &kingdom)
{
    main_menu_options option;
    //int query;

    do
    {
        
        option = main_query();

        switch(option)
        {
            case GENERATE:
                break;

            case BATTLE:
                break;
            
            case EXIT_MENU:
                break;

            default:
                write_line("Invalid choice, try again.");
        }
    } while (option != EXIT_MENU);
}

/*
* end of
* knight_data.cpp
*/