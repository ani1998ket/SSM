#include "VM.h"
#include <fstream>
#include <iostream>
#include <vector>

int read_raw_int( std::ifstream& fs ){
    int c = 0;
    char ch;
    int shift = 0;
    // little endian encoding
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
    fs.close();
    return program;
}
std::vector<int> read_txt( std::string filename ){
     std::ifstream fs;
    fs.open(filename, std::ifstream::in | std::ifstream::binary );
    if( !fs.is_open() ){
        std::cerr << "Error opening file\n";
        exit(1);
    }
    std::vector<int> program;
    while( !fs.eof() ){
        int temp;
        fs >> temp;
        program.push_back(temp);
    }
    fs.close();
    return program;
}

int main(int argc, char** argv ){
    std::string filename;
    std::vector<int> program;

    if( argc == 2 && strcmp(argv[1], "-t") != 0){
        filename = argv[1];
        program = read_bytecode( filename );
    }
    else if( argc == 3 && strcmp(argv[1], "-t") == 0 ){
        filename = argv[2];
        program = read_txt( filename );
    }
    else{
        std::cerr << "Usage : ";
        std::cerr << "bin/ssm [options] <bytecode_file> \n\n";
        std::cerr << "Options : \n";
        std::cerr << "\t-t \t\t Run text file equivalent of the bytecode" << std::endl;
        return 1;
    }

    VM vm;
    vm.reset();
    vm.load_program( program );
    vm.run();
    vm.print_stack();
}
