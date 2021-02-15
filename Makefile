ssm : main.cpp VM.o
	g++ -std=c++17 -o ssm main.cpp VM.o

VM.o : VM.cpp VM.h
	g++ -std=c++17 -c VM.cpp 