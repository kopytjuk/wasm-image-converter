#include <fstream>
#include <iostream>
#include <string>

#include "utils.h"

void utils::read_file_to_char_array(std::string fn, char **arr, int &size){

  std::ifstream file (fn, std::ios::in | std::ios::binary | std::ios::ate);

  if (file.is_open())
  {
      size = file.tellg();

      // allocate memory for file
      *arr = new char [size];

      file.seekg (0, std::ios::beg);
      file.read (*arr, size);
      file.close();

  }
}


void utils::print_first_bytes(char *arr, int size){
  for(int i=0; i<size; i++){
    printf("%02hhx ", arr[i]);
  }
  std::cout << std::endl;
}

std::string utils::getExtension(std::string fn){
  return fn.substr(fn.find_last_of("."));
}

void utils::write_char_array_to_file(const std::string fn, char **arr, int &size){
    std::ofstream file (fn, std::ios::out | std::ios::binary);

    if (file.is_open())
    {
        file.write(*arr, size);
        file.close();

    }
}
