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
    Unary_Plus(Expr* pe) : Unary_Expr(pe)
    {
    }

    int eval() override;
};

#endif
