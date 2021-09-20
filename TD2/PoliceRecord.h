//
// Created by Tom on 13/09/2021.
//

#ifndef TD2_POLICERECORD_H
#define TD2_POLICERECORD_H


#include <string>

class PoliceRecord
{
public:
    explicit PoliceRecord(std::string fact);

    std::string fact;
};

std::ostream& operator<<(std::ostream& os, const PoliceRecord& g);

#endif //TD2_POLICERECORD_H
