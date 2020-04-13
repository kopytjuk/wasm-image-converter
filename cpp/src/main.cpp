#include <fstream>
#include <iostream>
#include <string> 

#include "converter.h"
#include "utils.h"
 
using namespace std;

 
//int main ( int argc, char *argv[] )
int main ()
{
  //string input_filename(argv[1]);
  //string output_filename(argv[2]);

  string input_filename = "test.jpg";

  char *indata;
  int insize;

  string inext = utils::getExtension(input_filename);
  ImageType intype = resolveImageType(inext);

  utils::read_file_to_char_array(input_filename, &indata, insize);

  // output

  string output_filename = "test.png";

  char *outdata;
  int outsize;

  string outext = utils::getExtension(output_filename);
  ImageType outtype = resolveImageType(outext);

  convert_image(&indata, insize, intype, &outdata, outsize, outtype);

  cout << "Output file: " << to_string(outsize) << "B" << endl;

  utils::write_char_array_to_file(output_filename, &outdata, outsize);

  cout << "Done!" << endl;

  return 0;

  // convert image
  // convert_image(input_filename, output_filename);
}
