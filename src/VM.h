#pragma once

#include <deque>
#include <vector>
#include "utils.h"
#include "StackFrame.h"

enum class OPCODES{
    NOP = 0, HALT, PUSH, POP,
    NEG, ADD, SUB, MUL, DIV,
    AND, OR, XOR, NOT,
    GT, GE, LT, LE, EQ,
    JMP, JIF,
    CALL, RET,
    LOAD, STORE
};

class VM{

public:
    VM();
    void run();
    void step();
    void reset();
    void load_program( std::vector<WORD> program );
    void print_stack();

    bool debug_mode = false;
    
private:
    std::deque< WORD > stack;
    std::deque< StackFrame > frame_stack;
    UWORD IP;
    bool is_halted;
    WORD opcode, arg;
    std::vector<WORD> program;

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