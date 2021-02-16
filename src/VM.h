#pragma once

#include <deque>
#include "utils.h"

class VM{

public:
    VM();
    void step();
    void reset();
    void print_stack();
    
private:
public:
    std::deque< WORD > stack;
    UWORD IP;
    bool is_halted;
    WORD opcode;

    void fetch();
    void decode();
    void execute();

    void NOP();
    void HALT();
    void PUSH( WORD value );
    WORD POP();

    void NEG();
    void ADD();
    void SUB();
    void MUL();
    void DIV();
    void AND();
    void OR();
    void XOR();
    void NOT();

    void GT();
    void GE();
    void LT();
    void LE();
    void EQ();

    void JMP( UWORD address );
    void JIF( UWORD address );

    void CALL( UWORD address );
    void RET();

    void LOAD ( int index );
    void STORE( int index );

};