//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// WTFPL
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#ifndef _UNARY_EXPR_H_
#define _UNARY_EXPR_H_

#include <memory>
#include "Expr.h"

class Unary_Expr : public Expr
{
protected:
    std::unique_ptr<const Expr> op;
public:
    Unary_Expr(const Expr& pe) : op(pe.clone())
    {
    }
};


#endif
