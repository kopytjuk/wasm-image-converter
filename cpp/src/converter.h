#ifndef CONVERTER_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define CONVERTER_H

#include <string>
#include <boost/gil/image.hpp>

using namespace boost::gil;

enum ImageType {
    PngImage,
    JpegImage,
    UnknownImage
};

using namespace std;

void convert_image(string inp, string out);
void convert_image(char** inp, int& insize, ImageType intype, char** outp, int& outsize, ImageType outtype);
ImageType resolveImageType(const string ext);
void char_array_to_image(char **arr, int arr_size, rgb8_image_t &img, ImageType type);
void image_to_char_array(rgb8_image_t &img, ImageType type, char **arr, int &size);

#endif