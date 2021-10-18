//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Binary_Mult.h"

int Binary_Mult::eval() const
{
    return opl->eval() * opr->eval();
}

std::unique_ptr<const Expr> Binary_Mult::clone() const
{
    return std::make_unique<const Binary_Mult>(*this);
}
