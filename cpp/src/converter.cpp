#include "converter.h"

#include <string>
#include <iostream>

#include <boost/filesystem.hpp>
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

void convert_image(string inp, string out) {

  using namespace boost::gil;
  using namespace boost::filesystem;
  
  string input_filename(inp);
  string output_filename(out);

  cout << "Input: " << inp << endl;
  cout << "Output: " << out << endl;

  path inp_filepath(input_filename);
  path out_filepath(output_filename);

  const string inp_ext = inp_filepath.extension().string();
  const string out_ext = out_filepath.extension().string();

  cout << "Input Extension: " << inp_ext << endl;
  cout << "Output Extension: " << out_ext << endl;

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