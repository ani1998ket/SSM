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
