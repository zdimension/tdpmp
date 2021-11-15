//
// Created by Tom on 15/11/2021.
//

#ifndef TPNOTE_TESTUTILS_H
#define TPNOTE_TESTUTILS_H

#include <cstdarg>

/**
 * Fonction de log simpliste avec affichage d'un statu
 * @param success si le test a echoué ou non
 * @param ... information sur le test
 */
void internal_log(int success, ...)
{
    std::cout << '[' << (success ? "\033[1;32mOK\033[0m" : "\033[1;31mKO\033[0m") << "] ";
    va_list args;
    va_start(args, success);
    while (const char* message = va_arg(args, const char *))
        std::cout << message;
    va_end(args);
    std::cout << std::endl;
}

// Macro permettant d'ajouter le marqueur nullptr après les arguments variadiques
#define log(success, ...) internal_log(success, __VA_ARGS__, nullptr)

// Macro vérifiant qu'un morceau de code déclenche bien une exception du type spécifié
#define should_throw(code, message, type) do \
    {                                  \
        try                             \
        { \
            code; \
            log(false, message " -- aurait dû déclencher une exception"); \
        }                               \
        catch (const type& e)\
        { \
            log(true, message " -- a bien déclenché une exception " #type " (\"", e.what(), "\")"); \
        } \
        catch (const std::exception& e)\
        { \
            log(false, message " -- a déclenché une exception du mauvais type : ", typeid(e).name(), " (\"", e.what(), "\")"); \
        } \
    } while (0)

// Macro vérifiant qu'un morceau de code s'exécute sans exception
#define should_pass(code, message) do \
    {                                    \
        try                             \
        { \
            code; \
            log(true, message " -- s'est bien exécuté sans exception"); \
        }                               \
        catch (const std::exception& e)\
        { \
            log(false, message " -- a échoué et déclenché l'exception : ", typeid(e).name(), " (\"", e.what(), "\")"); \
        } \
    } while (0)

#endif //TPNOTE_TESTUTILS_H
