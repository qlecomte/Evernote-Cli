#ifndef NOTE_H
#define NOTE_H

#include <string>
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

    string getTitle();
    string getContent();
    string getGuid();
    Notebook getNotebook();
    void setTitle(string title);
    void setContent(string title);
    void setNotebook(Notebook notebook);
    void addTag(Tag tag);
    void removeTag(Tag tag);
    void create();

private:
    en::Note note;
    Evernote evernote;
};

#endif // NOTE_H
