#include "converter.h"

#include <string>
#include <iostream>
#include <sstream> 

#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/io/png.hpp>

#include "utils.h"

using namespace boost::gil;
using namespace std;


ImageType resolveImageType(const string ext){
  if (ext == ".jpg" | ext==".jpeg"){
    return JpegImage;
  } else if (ext == ".png"){
    return PngImage;
  } else {
    return UnknownImage;
  }
}

void convert_image(char** inp, int& insize, ImageType intype, char** outp, 
  int& outsize, ImageType outtype){

  cout << "Decoding image..." << endl;

  cout << "First 10 bytes: ";
  utils::print_first_bytes(*inp, 10);

  rgb8_image_t imageData;

  char_array_to_image(inp, insize, imageData, intype);

  cout << "Image decoded! Encoding..." << endl;
  
  image_to_char_array(imageData, outtype, outp, outsize);

  cout << "Image encoded to desired format!" << endl;

}

void char_array_to_image(char **arr, int arr_size, rgb8_image_t &img, ImageType type) {
  
  stringstream arr_stream(ios_base::in | ios_base::out | ios_base::binary);
  arr_stream.write(*arr, arr_size);
  arr_stream.seekg(0);

  switch (type) {
    case JpegImage:
      read_image( arr_stream, img, jpeg_tag() );
      break;
    case PngImage:
      read_image( arr_stream, img, png_tag() );
      break;
    default:
      cout << "Cannot convert input image type! Exiting." << endl;
      break;
    }
}

void image_to_char_array(rgb8_image_t &img, ImageType type, char **arr, int &size){

  stringstream arr_stream(ios_base::in | ios_base::out | ios_base::binary);

  switch (type) {
    case JpegImage:
      write_view(arr_stream, view(img), jpeg_tag() );
      break;
    case PngImage:
      write_view(arr_stream, view(img), png_tag() );
      break;
    default:
      cout << "Cannot write to output image type! Exiting." << endl;
      break;
  }

  arr_stream.seekg(0, ios::end);

  size = arr_stream.tellg();

  cout << "Allocating " << to_string(size/1024) << "KB for the output image."<< endl;

  // allocate memory for file
  *arr = new char [size];

  arr_stream.seekg (0, ios::beg);
  arr_stream.read (*arr, size);

}