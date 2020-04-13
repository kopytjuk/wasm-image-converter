#include <iostream>
#include <string>
#include <math.h>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include "converter.h"

extern "C" {
    int int_sqrt(int x) {
        return sqrt(x);
    }
}

emscripten::val convert_image_interface(std::string indata, int insize, int informat, int outformat){

    ImageType intype;
    ImageType outtype;
    
    char* in = new char[insize];
    for (int i=0;i<insize;i++){
        in[i] = indata[i];
    }

    switch(informat){
    case 0:
        intype = JpegImage;
        break;
    case 1:
        intype = PngImage;
        break;
    default:
        cout << "Cannot convert input image type! Exiting." << endl;
        return emscripten::val::null();
    }

    switch(outformat){
    case 0:
        outtype = JpegImage;
        break;
    case 1:
        outtype = PngImage;
        break;
    default:
        cout << "Cannot convert input image type! Exiting." << endl;
        return emscripten::val::null();
    }

    char *outdata;
    int outsize;

    convert_image(&in, insize, intype, &outdata, outsize, outtype);

    unsigned char *result = new unsigned char[outsize];

    // convert from char to uchar
    for (int i=0;i<outsize;i++){
        result[i] = outdata[i];
    }

    return emscripten::val(emscripten::typed_memory_view(outsize, result));
}

// bind c++ function to js Module as Module.convertImage
EMSCRIPTEN_BINDINGS(convertImageExample) {
        emscripten::function("convertImage", &convert_image_interface);
}
