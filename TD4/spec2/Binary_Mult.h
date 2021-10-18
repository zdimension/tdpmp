//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// WTFPL
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#ifndef _BINARY_MUL_H_
#define _BINARY_MUL_H_

#include "Binary_Expr.h"


class Binary_Mult : public Binary_Expr
{
public:
    Binary_Mult(const Expr& pe1, const Expr& pe2) : Binary_Expr(pe1, pe2)
    {
    }

    Binary_Mult(const Binary_Mult& orig) : Binary_Mult(*orig.opl, *orig.opr)
    {
    }

    int eval() const override;
    std::unique_ptr<const Expr> clone() const override;
};


#endif
