#ifndef NOTES_H
#define NOTES_H

#include <string>
#include <vector>
using namespace std;

#include "evernote.h"
#include "sdk-evernote/Types_types.h"
namespace en = evernote::edam;

#include "note.h"

class Notes
{
public:
    Notes();
    Notes(en::NotesMetadataList n);

    Note getNote(string title);
    vector<string> getTitles();
    size_t count();

private:
    en::NotesMetadataList notes;
    Evernote evernote;
};

#endif // NOTES_H
