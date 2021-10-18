//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Binary_Plus.h"

int Binary_Plus::eval()
{
    return opl->eval() + opr->eval();
}

std::unique_ptr<Expr> Binary_Plus::clone() const
{
    return std::make_unique<Binary_Plus>(*this);
}
