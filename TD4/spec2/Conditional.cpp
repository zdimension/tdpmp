#include "Conditional.h"

int Conditional::eval() const
{
    return condition->eval() ? opl->eval() : opr->eval();
}

std::unique_ptr<const Expr> Conditional::clone() const
{
    return std::make_unique<const Conditional>(*this);
}
