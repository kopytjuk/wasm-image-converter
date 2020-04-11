#include <fstream>
#include <iostream>
#include <string>

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

ImageType resolveImageType(string input);

// usage converter <input> <output>
 
int main ( int argc, char *argv[] )
{
  using namespace boost::gil;
  using namespace boost::filesystem;
  
  string input_filename(argv[1]);
  string output_filename(argv[2]);

  cout << "Input: " << input_filename << endl;
  cout << "Output: " << output_filename << endl;

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
    return 0;
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
    return 0;
    break;
  }

  cout << "Successfully converted image!" << endl;

}

ImageType resolveImageType(const string ext){
  if (ext == ".jpg" | ext==".jpeg"){
    return JpegImage;
  } else if (ext == ".png"){
    return PngImage;
  } else {
    return UnknownImage;
  }
}