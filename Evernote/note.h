/*
 * Auteur : Quentin LECOMTE
 * Date de création : 01/05/2016
 * Date de dernière modification : 01/06/2016
 * Version : 0.2.1
 * Nom de la classe : Note
 * Description : Classe pour créer, récupérer et mettre à jour une note.
 * Licence : Licence GNU GPL v3 - http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <iostream>

#include "evernote.h"
#include "sdk-evernote/Types_types.h"
namespace en = evernote::edam;

#include "consoleutils.h"
#include "notebook.h"
#include "tag.h"
#include "resource.h"

class Note
{
public:
    Note();
    Note(std::string guid);
    Note(en::Note n);

    std::string getTitle() const;
    std::string getContent() const;
    std::string getGuid() const;
    Notebook getNotebook();
    void setTitle(std::string title);
    void setContent(std::string title);
    void setNotebook(Notebook notebook);
    void addTag(Tag tag);
    void removeTag(Tag tag);
    void create();
    void downloadMedias();

    friend std::ostream& operator << (std::ostream&, const Note& note);

private:
    en::Note note;
    Evernote evernote;
};




#endif // NOTE_H
