//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// WTFPL
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#ifndef _BINARY_MOD_H_
#define _BINARY_MOD_H_

#include "Binary_Expr.h"


class Binary_Mod : public Binary_Expr
{
public:
    Binary_Mod(const Expr& pe1, const Expr& pe2) : Binary_Expr(pe1, pe2)
    {
    }

    Binary_Mod(const Binary_Mod& orig) : Binary_Mod(*orig.opl, *orig.opr)
    {
    }

    int eval() const override;
    std::unique_ptr<const Expr> clone() const override;
};

#endif
