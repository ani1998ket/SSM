#include "VM.h"

int main(){
    VM vm;
    // !((2+3)-2)
    vm.PUSH(2);
    vm.PUSH(3);
    vm.ADD();
    vm.PUSH(4);
    vm.SUB();
    vm.NOT();
    vm.print_stack();

    // 3 < 5
    vm.reset();
    vm.PUSH(3);
    vm.PUSH(5);
    vm.LT();

    // 1 ^ 2
    vm.reset();
    vm.PUSH(1);
    vm.PUSH(0);
    vm.XOR();
    vm.print_stack();
}