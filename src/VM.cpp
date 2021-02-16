#include "VM.h"

VM::VM() 
{
    reset();
}

void VM::step() 
{
    if( is_halted ) return;
    fetch();
    decode();
    execute();
}

void VM::reset() 
{
    IP = 0;
    is_halted = false;
    opcode = 0;
    stack.clear();
    frame_stack.clear();
    program.clear();
    frame_stack.push_back({0});
}

void VM::load_program( std::vector<WORD> program ){
    this-> program = program;
}

void VM::fetch() 
{
    opcode = program[IP++];   
}

void VM::decode() 
{
    switch ((OPCODES)opcode)
    {
    case OPCODES::PUSH:
    case OPCODES::JMP:
    case OPCODES::JIF:
    case OPCODES::CALL:
    case OPCODES::LOAD:
    case OPCODES::STORE:
        arg = program[IP++];
        break;
    default:
        break;
    }
}

void VM::execute() 
{
    switch ((OPCODES)opcode)
    {
        case OPCODES::NOP:  NOP();      break;
        case OPCODES::HALT: HALT();     break;
        case OPCODES::PUSH: PUSH(arg);  break;
        case OPCODES::POP:  POP();      break;
        case OPCODES::NEG:  NEG();      break;
        case OPCODES::ADD:  ADD();      break;
        case OPCODES::SUB:  SUB();      break;
        case OPCODES::MUL:  MUL();      break;
        case OPCODES::DIV:  DIV();      break;
        case OPCODES::AND:  AND();      break;
        case OPCODES::OR:   OR();       break;
        case OPCODES::XOR:  XOR();      break;
        case OPCODES::NOT:  NOT();      break;
        case OPCODES::GT:   GT();       break;
        case OPCODES::GE:   GE();       break;
        case OPCODES::LT:   LT();       break;
        case OPCODES::LE:   LE();       break;
        case OPCODES::EQ:   EQ();       break;
        case OPCODES::JMP:  JMP(arg);   break;
        case OPCODES::JIF:  JIF(arg);   break;
        case OPCODES::CALL: CALL(arg);  break;
        case OPCODES::RET:  RET();      break;
        case OPCODES::LOAD: LOAD(arg);  break;
        case OPCODES::STORE: STORE(arg);break;
        default:
        break;
    }
}

void VM::NOP() 
{
    
}

void VM::HALT() 
{
    is_halted = true;
}

void VM::PUSH(WORD value) 
{
    stack.push_back( value );   
}

WORD VM::POP() 
{
    WORD value = stack.back();
    stack.pop_back();
    return value;
}

void VM::NEG()
{
    WORD v = POP();
    PUSH( -v ); 
}

void VM::ADD() 
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( v1 + v2 );   
}

void VM::SUB() 
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( v1 - v2 );    
}

void VM::MUL() 
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( v1 * v2 ); 
}

void VM::DIV() 
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( v1 / v2 ); 
}

void VM::AND() 
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( v1 && v2 ); 
}

void VM::OR() 
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( v1 || v2 ); 
}

void VM::XOR() 
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( bool(v1) != bool(v2) ); 
}

void VM::NOT() 
{
    WORD v = POP();
    PUSH( !v ); 
}

void VM::GT() 
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( v1 > v2 ); 
}

void VM::GE() 
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( v1 >= v2 ); 
}

void VM::LT()
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( v1 < v2 );
}

void VM::LE() 
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( v1 <= v2 );
}

void VM::EQ() 
{
    WORD v2 = POP();
    WORD v1 = POP();
    PUSH( v1 == v2 ); 
}

void VM::JMP( UWORD address ) 
{
    IP = address;
}

void VM::JIF( UWORD address ) 
{
    if( POP() ) JMP( address );
}

void VM::CALL( UWORD address ) 
{
    frame_stack.push_back( {IP} );
}

void VM::RET()
{
    IP = frame_stack.back().get_return_address();
    frame_stack.pop_back();
}

void VM::LOAD(int index) 
{
    PUSH( frame_stack.back().get_variable(index) );
}

void VM::STORE(int index) 
{
    frame_stack.back().set_variable( index, POP() );
}

#include <iostream>

void VM::print_stack(){
    std::cout << "Stack : ";
    for( auto e : stack ){
        std::cout << e << ", ";
    } 
    std::cout << std::endl;
}