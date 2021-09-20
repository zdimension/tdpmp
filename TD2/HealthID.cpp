//
// Created by Tom on 20/09/2021.
//

#include "HealthID.h"

HealthID::HealthID(long uid, Person& person) : uid(uid), person(person)
{
}

long HealthID::getUid() const
{
    return uid;
}

Person& HealthID::getPerson() const
{
    return person;
}
