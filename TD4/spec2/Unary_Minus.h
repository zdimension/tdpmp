//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// WTFPL
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#ifndef _UNARY_MINUS_H_
#define _UNARY_MINUS_H_


#include "Unary_Expr.h"


class Unary_Minus : public Unary_Expr
{
public:
    Unary_Minus(Expr& pe) : Unary_Expr(pe)
    {
    }

    int eval() override;
};


#endif
