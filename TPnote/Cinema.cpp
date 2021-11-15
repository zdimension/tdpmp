//
// Created by Tom on 15/11/2021.
//

#include <random>
#include "Cinema.h"
#include "Client.h"
#include "Siege.h"

void Cinema::reserver(Client& client, Siege& siege)
{
    if (client.parent != this || &siege.parent != this)
    {
        throw InvalidParentException();
    }

    if (client.estPresent())
    {
        throw ExistingReservationException();
    }

    if (!siege.estLibre())
    {
        throw OccupiedSeatException();
    }

    clientsPresents.push_back(&client);
    client.affecterSiege(siege);
    siege.affecterClient(client);
}

Client& Cinema::ajouterClient(const Client& client)
{
    Client& ptr = client.clone();
    ptr.parent = this;
    clients.push_back(&ptr);
    return ptr;
}

Cinema::~Cinema()
{
    // libération des entités allouées dynamiquement
    for (auto siege : places_assises)
    {
        delete siege;
    }

    for (auto client : clients)
    {
        delete client;
    }
}

std::vector<Siege*> Cinema::siegesLibres()
{
    std::vector<Siege*> sieges;
    for (auto siege : places_assises)
    {
        if (siege->estLibre())
        {
            sieges.push_back(siege);
        }
    }
    return sieges;
}

Cinema::Cinema(size_t nb_places_assises)
{
    for (size_t i = 0; i < nb_places_assises; i++)
    {
        places_assises.push_back(new Siege(*this));
    }
}

static std::random_device rd;
static std::mt19937 generator(rd());

Siege& Cinema::siegeLibreAlea()
{
    std::vector<Siege*> sieges = siegesLibres();
    if (sieges.empty())
    {
        throw NoFreeSeatsException();
    }

    std::uniform_int_distribution<size_t> dist(0, sieges.size() - 1);
    return *sieges[dist(generator)];
}

void Cinema::annulerReservation(Client& client)
{
    if (client.parent != this)
    {
        throw InvalidParentException();
    }

    if (!client.estPresent())
    {
        throw MissingReservationException();
    }

    client.siege->liberer();
    client.liberer();

    for (auto it = clientsPresents.begin(); it != clientsPresents.end(); it++)
    {
        if (*it == &client)
        {
            clientsPresents.erase(it);
            break;
        }
    }
}
