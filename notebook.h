#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <string>
using namespace std;

#include "evernote.h"
#include "sdk-evernote/Types_types.h"
namespace en = evernote::edam;

#include "notes.h"

class Notebook
{
public:
    Notebook();
    Notebook(string title);
    Notebook(en::Notebook nb);

    string getName();
    string getGuid();
    bool isDefault();
    Notes getNotes();

private:
    en::Notebook notebook;
    Evernote evernote;
};

#endif // NOTEBOOK_H
