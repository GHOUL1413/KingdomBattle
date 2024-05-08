/*
* THIS IS THE BEGINNING OF
* program.cpp
*/
#include "splashkit.h"
#include "read_inputs.h"
#include "knight_data.h"

int main()
{
    open_window("Kingdom Battle", 1400, 800);

    kingdom_data my_kingdom;
    my_kingdom.name = read_kingdom();

    add_knight(my_kingdom);

    main_menu(my_kingdom);

    write_line("Exiting program...");

    return 0;
}
/*
* THIS IS THE END OF
* program.cpp
*/
