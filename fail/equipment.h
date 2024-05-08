/*
* THIS IS THE BEGINNING OF
* equipment_data.h
*/
#ifndef EQUIPMENT_DATA
#define EQUIPMENT_DATA

#include "knight_data.h"

#include <string>
#include <vector>

/*
* List of all equipment choices.
*/
enum equipment_type
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
    HELMET,
    STANDARD,
    HORSE
};

/*
* Catagories of equipment used to select and organise unit equipment.
*/
enum equipment_slot
{
    MELEE_WEAPON,
    RANGED_WEAPON,
    ARMOUR_SET,
    MISC_ITEM
};

/*
* Equipment object, includes weight, type and advantage.
*/
struct equipment
{
    equipment_type type;
    equipment_slot slot;
    int weight;
    vector<equipment_slot> advantage;
};

/*
* Assigns weight of equipment dependent on opposing units equipment.
*/
void determine(kingdom_data &kingdom);

/*
* assigned weight
*/
int weight(kingdom_data &kingdom, const equipment_type equipment);

/*
* generate knight
*/
void generate_knights(kingdom_data &kingdom);

#endif
/*
* end of
* equipment_data.h
*/