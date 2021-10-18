//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Binary_Div.h"

int Binary_Div::eval()
{
    return opl->eval() / opr->eval();
}

std::unique_ptr<Expr> Binary_Div::clone() const
{
    return std::make_unique<Binary_Div>(*this);
}
