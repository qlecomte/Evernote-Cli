#ifndef TAG_H
#define TAG_H

#include <string>
using namespace std;

#include "evernote.h"
#include "sdk-evernote/Types_types.h"
namespace en = evernote::edam;

#include "notes.h"

class Tag
{
public:
    Tag();
    Tag(string name);
    Tag(en::Tag tag);

    string getName();
    string getGuid();
    Notes getNotes();

private:
    en::Tag tag;
    Evernote evernote;
};

#endif // TAG_H
