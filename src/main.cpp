#include "VM.h"

int main(){
    VM vm;

    // 2 + 3
    vm.reset();
    vm.load_program({
        (WORD)OPCODES::PUSH, 2,
        (WORD)OPCODES::PUSH, 3,
        (WORD)OPCODES::ADD,
        (WORD)OPCODES::HALT
    });
    vm.run();
    vm.print_stack();

    // 3 < 5
    vm.reset();
    vm.load_program({
        (WORD)OPCODES::PUSH, 3,
        (WORD)OPCODES::PUSH, 4,
        (WORD)OPCODES::LT,
        (WORD)OPCODES::HALT
    });
    vm.run();
    vm.print_stack();

    // x = 3; x = x + 1;
    vm.reset();
    vm.load_program({
        (WORD)OPCODES::PUSH, 3,
        (WORD)OPCODES::STORE, 0,

        (WORD)OPCODES::LOAD, 0,
        (WORD)OPCODES::PUSH, 1,
        (WORD)OPCODES::ADD,
        (WORD)OPCODES::STORE, 0,

        (WORD)OPCODES::LOAD, 0,
        (WORD)OPCODES::HALT
    });
    vm.run();
    vm.print_stack();

    // x = 3; if( x < 4 ) x = 1, else x = 0;
    vm.reset();
    vm.load_program({
        (WORD)OPCODES::PUSH, 3,
        (WORD)OPCODES::PUSH, 4,
        (WORD)OPCODES::LT,
        (WORD)OPCODES::JIF, 11,
        //ELSE
        (WORD)OPCODES::PUSH, 0,
        (WORD)OPCODES::JMP, 13,
        //IF
        (WORD)OPCODES::PUSH, 1,

        (WORD)OPCODES::HALT
    });
    vm.run();
    vm.print_stack();

    // square(t) -> return t*t
    // x = 10; square(x);
    vm.reset();
    vm.load_program({
        (WORD)OPCODES::PUSH, 10,
        (WORD)OPCODES::CALL, 5,
        (WORD)OPCODES::HALT,
        //fcall()
        (WORD)OPCODES::STORE, 0,
        (WORD)OPCODES::LOAD, 0,
        (WORD)OPCODES::LOAD, 0,
        (WORD)OPCODES::MUL,
        (WORD)OPCODES::RET,
    });
    vm.run();
    vm.print_stack();
}