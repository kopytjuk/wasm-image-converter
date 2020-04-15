# Web assembly 101

[LINK](https://kopytjuk.github.io/wasm-image-converter/website/index.html)

This repo contains a simple image converter using WASM technology and C++ code.

## Hard steps

1. Compilation of `zlib`: Set `#define Z_SOLO` in `zconf.h`
2. Build static library `jpeg-9d`

## Build libjpeg

JPEG_LIB_PATH=include/jpeg-9d
build_jpeg:
	emconfigure $(JPEG_LIB_PATH)/configure
	emmake $(JPEG_LIB_PATH)/make