#include "note.h"

Note::Note(){}

Note::Note(string guid){
    note = evernote.dlNote(guid);
}

Note::Note(en::Note n) : note(n)
{}

string Note::getTitle(){
    return note.title;
}

string Note::getContent(){
    return note.content;
}

string Note::getGuid(){
    return note.guid;
}

Notebook Note::getNotebook(){
    return Notebook(evernote.dlNotebook(note.notebookGuid).name);
}

void Note::setTitle(string title)
{
    if (title.length() > evernote::limits::g_Limits_constants.EDAM_NOTE_TITLE_LEN_MAX){
        note.title = title.substr(0, evernote::limits::g_Limits_constants.EDAM_NOTE_TITLE_LEN_MAX);
        note.__isset.title = true;
    }else{
        note.title = title;
        note.__isset.title = true;
    }
}

void Note::setContent(string content)
{
    string header = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE en-note SYSTEM \"http://xml.evernote.com/pub/enml2.dtd\"><en-note><div>" ;
    string footer = "<br clear=\"none\"/></div></en-note>";


    note.content = header + content + footer;
    note.__isset.content = true;
}

void Note::setNotebook(Notebook notebook)
{
    note.notebookGuid = notebook.getGuid();
    note.__isset.notebookGuid = true;
}

void Note::addTag(Tag tag)
{
    note.tagGuids.push_back(tag.getGuid());
    note.__isset.tagGuids = true;
}

void Note::removeTag(Tag tag)
{
    for (vector<en::Guid>::iterator it = note.tagGuids.begin(); it != note.tagGuids.end(); ++it){
        if ( *it == tag.getGuid() ){
            note.tagGuids.erase(it);
        }
    }

    if (note.tagGuids.size() == 0){
        note.__isset.tagGuids = false;
    }
}

void Note::create()
{
    evernote.createNote(note);
}
