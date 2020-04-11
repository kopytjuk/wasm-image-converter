build: src/main.cpp
	g++ -L/usr/local/boost_1_72_0/stage/lib -I/usr/local/boost_1_72_0/ \
	src/main.cpp -o build/converter \
	-lboost_filesystem -lboost_system -ljpeg -lpng
run: build
	./build/converter ./test.jpg ./test.png
clean:
	rm ./test.png