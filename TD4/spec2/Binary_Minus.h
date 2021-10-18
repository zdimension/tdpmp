#ifndef _BINARY_MINUS_H_
#define _BINARY_MINUS_H_

#include "Binary_Expr.h"


class Binary_Minus : public Binary_Expr
{
public:
    Binary_Minus(const Expr& pe1, const Expr& pe2) : Binary_Expr(pe1, pe2)
    {
    }

    Binary_Minus(const Binary_Minus& orig) : Binary_Minus(*orig.opl, *orig.opr)
    {
    }

    int eval() const override;
    std::unique_ptr<const Expr> clone() const override;
};


#endif
