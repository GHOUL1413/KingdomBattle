#include "splashkit.h"

// Input prompt, display to user, read input, return string;
string read_string(string prompt)
{
    string input;
    write(prompt);
    input = read_line();
    return input;
}

// Input prompt, display to user, check for valid input, convert and return integer;
int read_integer(string prompt)
{
    string input;
    write(prompt);
    input = read_line();
    while (not is_integer(input))
    {
        write_line("Invalid input, please enter a whole number: ");
        input = read_line();
    }
    return convert_to_integer(input);
}

// Input prompt, display to user, check for valid input, convert and return double;
double read_double(string prompt)
{
    string input;
    write(prompt);
    input = read_line();
    while (not is_double(input))
    {
        write("Invalid input, please enter a number: ");
        input = read_line();
    }
    return convert_to_double(input);
}

// Input prompt, display to user, check for valid y/n input, return boolean;
bool read_boolean(string prompt)
{
    string response;
    bool output;
    write(prompt);
    response = read_line();
    response = trim(to_lowercase(response));
    // Defining valid inputs;
    while (response != "yes" and response != "y" and response != "no" and response != "n")
    {
        write("Invalid input, please enter a valid Y/N response: ");
        response = read_line();
        response = trim(to_lowercase(response));
    }
    // Now check users response;
    if (response == "yes" or response == "y")
    {
        output = true;
    } else
    {
        output = false;
    }
    return output;
}
