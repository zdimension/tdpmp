//
// Created by Tom on 13/09/2021.
//

#include "Gender.h"

#include <iostream>

std::ostream& operator<<(std::ostream& os, Gender g)
{
    switch(g)
    {
        case Male:
            return os << "Masculin";
        case Female:
            return os << "Féminin";
        default:
            return (os.setstate(std::ios_base::failbit), os);
    }
}
