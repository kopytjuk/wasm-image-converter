build: src/main.cpp src/converter.cpp src/converter.h src/utils.cpp src/utils.h
	g++ -L/usr/local/boost_1_72_0/stage/lib -I/usr/local/boost_1_72_0/ \
	src/main.cpp src/converter.cpp src/utils.cpp -o build/converter \
	-lboost_filesystem -lboost_system -ljpeg -lpng
run: build
	./build/converter ./test.jpg ./test.png
wasm_main: src/main.cpp src/converter.cpp src/converter.h src/utils.cpp src/utils.h
	emcc --std=c++11 src/main.cpp src/converter.cpp src/utils.cpp \
	-s USE_BOOST_HEADERS=1 \
	-s USE_ZLIB=1 \
	-s USE_LIBPNG=1 \
	-I include/ \
	-I /usr/include/x86_64-linux-gnu \
	-ljpeg -L include/jpeg-9d/.libs/ -I include/jpeg-9d/ \
	-lz -lpng \
	 -o build_wasm/index.html --preload-file test.jpg
wasm_page: src/main.cpp src/converter.cpp src/converter.h src/utils.cpp src/utils.h
	emcc --bind --std=c++11 src/interface.cpp src/converter.cpp src/utils.cpp \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s USE_BOOST_HEADERS=1 \
	-s USE_ZLIB=1 \
	-s USE_LIBPNG=1 \
	-I include/ \
	-I /usr/include/x86_64-linux-gnu \
	-ljpeg -L include/jpeg-9d/.libs/ -I include/jpeg-9d/ \
	-lz -lpng \
	 -o ../website/js/wasmconverter.js -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'

clean:
	rm ./test.png
	em++ --clear-cache --clear-ports