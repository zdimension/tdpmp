#include <iostream>
#include "Person.h"

int main()
{
    HealthInsuranceOffice office;

    Person
            charles("Charles", Gender::Male, office),
            amandine("Amandine", Gender::Female, office);
    charles.setPartner(amandine);
    Person fred("Fred", Gender::Male, office);
    charles.addChild(fred);
    charles.divorce();

    Person sylvie("Sylvie", Gender::Female, office);
    charles.setPartner(sylvie);
    Person regis("Régis", Gender::Male, office);
    charles.addChild(regis);

    Person jeff("Jeff", Gender::Male, office);
    amandine.setPartner(jeff);
    Person
        marie("Marie", Gender::Female, office),
        pedro("Pedro", Gender::Male, office);
    amandine.addChild(marie);
    amandine.addChild(pedro);

    marie.setPartner(regis);
    Person benoit("Benoit", Gender::Male, office);
    marie.addChild(benoit);

    marie.addPoliceRecord(PoliceRecord("Mangeage de choucroute prohibé"));

    std::cout << marie << std::endl;

    std::cout << marie.check(true) << std::endl;

    marie.addChild(amandine);

    std::cout << marie.check(true) << std::endl;

    return 0;
}
