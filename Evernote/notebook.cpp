#include "notebook.h"

using namespace std;

Notebook::Notebook()
{}

Notebook::Notebook(string name)
{
    vector<en::Notebook> notebooks = evernote.dlNotebooks();
    for (vector<en::Notebook>::const_iterator it = notebooks.cbegin(); it != notebooks.cend(); ++it){
        if ( boost::iequals(((en::Notebook)*it).name, name)){
            notebook = *it;
        }
    }
}

Notebook::Notebook(en::Notebook nb) : notebook(nb)
{}

string Notebook::getName() const
{
    return notebook.name;
}

string Notebook::getGuid() const
{
    return notebook.guid;
}

bool Notebook::isDefault() const
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

void Notebook::setName(string name)
{
    if (name.length() > (u_int32_t)evernote::limits::g_Limits_constants.EDAM_NOTEBOOK_NAME_LEN_MAX){
        notebook.name = name.substr(0, evernote::limits::g_Limits_constants.EDAM_NOTEBOOK_NAME_LEN_MAX);
    }else{
        notebook.name = name;
    }

    notebook.__isset.name = true;
}

void Notebook::create()
{
    evernote.createNotebook(notebook);
}

ostream& operator << (ostream& os, const Notebook& notebook)
{
    os << ConsoleUtils::boldOn << ConsoleUtils::setColorRed << "Nom : " << ConsoleUtils::resetColor << ConsoleUtils::boldOff;
    os << notebook.getName();
    return os;
}
