#include <iostream>
#include "Person.h"

int main()
{
    HealthInsuranceOffice office;

    Person
            charles("Charles", Male, office),
            amandine("Amandine", Female, office);
    charles.setPartner(&amandine);
    Person fred("Fred", Male, office);
    charles.addChildren(&fred);
    charles.divorce();

    Person sylvie("Sylvie", Female, office);
    charles.setPartner(&sylvie);
    Person regis("Régis", Male, office);
    charles.addChildren(&regis);

    Person jeff("Jeff", Male, office);
    amandine.setPartner(&jeff);
    Person
        marie("Marie", Female, office),
        pedro("Pedro", Male, office);
    amandine.addChildren(&marie);
    amandine.addChildren(&pedro);

    marie.setPartner(&regis);
    Person benoit("Benoit", Male, office);
    marie.addChildren(&benoit);

    marie.addPoliceRecord(PoliceRecord("Mangeage de choucroute prohibé"));

    std::cout << marie << std::endl;

    return 0;
}
