#include "tag.h"

using namespace std;

Tag::Tag()
{}

Tag::Tag(string name)
{
    vector<en::Tag> tags = evernote.dlTags();
    for (vector<en::Tag>::iterator it = tags.begin(); it != tags.end(); ++it){
        if ( boost::iequals(((en::Tag)*it).name, name)){
            tag = *it;
        }
    }
}

Tag::Tag(evernote::edam::Tag tag) : tag(tag)
{}

string Tag::getName()
{
    return tag.name;
}

string Tag::getGuid()
{
    return tag.guid;
}

Notes Tag::getNotes()
{
    en::NoteFilter filter;
    vector<en::Guid> guids;

    guids.push_back(tag.guid);
    filter.tagGuids = guids;
    filter.__isset.tagGuids = true;

    return Notes(evernote.dlNotes(filter));
}
