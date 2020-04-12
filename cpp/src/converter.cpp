#include "converter.h"

#include <string>
#include <iostream>
#include <sstream> 

#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/io/png.hpp>

using namespace boost::gil;
using namespace std;

enum ImageType {
    PngImage,
    JpegImage,
    UnknownImage
};

ImageType resolveImageType(const string ext){
  if (ext == ".jpg" | ext==".jpeg"){
    return JpegImage;
  } else if (ext == ".png"){
    return PngImage;
  } else {
    return UnknownImage;
  }
}

string getExtension(string fn){
  return fn.substr(fn.find_last_of("."));
}

void convert_image(string inp, string out) {
  
  string input_filename(inp);
  string output_filename(out);

  string inp_ext = getExtension(input_filename);
  string out_ext = getExtension(output_filename);

  ImageType inImageType = resolveImageType(inp_ext);
  ImageType outImageType = resolveImageType(out_ext);

  rgb8_image_t imageData;

  switch (inImageType) {
  case JpegImage:
    read_image( input_filename, imageData, jpeg_tag() );
    break;
  case PngImage:
    read_image( input_filename, imageData, png_tag() );
    break;
  default:
    cout << "Cannot convert input image type! Exiting." << endl;
    break;
  }
  cout << "Successfully read image!" << endl;

  switch (outImageType) {
  case JpegImage:
    write_view(output_filename, view(imageData), jpeg_tag() );
    break;
  case PngImage:
    write_view( output_filename, view(imageData), png_tag() );
    break;
  default:
    cout << "Cannot write to output image type! Exiting." << endl;
    break;
  }

  cout << "Successfully converted image!" << endl;
}


void char_to_image(char *arr, int arr_size, rgb8_image_t &img, ImageType type){

  stringstream arr_stream;
  arr_stream.write(arr, arr_size);
  arr_stream.seekg (0, ios::beg);

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

streampos image_to_arr(rgb8_image_t &img, char *arr, ImageType type){

  stringstream arr_stream;

  switch (type) {
    case JpegImage:
      write_view(arr_stream, view(img), jpeg_tag() );
      break;
    case PngImage:
      write_view( arr_stream, view(img), png_tag() );
      break;
    default:
      cout << "Cannot write to output image type! Exiting." << endl;
      break;
  }

  streampos size;
  size = arr_stream.tellg();

  // allocate memory for file
  arr = new char [size];

  arr_stream.seekg (0, ios::beg);
  arr_stream.read (arr, size);

  return size;
}