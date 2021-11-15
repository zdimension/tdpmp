//
// Created by Tom on 15/11/2021.
//

#ifndef TPNOTE_CINEMA_H
#define TPNOTE_CINEMA_H


#include <vector>
#include "CinemaException.h"
#include "Personne.h"

class Client;

class Siege;

// Types d'exceptions
EXCEPTION(InvalidParentException, "L'entité n'appartient pas à ce cinéma");

EXCEPTION(MissingReservationException, "Pas de réservation existante");

EXCEPTION(NoFreeSeatsException, "Aucun siège libre");

EXCEPTION(ExistingReservationException, "Une réservation pour ce client existe déjà");

EXCEPTION(OccupiedSeatException, "Le siège est déjà occupé");

class Cinema
{
public:
    // composition, on serait tentés par vector<Siege> mais en réalité on doit faire via des
    // pointeurs, car on souhaite que Client puisse garder une référence vers un Siege
    // or, un vector peut déplacer ses éléments dans la mémoire lors d'une modification
    // on ne peut donc pas faire un vector<Siege> et simplement prendre l'adresse d'un élément
    // -> allocation dynamique
    std::vector<Siege*> places_assises;

    // idem, on aimerait vector<Client> mais Client est une classe abstraite et on ne peut donc pas
    // stocker les instances "telles quelles" car la taille dépend du type dynamique.
    std::vector<Client*> clients;

    /**
     * Crée un cinéma avec le nombre spécifié de places assises
     */
    explicit Cinema(size_t nb_places_assises);

    /**
     * Interdit la copie d'un cinéma (cela n'a pas de sens, et en outre ce n'est pas demandé)
     */
    Cinema(const Cinema&) = delete;

    ~Cinema();

    /**
     * Inscrit un nouvel enregistrement dans la base clients du cinéma
     * @param client par référence car on va le copier via son .clone()
     */
    Client& ajouterClient(const Client& client);

    /**
     * @return la liste des sièges libres (non affectés à un client)
     */
    std::vector<Siege*> siegesLibres();

    /**
     * @return un siège libre tiré au hasard, en référence car il sera plus tard passé à reserver()
     * @throws CinemaException si aucun siège n'est libre
     */
    Siege& siegeLibreAlea();

    /**
     * Enregistre la réservation d'un client pour un siège donné
     * @param client par référence, on doit pouvoir modifier le client, et ici rien ne nous force à utiliser un pointeur
     * @param siege idem
     * @throws CinemaException si le client a déjà réservé un siège, ou si le siège est déjà occupé
     */
    void reserver(Client& client, Siege& siege);

    /**
     * Annule la réservation d'un client
     * @param client idem
     * @throws CinemaException si le client n'a pas de réservation
     */
    void annulerReservation(Client& client);

private:
    // ici, on doit stocker les clients par référence (car ce vecteur ne les possède pas) et on ne peut
    // stocker des références dans un conteneur générique, on stocke donc sous forme de pointeurs
    std::vector<Client*> clientsPresents;
};


#endif //TPNOTE_CINEMA_H
