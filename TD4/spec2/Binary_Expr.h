//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#ifndef _BINARY_EXPR_H_
#define _BINARY_EXPR_H_

#include <memory>
#include "Expr.h"

class Binary_Expr : public Expr
{
protected:
    std::unique_ptr<const Expr> opl;
    std::unique_ptr<const Expr> opr;
public:
    Binary_Expr(const Expr& pe1, const Expr& pe2) : opl(pe1.clone()), opr(pe2.clone())
    {
    }
};

#endif
