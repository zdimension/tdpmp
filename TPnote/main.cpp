#include <iostream>
#include "Personne.h"
#include "Cinema.h"
#include "ClientOccasionnel.h"
#include "TestUtils.h"
#include "ClientAbonne.h"

int main()
{
    Cinema pathe(100);

    log(pathe.siegesLibres().size() == 100, "Tous les sièges sont bien initialement libres");

    Client& bob_client = pathe.ajouterClient(ClientOccasionnel(Personne("Bob")));
    Client& jim_client = pathe.ajouterClient(ClientAbonne(Personne("Jim")));

    log(bob_client.getTarif() == 12, "Tarif occasionnel est de 12 ?");
    log(jim_client.getTarif() == 7, "Tarif abonné est de 7 ?");

    auto& siege = pathe.siegeLibreAlea();

    should_pass(pathe.reserver(bob_client, siege), "Réservation valide");

    should_throw(pathe.reserver(bob_client, pathe.siegeLibreAlea()), "Réservation en doublon",
                 ExistingReservationException);

    should_throw(pathe.reserver(jim_client, siege), "Réservation sur siège occupé", OccupiedSeatException);

    should_throw(pathe.annulerReservation(jim_client), "Annulation sans réservation", MissingReservationException);

    should_pass(pathe.annulerReservation(bob_client), "Annulation valide");

    should_pass(pathe.reserver(jim_client, siege), "Réservation sur siège libéré");

    should_pass(pathe.reserver(bob_client, pathe.siegeLibreAlea()), "Réservation valide");

    log(pathe.siegesLibres().size() == 98, "98 sièges libres");

    should_pass({
                       for (int i = 0; i < 98; i++)
                       {
                           pathe.reserver(pathe.ajouterClient(ClientAbonne(Personne("Django Fett"))),
                                          pathe.siegeLibreAlea());
                       }
                   }, "98 réservations valides");

    should_throw(pathe.siegeLibreAlea(), "Réservation sur cinéma plein", NoFreeSeatsException);

    should_pass(pathe.annulerReservation(jim_client), "Annulation valide");

    Cinema gaumont(50);

    should_throw(gaumont.reserver(jim_client, gaumont.siegeLibreAlea()),
                 "Réservation d'un client d'un autre cinéma", InvalidParentException);
    should_throw(gaumont.reserver(gaumont.ajouterClient(ClientOccasionnel(Personne("Tim"))), pathe.siegeLibreAlea()),
                 "Réservation d'un siège d'un autre cinéma", InvalidParentException);

    return 0;
}
