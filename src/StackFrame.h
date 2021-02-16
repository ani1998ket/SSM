#include "utils.h"
#include <map>

class StackFrame{
public:
    StackFrame( WORD return_address );
    WORD get_variable( UWORD index );
    void set_variable( UWORD index, WORD value);
    WORD get_return_address();
private:
    WORD return_address = 0;
    std::map<UWORD, WORD> variables;
};