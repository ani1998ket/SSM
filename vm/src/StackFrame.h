#pragma once

#include "utils.h"
#include <map>

class StackFrame{
public:
    StackFrame( u32 return_address );

    i32 get_return_address();
    i32 get_variable( u32 index );
    void set_variable( u32 index, i32 value);

private:
    u32 return_address = 0;
    std::map<u32, i32> variables;
};