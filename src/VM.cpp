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
}

void VM::fetch() 
{
    
}

void VM::decode() 
{
    
}

void VM::execute() 
{

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
    
}

void VM::LOAD(int index) 
{
    
}

void VM::STORE(int index) 
{
    
}

#include <iostream>

void VM::print_stack(){
    std::cout << "Stack : ";
    for( auto e : stack ){
        std::cout << e << ", ";
    } 
    std::cout << std::endl;
}