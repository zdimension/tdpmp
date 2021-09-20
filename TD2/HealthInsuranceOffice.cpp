//
// Created by Tom on 20/09/2021.
//

#include "HealthInsuranceOffice.h"
#include "HealthID.h"

HealthID& HealthInsuranceOffice::allocate(Person& person)
{
    HealthID id(currentID++, person);
    ownedIDs.push_back(id);
    return ownedIDs.back();
}
