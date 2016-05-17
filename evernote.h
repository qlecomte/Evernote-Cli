/*
 * Auteur : Quentin LECOMTE
 * Date de création : 01/05/2016
 * Date de dernière modification : 18/05/2016
 * Version : 0.2.0
 * Nom de la classe : Evernote
 * Description : Classe de gestion pour télécharger et récupérer des informations du SDK Evernote
 * Licence : Licence GNU GPL v3 - http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef EVERNOTE_H
#define EVERNOTE_H

// Thrift headers
#include <transport/THttpClient.h>
#include <protocol/TBinaryProtocol.h>

// Boost headers
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/algorithm/string.hpp>

// Std headers
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// Evernote SDK headers
#include "sdk-evernote/UserStore.h"
#include "sdk-evernote/UserStore_constants.h"
#include "sdk-evernote/NoteStore.h"
#include "sdk-evernote/NoteStore_constants.h"
#include "sdk-evernote/Types_constants.h"
#include "sdk-evernote/Limits_constants.h"
namespace en = evernote::edam;

class Note;
class Notebook;
class Notes;
class Tag;

class Evernote
{
public:
    Evernote();
    ~Evernote();

    en::NotesMetadataList dlNotes();
    en::NotesMetadataList dlNotes(en::NoteFilter filter);
    en::Note dlNote(string guid);
    vector<en::Notebook> dlNotebooks();
    en::Notebook dlNotebook(string guid);
    vector<en::Tag> dlTags();
    void createNote(en::Note note);

private:
    string getAuthToken();

    en::NoteStoreClient* noteStore;
    en::UserStoreClient* userStore;
    boost::shared_ptr<apache::thrift::transport::THttpClient> authHttpUser;
    boost::shared_ptr<apache::thrift::transport::THttpClient> authHttpNote;
};

#endif // EVERNOTE_H
