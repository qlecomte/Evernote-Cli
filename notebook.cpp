#include "notebook.h"

Notebook::Notebook()
{}

Notebook::Notebook(string name)
{
    vector<en::Notebook> notebooks = evernote.dlNotebooks();
    for (vector<en::Notebook>::iterator it = notebooks.begin(); it != notebooks.end(); ++it){
        if ( boost::iequals(((en::Notebook)*it).name, name)){
            notebook = *it;
        }
    }
}

Notebook::Notebook(en::Notebook nb) : notebook(nb)
{}

string Notebook::getName()
{
    return notebook.name;
}

string Notebook::getGuid()
{
    return notebook.guid;
}

bool Notebook::isDefault()
{
    return notebook.defaultNotebook;
}

Notes Notebook::getNotes()
{
    en::NoteFilter filter;
    filter.notebookGuid = notebook.guid;
    filter.__isset.notebookGuid = true;

    return Notes(evernote.dlNotes(filter));
}
