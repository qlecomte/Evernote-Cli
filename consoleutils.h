/*
 * Auteur : Quentin LECOMTE
 * Date de création : 17/05/2016
 * Date de dernière modification : 18/05/2016
 * Version : 0.2.0
 * Nom de la classe : ConsoleUtils
 * Description : Des fonctions utiles pour mettre en forme le texte dans une sortie console.
 * Licence : Licence GNU GPL v3 - http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef CONSOLEUTILS_H
#define CONSOLEUTILS_H

#include <iostream>

namespace ConsoleUtils
{
    inline std::ostream &boldOn(std::ostream& os){
        return os << "\e[1m";
    }
    inline std::ostream &boldOff(std::ostream& os){
        return os << "\e[0m";
    }

    inline std::ostream &setColorRed(std::ostream& os){
        return os << "\e[31m";
    }
    inline std::ostream &setColorGreen(std::ostream& os){
        return os << "\e[32m";
    }
    inline std::ostream &setColorYellow(std::ostream& os){
        return os << "\e[33m";
    }
    inline std::ostream &setColorBlue(std::ostream& os){
        return os << "\e[34m";
    }
    inline std::ostream &setColorMagenta(std::ostream& os){
        return os << "\e[35m";
    }
    inline std::ostream &setColorCyan(std::ostream& os){
        return os << "\e[36m";
    }

    inline std::ostream &resetColor(std::ostream& os){
        return os << "\e[0;39m" ;
    }

}

#endif // CONSOLEUTILS_H
