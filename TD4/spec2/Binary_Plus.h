//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// WTFPL
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#ifndef _BINARY_PLUS_H_
#define _BINARY_PLUS_H_

#include "Binary_Expr.h"


class Binary_Plus : public Binary_Expr
{
public:
    Binary_Plus(const Expr& pe1, const Expr& pe2) : Binary_Expr(pe1, pe2)
    {
    }

    Binary_Plus(const Binary_Plus& orig) : Binary_Plus(*orig.opl, *orig.opr)
    {
    }

    int eval() const override;
    std::unique_ptr<const Expr> clone() const override;
};


#endif
