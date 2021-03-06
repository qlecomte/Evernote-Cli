/*
 * Auteur : Quentin LECOMTE
 * Date de création : 01/05/2016
 * Date de dernière modification : 18/05/2016
 * Version : 0.2.0
 * Nom de la classe : Notebook
 * Description : Classe pour créer, récupérer et mettre à jour un carnet de note.
 * Licence : Licence GNU GPL v3 - http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <string>

#include <boost/algorithm/string.hpp>

#include "evernote.h"
#include "sdk-evernote/Types_types.h"
namespace en = evernote::edam;

#include "consoleutils.h"
#include "notes.h"

class Notebook
{
public:
    Notebook();
    Notebook(std::string title);
    Notebook(en::Notebook nb);

    std::string getName() const;
    std::string getGuid() const;
    bool isDefault() const;
    Notes getNotes();
    void setName(std::string name);
    void create();

    friend std::ostream& operator << (std::ostream&, const Notebook& notebook);

private:
    en::Notebook notebook;
    Evernote evernote;
};

#endif // NOTEBOOK_H
