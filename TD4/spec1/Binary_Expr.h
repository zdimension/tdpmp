//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#ifndef _BINARY_EXPR_H_
#define _BINARY_EXPR_H_

#include "Expr.h"

class Binary_Expr : public Expr
{
protected:
    ??
    opl;
    ??
    opr;
public:
    Binary_Expr(Expr* pe1, Expr* pe2) : opl(pe1), opr(pe2)
    {
    }
};

#endif
