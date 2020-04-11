#include <fstream>
#include <iostream>

#include "converter.h"
 
using namespace std;

// usage converter <input> <output>
 
int main ( int argc, char *argv[] )
{
  
  string input_filename(argv[1]);
  string output_filename(argv[2]);

  convert_image(input_filename, output_filename);
}
