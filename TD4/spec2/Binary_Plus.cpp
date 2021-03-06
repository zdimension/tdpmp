//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Binary_Plus.h"

int Binary_Plus::eval() const
{
    return opl->eval() + opr->eval();
}

std::unique_ptr<const Expr> Binary_Plus::clone() const
{
    return std::make_unique<const Binary_Plus>(*this);
}
