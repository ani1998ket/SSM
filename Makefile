all : bin/ssm

bin/ssm : obj/ bin/ src/main.cpp obj/VM.o
	g++ -std=c++17 -I src/ -o bin/ssm src/main.cpp obj/VM.o

obj/ :
	mkdir obj

bin/ :
	mkdir bin

obj/VM.o : src/VM.cpp src/VM.h
	g++ -std=c++17 -I src/ -c src/VM.cpp -o obj/VM.o

clean :
	rm -rf obj/ bin/