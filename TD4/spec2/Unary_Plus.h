//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// WTFPL
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#ifndef _UNARY_PLUS_H_
#define _UNARY_PLUS_H_

#include "Unary_Expr.h"


class Unary_Plus : public Unary_Expr
{
public:
    Unary_Plus(const Expr& pe) : Unary_Expr(pe)
    {
    }

    Unary_Plus(const Unary_Plus& orig) : Unary_Plus(*orig.op)
    {
    }

    int eval() const override;
    std::unique_ptr<const Expr> clone() const override;
};

#endif
