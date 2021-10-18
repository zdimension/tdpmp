//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================

#include "Unary_Minus.h"

int Unary_Minus::eval() const
{
    return -op->eval();
}

std::unique_ptr<const Expr> Unary_Minus::clone() const
{
    return std::make_unique<const Unary_Minus>(*this);
}
