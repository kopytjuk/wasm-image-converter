#include <fstream>
#include <iostream>

#include "converter.h"
 
using namespace std;

// usage converter <input> <output>
 
//int main ( int argc, char *argv[] )
int main ()
{
  
  string input_filename = "test.jpg";
  string output_filename = "test.png";
  //string input_filename(argv[1]);
  //string output_filename(argv[2]);

  // convert image
  convert_image(input_filename, output_filename);
}
