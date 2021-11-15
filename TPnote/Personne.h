//
// Created by Tom on 15/11/2021.
//

#ifndef TPNOTE_PERSONNE_H
#define TPNOTE_PERSONNE_H


#include <string>
#include <utility>

class Personne
{
public:
    std::string nom;

    inline explicit Personne(std::string nom) : nom(std::move(nom))
    {
    }
};


#endif //TPNOTE_PERSONNE_H
