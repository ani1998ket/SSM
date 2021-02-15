#pragma once

#include <deque>
#include <cstdint>
#include "VMTester.h"

using BYTE      = int8_t;
using DBYTE     = int16_t;
using WORD      = int32_t;
using DWORD     = int64_t;

using UBYTE     = uint8_t;
using UDBYTE    = uint16_t;
using UWORD     = uint32_t;
using UDWORD    = uint64_t;

class VM{

public:
    VM();
    void step();
    void reset();
    
private:
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
    void EQ();

    void JMP( UWORD address );
    void JIF( UWORD address );

    void CALL( UWORD address );
    void RET();

    void LOAD ( int index );
    void STORE( int index );

    friend class VMTester;
};