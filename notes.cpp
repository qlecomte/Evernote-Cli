#include "notes.h"

Notes::Notes()
{
    notes = evernote.dlNotes();
}

Notes::Notes(en::NotesMetadataList n) : notes(n)
{}

Note Notes::getNote(string title){
    for (vector<en::NoteMetadata>::const_iterator it = notes.notes.cbegin(); it != notes.notes.cend(); ++it){
        if (boost::iequals(((en::NoteMetadata)*it).title, title)){
            return Note(evernote.dlNote(((en::NoteMetadata)*it).guid));
        }
    }

    return Note();
}

vector<string> Notes::getTitles() const{
    vector<string> titles;
    for (vector<en::NoteMetadata>::const_iterator it = notes.notes.cbegin(); it != notes.notes.cend(); ++it){
        titles.push_back(((en::NoteMetadata)*it).title);
    }

    return titles;
}

size_t Notes::count() const{
    return notes.notes.size();
}
