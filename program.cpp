#include "splashkit.h"
#include "read_inputs.h"
#include "knight_data.h"

int main()
{
    load_font("arial", "arial.ttf");
    battlefield_data my_battlefield;

    load_battlefield(my_battlefield);

    battle_menu(my_battlefield);

    write_line("Exiting program...");

    return 0;
}
