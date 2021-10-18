//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Binary_Minus.h"

int Binary_Minus::eval() const
{
    return opl->eval() - opr->eval();
}

std::unique_ptr<const Expr> Binary_Minus::clone() const
{
    return std::make_unique<const Binary_Minus>(*this);
}
