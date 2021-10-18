//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Unary_Plus.h"

int Unary_Plus::eval()
{
    return op->eval();
}

std::unique_ptr<Expr> Unary_Plus::clone() const
{
    return std::make_unique<Unary_Plus>(*this);
}
