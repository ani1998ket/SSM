#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <unordered_map>

int label_count = 0;
std::unordered_map< std::string, int > label_map;
std::unordered_map< int, std::string > unresolved_labels;
std::vector< int > bytecode;

struct Instruction{
    std::string name;
    int value;
    int arguments;
};

std::vector< Instruction > opcode_table;

void init_table();
void remove_comments( std::string& line );
void remove_whitespace( std::string& line );
void find_opcode( std::string& line );
void find_label( std::string& line );
void resolve_labels();

int main( int argc, char** argv ){

    if( argc != 2 ){
        std::cerr << "Usage: " << argv[0] << " <filename> \n";
        return 1;
    }

    init_table();

    std::string filename = argv[1];
    std::ifstream ifs;
    ifs.open( filename, std::ifstream::in );

    if( !ifs.is_open() ){
        std::cerr << "Error opening: " << filename << "\n";
        return 1;
    }

    std::vector< std::string > input_lines;
    while( !ifs.eof() ){
        std::string line;
        getline( ifs, line );
        remove_comments( line );
        remove_whitespace(line );
        find_label( line );
        find_opcode( line );
        if( line != "")
            input_lines.push_back( line );
    }
    resolve_labels();

    
    std::ofstream ofs;
    ofs.open( "out.sbc" , std::ifstream::out | std::ifstream::binary | std::ifstream::trunc );
    for( auto e : bytecode ){
        int temp = e;
        ofs.write( (char *)&temp, sizeof(int) );
    }

    ifs.close();
    ofs.close();
    return 0;
}

void remove_comments( std::string& line ){
    std::regex r("//.*");
    line = std::regex_replace (line,r, "");
}

void remove_whitespace( std::string& line ){
    std::regex r_front("^[ \t\r\n]+");
    line = std::regex_replace (line,r_front, "");

    std::regex r_between("[ \t\r\n]+");
    line = std::regex_replace (line,r_between, " ");  

    std::regex r_back("[ \t\r\n]+$");
    line = std::regex_replace (line,r_back, "");
}

void find_opcode( std::string& line ){
    if( line == "" ) return;
    std::vector<std::string> tokens;
    std::stringstream ss( line );
    std::string temp;
    while( getline( ss, temp,  ' ') ){
        tokens.push_back( temp );
    }
    if( tokens.size() > 2 ){
        std::cerr << "Syntax error : <opcode> [optional-argument]\n";
        exit(1);
    }

    int i = 0;
    for(; i < opcode_table.size(); i++ ){
        if( opcode_table[i].name == tokens[0] ){

            if( tokens.size() - 1 != opcode_table[i].arguments ){
                std::cerr << "Syntax error : " << tokens[0] << " required " << opcode_table[i].arguments <<" arguments";
                std::cerr << " but provided " << tokens.size() - 1 << ".\n";
                exit(1);
            }

            bytecode.push_back( opcode_table[i].value );
            if( tokens.size() == 2 ){
                switch( opcode_table[i].value ){
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                        unresolved_labels[bytecode.size()] = tokens[1];
                        bytecode.push_back( -1 );
                        break;
                    default:
                        bytecode.push_back( stoi(tokens[1]) );
                        break;
                }
                
            }
            break;
        }
    }
    if( i >= opcode_table.size() ){
        std::cerr << "Syntax error : "<< tokens[0] << " isn't a valid opcode \n";
        exit(1);
    }
}
void find_label( std::string& line ){
    std::regex r("^(.*):");
    if( std::regex_match(line, r) ){
        label_count++;
        label_map[ line.substr(0, line.length() - 1)] = bytecode.size();
        line = std::regex_replace (line,r,"");
    }
}

void resolve_labels(){
    for( auto e : unresolved_labels ){
        int index = e.first;
        std::string label = e.second;
        if( label_map.find(label) == label_map.end() ){
            std::cerr << label << " not found\n";
            exit(1);
        }
        bytecode[index] = label_map[label];
    }
}

void init_table(){
    opcode_table.push_back( {"NOP",     0, 0} );
    opcode_table.push_back( {"HALT",    1, 0} );
    opcode_table.push_back( {"PUSH",    2, 1} );
    opcode_table.push_back( {"POP",     3, 0} );
    opcode_table.push_back( {"NEG",     4, 0} );
    opcode_table.push_back( {"ADD",     5, 0} );
    opcode_table.push_back( {"SUB",     6, 0} );
    opcode_table.push_back( {"MUL",     7, 0} );
    opcode_table.push_back( {"DIV",     8, 0} );
    opcode_table.push_back( {"AND",     9, 0} );
    opcode_table.push_back( {"OR",      10, 0} );
    opcode_table.push_back( {"XOR",     11, 0} );
    opcode_table.push_back( {"NOT",     12, 0} );
    opcode_table.push_back( {"GT",      13, 0} );
    opcode_table.push_back( {"GE",      14, 0} );
    opcode_table.push_back( {"LT",      15, 0} );
    opcode_table.push_back( {"LE",      16, 0} );
    opcode_table.push_back( {"EQ",      17, 0} );
    opcode_table.push_back( {"JMP",     18, 1} );
    opcode_table.push_back( {"JIF",     19, 1} );
    opcode_table.push_back( {"CALL",    20, 1} );
    opcode_table.push_back( {"RET",     21, 0} );
    opcode_table.push_back( {"LOAD",    22, 1} );
    opcode_table.push_back( {"STORE",   23, 1} );
}
