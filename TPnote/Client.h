//
// Created by Tom on 15/11/2021.
//

#ifndef TPNOTE_CLIENT_H
#define TPNOTE_CLIENT_H


#include "Personne.h"
#include "Cinema.h"

class Siege;

class Client
{
public:
    virtual int getTarif() = 0;

    const Personne& personne;
    Siege* siege;

    /**
     * Construit un client associé à la personne spécifiée
     */
    inline explicit Client(const Personne& personne) : personne(personne), siege(nullptr), parent(nullptr)
    {
    }

    inline Client(const Client& orig) : personne(orig.personne), siege(nullptr), parent(nullptr)
    {
    }

    /**
     * @return true si le client est présent dans le cinéma (est affecté à un siège)
     */
    inline bool estPresent() const
    {
        return siege != nullptr;
    }

    /**
     * @return une copie de cette instance de Client allouée via new
     */
    virtual Client& clone() const = 0;

    /**
     * Destructeur virtuel car classe abstraite
     */
    virtual ~Client() = default;

private:
    Cinema* parent;

    inline void affecterSiege(Siege& siege)
    {
        this->siege = &siege;
    }

    inline void liberer()
    {
        this->siege = nullptr;
    }

    // Seule une réservation est censée pouvoir affecter un siège à un client
    friend void Cinema::reserver(Client& client, Siege& siege);
    friend Client& Cinema::ajouterClient(const Client& client);
    friend void Cinema::annulerReservation(Client& client);
};


#endif //TPNOTE_CLIENT_H
