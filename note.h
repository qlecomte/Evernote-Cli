/*
 * Auteur : Quentin LECOMTE
 * Date de création : 01/05/2016
 * Date de dernière modification : 18/05/2016
 * Version : 0.2.0
 * Nom de la classe : Note
 * Description : Classe pour créer, récupérer et mettre à jour une note.
 * Licence : Licence GNU GPL v3 - http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <iostream>
using namespace std;

#include "evernote.h"
#include "sdk-evernote/Types_types.h"
namespace en = evernote::edam;

#include "notebook.h"
#include "tag.h"



class Note
{
public:
    Note();
    Note(string guid);
    Note(en::Note n);

    string getTitle() const;
    string getContent() const;
    string getGuid() const;
    Notebook getNotebook();
    void setTitle(string title);
    void setContent(string title);
    void setNotebook(Notebook notebook);
    void addTag(Tag tag);
    void removeTag(Tag tag);
    void create();

    friend ostream& operator << (ostream&, const Note& note);

private:
    en::Note note;
    Evernote evernote;
};




#endif // NOTE_H
