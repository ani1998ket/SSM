all : bin/sasm

bin/sasm : obj/ bin/ src/main.cpp 
	g++ -std=c++17 -I src/ -o bin/sasm src/main.cpp
	
obj/ :
	mkdir obj

bin/ :
	mkdir bin

clean :
	rm -rf obj/ bin/ out.sbc