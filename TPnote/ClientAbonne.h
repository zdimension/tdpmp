//
// Created by Tom on 15/11/2021.
//

#ifndef TPNOTE_CLIENTABONNE_H
#define TPNOTE_CLIENTABONNE_H


#include "Client.h"

/**
 * Client abonné au cinéma. Tarif réduit.
 */
class ClientAbonne : public Client
{
public:
    static const int TARIF = 7;

    inline int getTarif() override
    {
        return TARIF;
    }

    inline explicit ClientAbonne(const Personne& personne) : Client(personne)
    {
    }

    inline Client& clone() const override
    {
        return *new ClientAbonne(*this);
    }
};


#endif //TPNOTE_CLIENTABONNE_H
