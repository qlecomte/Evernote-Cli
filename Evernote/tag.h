/*
 * Auteur : Quentin LECOMTE
 * Date de création : 07/05/2016
 * Date de dernière modification : 18/05/2016
 * Version : 0.2.0
 * Nom de la classe : ConsoleUtils
 * Description : Description : Classe pour créer, récupérer et mettre à jour des étiquettes.
 * Licence : Licence GNU GPL v3 - http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef TAG_H
#define TAG_H

#include <string>

#include "evernote.h"
#include "sdk-evernote/Types_types.h"
namespace en = evernote::edam;

#include "notes.h"

class Tag
{
public:
    Tag();
    Tag(std::string name);
    Tag(en::Tag tag);

    std::string getName();
    std::string getGuid();
    Notes getNotes();

private:
    en::Tag tag;
    Evernote evernote;
};

#endif // TAG_H
