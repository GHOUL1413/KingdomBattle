#ifndef READ_INPUTS
#define READ_INPUTS

#include <string>

/*
* Input prompt, display to user, read input, return string.
*/
string read_string (string prompt);

/*
* Input prompt, display to user, check for valid input, convert and return integer.
*/
int read_integer (string prompt);

/*
* Input prompt, display to user, check for valid input, convert and return double.
*/
double read_double(string prompt);

/*
* Input prompt, display to user, check for valid y/n input, return boolean.
*/
bool read_boolean(string prompt);

#endif
