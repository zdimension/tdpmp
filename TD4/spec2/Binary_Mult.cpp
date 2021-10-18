//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Binary_Mult.h"

int Binary_Mult::eval()
{
    return opl->eval() * opr->eval();
}

std::unique_ptr<Expr> Binary_Mult::clone() const
{
    return std::make_unique<Binary_Mult>(*this);
}
