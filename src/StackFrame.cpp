#include "StackFrame.h"

StackFrame::StackFrame( WORD return_address ){
    this->return_address = return_address;
}

WORD StackFrame::get_return_address(){
    return return_address;
};
WORD StackFrame::get_variable( WORD index ){
    return variables[index];
}