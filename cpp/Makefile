build: src/main.cpp src/converter.cpp
	g++ -L/usr/local/boost_1_72_0/stage/lib -I/usr/local/boost_1_72_0/ \
	src/main.cpp src/converter.cpp -o build/converter \
	-lboost_filesystem -lboost_system -ljpeg -lpng
run: build
	./build/converter ./test.jpg ./test.png
wasm: src/main.cpp src/converter.cpp
	emcc --std=c++11 src/main.cpp src/converter.cpp \
	-s USE_BOOST_HEADERS=1 \
	-s USE_ZLIB=1 \
	-I include/jpeg-6b  \
	-I include/ \
	-I /usr/include/x86_64-linux-gnu \
	-lboost_filesystem -lboost_system -ljpeg -lpng -lz \
	 -o build_wasm/converter
	

clean:
	rm ./test.png
	em++ --clear-cache --clear-ports