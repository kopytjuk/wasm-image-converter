#include "converter.h"

#include <string>
#include <iostream>

#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/io/io.hpp>
#include <boost/gil/extension/io/jpeg.hpp>
#include <boost/gil/extension/io/png.hpp>

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

  using namespace boost::gil;
  
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