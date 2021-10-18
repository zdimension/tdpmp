//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#ifndef _CONDITIONAL_H_
#define _CONDITIONAL_H_

#include <memory>
#include "Expr.h"

class Conditional : public Expr
{
protected:
    std::unique_ptr<const Expr> condition;
    std::unique_ptr<const Expr> opl;
    std::unique_ptr<const Expr> opr;
public:
    Conditional(const Expr& cond, const Expr& pe1, const Expr& pe2) : condition(cond.clone()), opl(pe1.clone()), opr(pe2.clone())
    {
    }

    Conditional(const Conditional& orig) : Conditional(*orig.condition, *orig.opl, *orig.opr)
    {
    }

    int eval() const override;
    std::unique_ptr<const Expr> clone() const override;
};

#endif
