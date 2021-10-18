//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Constant.h"

int Constant::eval()
{
    return val;
}

std::unique_ptr<Expr> Constant::clone() const
{
    return std::make_unique<Constant>(*this);
}
