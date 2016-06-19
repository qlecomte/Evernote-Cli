/*
 * Auteur : Quentin LECOMTE
 * Date de création : 01/05/2016
 * Date de dernière modification : 18/05/2016
 * Version : 0.2.0
 * Nom de la classe : ConsoleUtils
 * Description : Description : Classe pour récupérer et mettre à jour un ensemble de notes.
 * Licence : Licence GNU GPL v3 - http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef NOTES_H
#define NOTES_H

#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "evernote.h"
#include "sdk-evernote/Types_types.h"
namespace en = evernote::edam;

#include "consoleutils.h"
#include "note.h"

class Notes
{
public:
    Notes();
    Notes(en::NotesMetadataList n);

    Note getNote(std::string title);
    std::vector<std::string> getTitles() const;
    size_t count() const;

    friend std::ostream& operator << (std::ostream&, const Notes& notes);

private:
    en::NotesMetadataList notes;
    Evernote evernote;
};

#endif // NOTES_H
