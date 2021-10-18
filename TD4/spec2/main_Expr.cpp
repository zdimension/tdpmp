//=======================================================================
// class Expression
//      Utilization
//-----------------------------------------------------------------------
// Julien DeAntoni (inspired from Jean-Paul Rigault course)
// April 2010
//=======================================================================

#include <iostream>

using namespace std;

#include "Expr.h"
#include "Binary_Div.h"
#include "Binary_Mult.h"
#include "Binary_Plus.h"
#include "Constant.h"
#include "Unary_Minus.h"
#include "Unary_Plus.h"


int main()
{
// deux = 2
    Constant deux = 2;

// trois = 3
    Constant trois = 3;

// quatre = 4
    Constant quatre = 4;

// cinq = 5
    Constant cinq = 5;


// e00 = -3
    Unary_Minus moinsTrois(trois);

// e1 = -3*3
    Binary_Mult e1(trois, moinsTrois);



// e2plus3 = (2 + 3)
    Binary_Plus e2plus3(deux, trois);




// anExpr = (2 + 3)*4
    Binary_Mult anExpr(e2plus3, quatre);

     cout << "3 = "  << trois.eval()  << endl;
     cout << "-3 = " << moinsTrois.eval() << endl;
     cout << "e1 = "  << e1.eval()  << endl;
     cout << "2 + 3 = "  << e2plus3.eval()  << endl;
     cout << "(2 + 3) * 4 = "  << anExpr.eval()  << endl;

}
