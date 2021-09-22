//
// Created by Tom on 13/09/2021.
//

#ifndef TD2_PERSON_H
#define TD2_PERSON_H

#include <string>
#include <optional>
#include <vector>
#include "Gender.h"
#include "PoliceRecord.h"
#include "HealthID.h"

class Person
{
public:
    Person(std::string name, Gender gender, HealthInsuranceOffice& office);

    [[nodiscard]] bool check(bool verbose) const;

    [[nodiscard]] std::string toString() const;

    [[nodiscard]] std::string toStringShort() const;

    [[nodiscard]] Person* getPartner() const;

    void setPartner(Person& partner);

    [[nodiscard]] const std::vector<Person*>& getChildren() const;

    [[nodiscard]] const std::vector<Person*>& getParents() const;

    void addChild(Person& child);

    void divorce();

    bool isSibling(Person& other) const;

    void addPoliceRecord(const PoliceRecord& record);

    [[nodiscard]] const std::vector<PoliceRecord>& getPoliceRecords() const;

    [[nodiscard]] const std::string& getName() const;

    [[nodiscard]] Gender getGender() const;

private:
    std::string name;
    Gender gender;
    Person* partner{};
    std::vector<Person*> children{};
    std::vector<Person*> parents{};
    std::vector<PoliceRecord> policeRecords{};
    HealthID healthID;

    [[nodiscard]] bool checkCycles() const;
};

std::ostream& operator<<(std::ostream& os, const Person& p);


#endif //TD2_PERSON_H
