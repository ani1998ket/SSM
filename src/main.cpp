#include "VM.h"
#include <fstream>
#include <iostream>
#include <vector>

int read_raw_int( std::ifstream& fs ){
    int c = 0;
    char ch;
    int shift = 0;
    while ( fs.get( ch ) && shift < 24 ) {
        c |= (ch & 0xFF) << shift;
        shift += 8;
    }
    return c;
}

std::vector<int> read_bytecode( std::string filename ){
     std::ifstream fs;
    fs.open(filename, std::ifstream::in | std::ifstream::binary );
    if( !fs.is_open() ){
        std::cerr << "Error opening file\n";
        exit(1);
    }
    std::vector<int> program;
    while( !fs.eof() ){
        program.push_back( read_raw_int(fs) );
    }
    return program;
}

int main(int argc, char** argv ){
    if(argc != 2){
        std::cerr << "Usage :\n";
        std::cerr << "\t$ bin/ssm <bytecode_file>" << std::endl;
        return 1;
    }
    std::string filename(argv[1]);
    VM vm;
    vm.reset();
    vm.load_program( read_bytecode(filename) );
    vm.run();
    vm.print_stack();
}


// int main(){
//     VM vm;

//     // 2 + 3
//     vm.reset();
//     vm.load_program({
//         (WORD)OPCODES::PUSH, 2,
//         (WORD)OPCODES::PUSH, 3,
//         (WORD)OPCODES::ADD,
//         (WORD)OPCODES::HALT
//     });
//     vm.run();
//     vm.print_stack();

//     // 3 < 5
//     vm.reset();
//     vm.load_program({
//         (WORD)OPCODES::PUSH, 3,
//         (WORD)OPCODES::PUSH, 4,
//         (WORD)OPCODES::LT,
//         (WORD)OPCODES::HALT
//     });
//     vm.run();
//     vm.print_stack();

//     // x = 3; x = x + 1;
//     vm.reset();
//     vm.load_program({
//         (WORD)OPCODES::PUSH, 3,
//         (WORD)OPCODES::STORE, 0,

//         (WORD)OPCODES::LOAD, 0,
//         (WORD)OPCODES::PUSH, 1,
//         (WORD)OPCODES::ADD,
//         (WORD)OPCODES::STORE, 0,

//         (WORD)OPCODES::LOAD, 0,
//         (WORD)OPCODES::HALT
//     });
//     vm.run();
//     vm.print_stack();

//     // x = 3; if( x < 4 ) x = 1, else x = 0;
//     vm.reset();
//     vm.load_program({
//         (WORD)OPCODES::PUSH, 3,
//         (WORD)OPCODES::PUSH, 4,
//         (WORD)OPCODES::LT,
//         (WORD)OPCODES::JIF, 11,
//         //ELSE
//         (WORD)OPCODES::PUSH, 0,
//         (WORD)OPCODES::JMP, 13,
//         //IF
//         (WORD)OPCODES::PUSH, 1,

//         (WORD)OPCODES::HALT
//     });
//     vm.run();
//     vm.print_stack();

//     // square(t) -> return t*t
//     // x = 10; square(x);
//     vm.reset();
//     vm.load_program({
//         (WORD)OPCODES::PUSH, 10,
//         (WORD)OPCODES::CALL, 5,
//         (WORD)OPCODES::HALT,
//         //square()
//         (WORD)OPCODES::STORE, 0,
//         (WORD)OPCODES::LOAD, 0,
//         (WORD)OPCODES::LOAD, 0,
//         (WORD)OPCODES::MUL,
//         (WORD)OPCODES::RET,
//     });
//     vm.run();
//     vm.print_stack();

//     // add2(t) -> return t + 2
//     // square(t) -> return t*t
//     // x = 10; square( add2(x) );
//     vm.reset();
//     vm.load_program({
//         (WORD)OPCODES::PUSH, 10,
//         (WORD)OPCODES::CALL, 5,
//         (WORD)OPCODES::HALT,
//         //square()
//         (WORD)OPCODES::STORE, 0,
//         (WORD)OPCODES::LOAD, 0,
//         (WORD)OPCODES::CALL, 19,
//         (WORD)OPCODES::STORE, 1,
//         (WORD)OPCODES::LOAD, 1,
//         (WORD)OPCODES::LOAD, 1,
//         (WORD)OPCODES::MUL,
//         (WORD)OPCODES::RET,
//         //add2()
//         (WORD)OPCODES::STORE, 0,
//         (WORD)OPCODES::LOAD, 0,
//         (WORD)OPCODES::PUSH, 2,
//         (WORD)OPCODES::ADD,
//         (WORD)OPCODES::RET,
//     });
//     vm.run();
//     vm.print_stack();
// }