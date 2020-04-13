#ifndef UTILS_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define UTILS_H

#include <fstream>
#include <iostream>
#include <string> 

namespace utils 
{ 
    void read_file_to_char_array(std::string fn, char **arr, int &size);
    void write_char_array_to_file(const std::string fn, char **arr, int &size);
    void print_first_bytes(char *arr, int size);
    std::string getExtension(std::string fn);
}
#endif