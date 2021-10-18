//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#include "Binary_Mod.h"

int Binary_Mod::eval() const
{
    return opl->eval() % opr->eval();
}

std::unique_ptr<const Expr> Binary_Mod::clone() const
{
    return std::make_unique<const Binary_Mod>(*this);
}
