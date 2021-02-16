all : bin/ssm

bin/ssm : obj/ bin/ src/main.cpp obj/VM.o obj/StackFrame.o
	g++ -std=c++17 -I src/ -o bin/ssm src/main.cpp obj/VM.o obj/StackFrame.o

obj/ :
	mkdir obj

bin/ :
	mkdir bin

obj/VM.o : src/VM.cpp src/VM.h
	g++ -std=c++17 -I src/ -c src/VM.cpp -o obj/VM.o

obj/StackFrame.o : src/StackFrame.cpp src/StackFrame.h
	g++ -std=c++17 -I src/ -c src/StackFrame.cpp -o obj/StackFrame.o

clean :
	rm -rf obj/ bin/