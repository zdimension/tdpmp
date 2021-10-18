//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Binary_Div.h"

int Binary_Div::eval() const
{
    int right = opr->eval();
    if (right == 0)
        throw ZeroDivide();
    return opl->eval() / right;
}

std::unique_ptr<const Expr> Binary_Div::clone() const
{
    return std::make_unique<const Binary_Div>(*this);
}
