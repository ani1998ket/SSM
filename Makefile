ssm : obj/ main.cpp obj/VM.o
	g++ -std=c++17 -o ssm main.cpp obj/VM.o

obj/ :
	mkdir obj

obj/VM.o : VM.cpp VM.h
	g++ -std=c++17 -c VM.cpp -o obj/VM.o

clean :
	rm -rf obj/
	rm ssm