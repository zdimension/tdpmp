//
// Created by Tom on 13/09/2021.
//

#ifndef TD2_GENDER_H
#define TD2_GENDER_H

#include <iostream>

enum class Gender
{
    Male,
    Female
};

std::ostream& operator<<(std::ostream& os, Gender g);

#endif //TD2_GENDER_H
