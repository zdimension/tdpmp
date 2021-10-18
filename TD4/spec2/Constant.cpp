//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Constant.h"

int Constant::eval() const
{
    return val;
}

std::unique_ptr<const Expr> Constant::clone() const
{
    return std::make_unique<const Constant>(*this);
}
