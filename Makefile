# CLI tool for ubuntu
build: src/main.cpp src/converter.cpp src/converter.h src/utils.cpp src/utils.h
	g++ src/main.cpp src/converter.cpp src/utils.cpp -o build/converter \
	-L/usr/local/boost_1_72_0/stage/lib -I/usr/local/boost_1_72_0/ \
	-lboost_filesystem -lboost_system -ljpeg -lpng
run: build
	./build/converter ./test.jpg ./test.png

# test wasm bild with default html
wasm_main: src/main.cpp src/converter.cpp src/converter.h src/utils.cpp src/utils.h
	emcc --std=c++11 src/main.cpp src/converter.cpp src/utils.cpp \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s USE_BOOST_HEADERS=1 \
	-s USE_ZLIB=1 \
	-s USE_LIBPNG=1 \
	-I include/ \
	-I /usr/include/x86_64-linux-gnu \
	-ljpeg -L include/jpeg-9d/.libs/ -I include/jpeg-9d/ \
	-lz -lpng \
	--preload-file test.jpg \
	-o build_wasm/index.html 

# target for web
wasm_page: src/main.cpp src/converter.cpp src/converter.h src/utils.cpp src/utils.h
	emcc --bind --std=c++11 src/interface.cpp src/converter.cpp src/utils.cpp \
	-s ALLOW_MEMORY_GROWTH=1 \ # for dynamic memory allocation
	-s USE_BOOST_HEADERS=1 \ # use of boost
	-s USE_ZLIB=1 \ # use of zlib
	-s USE_LIBPNG=1 \ # use of libpng
	-I include/ \ # linux and asm headers are required
	-I /usr/include/x86_64-linux-gnu \
	-I include/jpeg-9d/ \ # libjpeg header files
	-ljpeg -L include/jpeg-9d/.libs/ \ # libjpeg static lib
	-lz -lpng \
	 -o ./website/js/wasmconverter.js -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'

clean:
	rm ./test.png
	make 