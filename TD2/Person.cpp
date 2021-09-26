//
// Created by Tom on 13/09/2021.
//

#include "Person.h"

#include <utility>
#include <iostream>
#include <set>
#include <sstream>


bool Person::check(bool verbose) const
{
    bool result = true;

    auto assert = [verbose, &result](bool condition, const std::string& message)
    {
        result = result && condition;
        if (verbose && !condition)
            std::cerr << "CHECK: " << message << std::endl;
    };

    assert(this->parents.size() <= 2, "More than two parents");

    if (partner != nullptr)
        assert(!isSibling(*partner), "Incestual wedding");
    if (parents.size() == 2)
        assert(!parents.at(0)->isSibling(*parents.at(1)), "Incestual child");

    assert(!this->checkCycles(), "Cycle in genealogical tree");

    return result;
}

std::string Person::toString() const
{
    std::stringstream ss;
    ss << this->toStringShort() << std::endl;

    if (this->parents.empty())
    {
        ss << "De parents inconnus." << std::endl;
    }
    else
    {
        ss << "Enfant de " << this->parents.at(0)->toStringShort();
        if (this->parents.size() == 2)
        {
            ss << " et de " << this->parents.at(1)->toStringShort();
        }
        ss << std::endl;
    }

    if (this->partner)
    {
        ss << "En couple avec " << this->partner->toStringShort() << std::endl;
    }

    if (this->children.empty())
    {
        ss << "Sans enfants." << std::endl;
    }
    else
    {
        ss << "Enfants :" << std::endl;
        for (const auto &item : this->children)
            ss << " - " << item->toStringShort() << std::endl;
    }

    if (policeRecords.empty())
    {
        ss << "Casier vierge." << std::endl;
    }
    else
    {
        ss << "Casier judiciaire :" << std::endl;
        for(const auto &item : this->policeRecords)
            ss << " - " << item << std::endl;
    }

    return ss.str();
}

Person::Person(std::string name, Gender gender, HealthInsuranceOffice& office) :
        name(std::move(name)),
        gender(gender),
        healthID(office.allocate(*this))
{
}

Person* Person::getPartner() const
{
    return partner;
}

void Person::setPartner(Person& other)
{
    if (this->partner)
    {
        this->partner->partner = nullptr;
    }

    this->partner = &other;
    other.partner = this;
}

const std::vector<Person*>& Person::getChildren() const
{
    return children;
}

const std::vector<Person*>& Person::getParents() const
{
    return parents;
}

void Person::addChild(Person& child)
{
    if (this->partner == nullptr)
    {
        std::cerr << "Partner required for child add" << std::endl;
        exit(EXIT_FAILURE);
    }

    this->children.push_back(&child);
    this->partner->children.push_back(&child);
    child.parents.push_back(this);
    child.parents.push_back(this->partner);
}

void Person::divorce()
{
    this->partner->partner = nullptr;
    this->partner = nullptr;
}

bool Person::isSibling(Person& other) const
{
    std::vector<Person*> s3;
    set_intersection(
            parents.begin(), parents.end(),
            other.parents.begin(), other.parents.end(),
            std::back_inserter(s3));
    return !s3.empty();
}

bool Person::checkCycles() const
{
    std::set<const Person*> visited{};
    std::vector<const Person*> toVisit{};

    toVisit.push_back(this);

    while (!toVisit.empty())
    {
        const Person* current = toVisit.back();
        toVisit.pop_back();

        if (visited.contains(current))
        {
            return true;
        }

        visited.insert(current);

        for (Person* child : current->children)
        {
            toVisit.push_back(child);
        }

        for (Person* parent : current->parents)
        {
            toVisit.push_back(parent);
        }
    }

    return false;
}

const std::vector<PoliceRecord>& Person::getPoliceRecords() const
{
    return policeRecords;
}

void Person::addPoliceRecord(const PoliceRecord& record)
{
    policeRecords.push_back(record);
}

std::string Person::toStringShort() const
{
    std::stringstream res;
    res << this->name << " (" << this->gender << ") [" << this->healthID.getUid() << "]";
    return res.str();
}

const std::string& Person::getName() const
{
    return name;
}

Gender Person::getGender() const
{
    return gender;
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    return os << p.toString();
}
