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

// The abstract classes

class Expr
{
public:

    class ZeroDivide : public std::exception
    {
    public:
        const char* what() const throw()
        {
            return "Division by 0";
        }
    };

};


#endif
