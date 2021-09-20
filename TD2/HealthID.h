//
// Created by Tom on 20/09/2021.
//

#ifndef TD2_HEALTHID_H
#define TD2_HEALTHID_H


#include "HealthInsuranceOffice.h"

class Person;

class HealthID
{
public:
    HealthID(long uid, Person& person);

    friend HealthID& HealthInsuranceOffice::allocate(Person& person);

    long getUid() const;

    Person& getPerson() const;

private:
    long uid;
    Person& person;
};


#endif //TD2_HEALTHID_H
