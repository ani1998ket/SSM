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
    void load_program( std::vector<i32> program );
    void print_stack();

    bool debug_mode = false;
    
private:
    std::deque< i32 > stack;
    std::deque< StackFrame > frame_stack;
    u32 IP;
    i32 opcode, arg;
    bool is_halted;
    std::vector<i32> program;

    void fetch();
    void decode();
    void execute();

    void NOP();
    void HALT();
    void PUSH( i32 value );
    i32 POP();

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

    void JMP( u32 address );
    void JIF( u32 address );

    void CALL( u32 address );
    void RET();

    void LOAD ( int index );
    void STORE( int index );

};