#ifndef CONVERTER_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define CONVERTER_H

#include <string>

using namespace std;

void convert_image(string inp, string out);
char * convert_image(char * data, ImageType inp, ImageType out);

#endif