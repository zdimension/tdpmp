//
// Created by Tom on 20/09/2021.
//

#ifndef TD2_HEALTHINSURANCEOFFICE_H
#define TD2_HEALTHINSURANCEOFFICE_H


#include <vector>

class HealthID;
class Person;

class HealthInsuranceOffice
{
public:
    HealthID& allocate(Person& person);

private:
    std::vector<HealthID> ownedIDs;
    long currentID = 0;
};


#endif //TD2_HEALTHINSURANCEOFFICE_H
