//
// Created by Tom on 15/11/2021.
//

#ifndef TPNOTE_CLIENTOCCASIONNEL_H
#define TPNOTE_CLIENTOCCASIONNEL_H


#include "Client.h"

class ClientOccasionnel : public Client
{
public:
    static const int TARIF = 12;

    inline int getTarif() override
    {
        return TARIF;
    }

    inline explicit ClientOccasionnel(const Personne& personne) : Client(personne)
    {
    }

    inline Client& clone() const override
    {
        return *new ClientOccasionnel(*this);
    }
};


#endif //TPNOTE_CLIENTOCCASIONNEL_H
