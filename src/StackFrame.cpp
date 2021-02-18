#include "StackFrame.h"

StackFrame::StackFrame( u32 return_address ){
    this->return_address = return_address;
}

i32 StackFrame::get_return_address(){
    return return_address;
};

i32 StackFrame::get_variable( u32 index ){
    return variables[index];
}

void StackFrame::set_variable( u32 index, i32 value ){
    variables[index] = value;
}