//
// Created by Tom on 15/11/2021.
//

#ifndef TPNOTE_SIEGE_H
#define TPNOTE_SIEGE_H

#include "Cinema.h"

class Client;

class Siege
{
public:
    Client* client;

    /**
     * @return true si le siège est libre (n'est réservé par aucun client)
     */
    inline bool estLibre() const
    {
        return client == nullptr;
    }

private:
    Cinema& parent;

    /**
     * Construit une instance de Siege. Ce constructeur est privé et ne doit être utilisé que par le
     * constructeur de Cinema.
     */
    inline explicit Siege(Cinema& parent) : parent(parent), client(nullptr)
    {
    }

    inline void affecterClient(Client& client)
    {
        this->client = &client;
    }

    inline void liberer()
    {
        this->client = nullptr;
    }

    // Seule une réservation est censée pouvoir affecter un client à un siège
    friend void Cinema::reserver(Client& client, Siege& siege);
    friend Cinema::Cinema(size_t nb_places_assises);
    friend void Cinema::annulerReservation(Client& client);
};


#endif //TPNOTE_SIEGE_H
