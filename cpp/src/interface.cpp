#include <iostream>
#include <math.h>

#include "converter.h"

extern "C" {

    int int_sqrt(int x) {
        return sqrt(x);
    }

    int convert_image(char *in, int insize, int informat, int outformat){
        ImageType intype;
        ImageType outtype;

        switch(informat){
        case 0:
            intype = JpegImage;
            break;
        case 1:
            intype = PngImage;
            break;
        default:
            cout << "Cannot convert input image type! Exiting." << endl;
            return -1;
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
            return -1;
        }

        char *outdata;
        int outsize;

        convert_image(&in, insize, intype, &outdata, outsize, outtype);
        return 0;
    }

}
