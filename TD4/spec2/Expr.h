//=======================================================================
//class Expression
//      Specification and implementation
//-----------------------------------------------------------------------
// WTFPL
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================


#ifndef _EXPR_H_
#define _EXPR_H_

#include <stdexcept>
#include <memory>
#include <iostream>

// The abstract classes

class Expr
{
public:

    class ZeroDivide : public std::exception
    {
    public:
        const char* what() const noexcept
        {
            return "Division by 0";
        }
    };

    virtual int eval() = 0;
    virtual std::unique_ptr<Expr> clone() const = 0;

    virtual ~Expr() = default;
};


#endif
