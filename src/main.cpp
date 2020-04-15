/*
Command line tool for conversion between different formats.
The tool determines the source and target formats via the file extension.
*/

#include <fstream>
#include <iostream>
#include <string> 

#include "converter.h"
#include "utils.h"
 
using namespace std;

 
int main ( int argc, char *argv[] )
{
  string input_filename(argv[1]);
  string output_filename(argv[2]);

  int insize = utils::filesize(input_filename);
  cout << insize << endl;

  char *indata = new char[insize];

  utils::print_first_bytes(indata, 10);

  string inext = utils::getExtension(input_filename);
  ImageType intype = resolveImageType(inext);

  utils::read_file_to_char_array(input_filename, indata, insize);


  utils::print_first_bytes(indata, 10);

  // output

  char *outdata;
  int outsize;

  string outext = utils::getExtension(output_filename);
  ImageType outtype = resolveImageType(outext);

  convert_image(&indata, insize, intype, &outdata, outsize, outtype);

  cout << "Output file: " << to_string(outsize) << "B" << endl;

  utils::write_char_array_to_file(output_filename, outdata, outsize);

  cout << "Done!" << endl;

  return 0;
}
