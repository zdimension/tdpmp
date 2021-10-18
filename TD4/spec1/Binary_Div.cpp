//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Binary_Div.h"

int Binary_Div::eval()
{
    int right = opr.eval();
    if (right == 0)
        throw ZeroDivide();
    return opl.eval() / right;
}
