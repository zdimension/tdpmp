//
// Created by Tom on 15/11/2021.
//

#ifndef TPNOTE_CINEMAEXCEPTION_H
#define TPNOTE_CINEMAEXCEPTION_H


#include <exception>
#include <string>

/**
 * Classe de base pour les exceptions déclenchées par les classes liées au cinéma
 */
class CinemaException : public std::exception
{
private:
    std::string message;

public:
    inline explicit CinemaException(std::string message)
    {
        this->message = std::move(message);
    }

    inline const char* what() const noexcept override
    {
        return message.c_str();
    }
};

// Macro de génération rapide d'une classe d'exception
#define EXCEPTION(name, message) class name : public CinemaException { public: inline explicit name() : CinemaException(message) {} }


#endif //TPNOTE_CINEMAEXCEPTION_H
