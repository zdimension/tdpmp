//
// Created by Tom on 13/09/2021.
//

#include "PoliceRecord.h"

#include <utility>

PoliceRecord::PoliceRecord(std::string fact) : fact(std::move(fact))
{
}

std::ostream& operator<<(std::ostream& os, const PoliceRecord& g)
{
    return os << g.fact;
}
