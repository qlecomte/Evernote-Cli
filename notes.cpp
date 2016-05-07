#include "notes.h"

Notes::Notes()
{
    notes = evernote.dlNotes();
}

Notes::Notes(en::NotesMetadataList n) : notes(n)
{}

Note Notes::getNote(string title)
{
    for (vector<en::NoteMetadata>::iterator it = notes.notes.begin(); it != notes.notes.end(); ++it){
        if (boost::iequals(((en::NoteMetadata)*it).title, title)){
            return Note(evernote.dlNote(((en::NoteMetadata)*it).guid));
        }
    }

    return Note();
}

vector<string> Notes::getTitles()
{
    vector<string> titles;
    for (vector<en::NoteMetadata>::iterator it = notes.notes.begin(); it != notes.notes.end(); ++it){
        titles.push_back(((en::NoteMetadata)*it).title);
    }

    return titles;
}

size_t Notes::count()
{
    return notes.notes.size();
}
