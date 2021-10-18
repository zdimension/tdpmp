//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// WTFPL
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#ifndef _BINARY_MUL_H_
#define _BINARY_MUL_H_

#include "Binary_Expr.h"


class Binary_Mult : public Binary_Expr
{
public:
    Binary_Mult(Expr& pe1, Expr& pe2) : Binary_Expr(pe1, pe2)
    {
    }

    int eval() override;
};


#endif
