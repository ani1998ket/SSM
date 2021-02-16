#include "utils.h"
#include <vector>

class StackFrame{
public:
    StackFrame( WORD return_address );
    WORD get_variable( WORD index );
    WORD get_return_address();
private:
    WORD return_address = 0;
    std::vector<WORD> variables;
};