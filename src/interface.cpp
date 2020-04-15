#include <iostream>
#include <string>
#include <math.h>

#include <emscripten/bind.h>
#include <emscripten/val.h>

#include "converter.h"

ImageType integer_toImageTypeEnum(int x){
    ImageType type;

    switch(x){
    case 0:
        type = JpegImage;
        break;
    case 1:
        type = PngImage;
        break;
    default:
        return type=UnknownImage;
    }
    return type;
}

emscripten::val convert_image_interface(std::string indata, int insize, int informat, int outformat){

    std::cout << "C++ logic is up and running!" << std::endl;

    ImageType intype;
    ImageType outtype;
    
    // we convert to char to match the interface
    char* in = new char[insize];
    for (int i=0;i<insize;i++){
        in[i] = indata[i];
    }

    intype = integer_toImageTypeEnum(informat);
    outtype = integer_toImageTypeEnum(outformat);

    if (intype==UnknownImage | outtype==UnknownImage){
        std::cout << "Conversion not possible! Exiting." << std::endl;
        return emscripten::val::null();
    }

    // declare pointers
    char *outdata;
    int outsize;

    // call conversion logic
    convert_image(&in, insize, intype, &outdata, outsize, outtype);

    // convert from char to uchar
    unsigned char *result = new unsigned char[outsize];
    for (int i=0;i<outsize;i++){
        result[i] = outdata[i];
    }

    // return uint8 array
    return emscripten::val(emscripten::typed_memory_view(outsize, result));
}

// bind c++ function to js Module as Module.convertImage
EMSCRIPTEN_BINDINGS(convertImageExample) {
        emscripten::function("convertImage", &convert_image_interface);
}
