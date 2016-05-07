#include "evernote.h"

using namespace std;

Evernote::Evernote()
{
    authHttpUser = boost::shared_ptr<apache::thrift::transport::THttpClient>( new apache::thrift::transport::THttpClient("sandbox.evernote.com", 80, "/edam/user") );
    authHttpUser->open();
    boost::shared_ptr<apache::thrift::protocol::TBinaryProtocol> userStoreProt( new apache::thrift::protocol::TBinaryProtocol(authHttpUser) );
    userStore = new en::UserStoreClient(userStoreProt);
    if (!userStore->checkVersion("Evernote-Cli", en::g_UserStore_constants.EDAM_VERSION_MAJOR, en::g_UserStore_constants.EDAM_VERSION_MINOR)){
        cerr << "Your SDK is invalid, please update it" << endl;
    }

    authHttpNote = boost::shared_ptr<apache::thrift::transport::THttpClient>( new apache::thrift::transport::THttpClient("sandbox.evernote.com", 80, "/shard/s1/notestore") );
    authHttpNote->open();
    boost::shared_ptr<apache::thrift::protocol::TBinaryProtocol> noteStoreProt( new apache::thrift::protocol::TBinaryProtocol(authHttpNote) );
    noteStore = new en::NoteStoreClient(noteStoreProt);
}

Evernote::~Evernote() {
    authHttpUser->close();
    authHttpNote->close();
}


en::NotesMetadataList Evernote::dlNotes()
{
    en::NoteFilter filter;

    return dlNotes(filter);
}
en::NotesMetadataList Evernote::dlNotes(en::NoteFilter filter)
{
    en::NotesMetadataList listNotes;
    en::NotesMetadataResultSpec resSpec;
    resSpec.includeTitle = true;
    resSpec.__isset.includeTitle = true;
    try{
        noteStore->findNotesMetadata(listNotes, getAuthToken(), filter, 0, 10, resSpec);
    }catch(en::EDAMUserException e){
        cout << e.errorCode << " : " << e.parameter << endl;
    }catch(en::EDAMSystemException e){
        cout << e.errorCode << " : " << e.message << endl;
    }catch(en::EDAMNotFoundException e){
        cout << e.identifier << " : " << e.key << endl;
    }

    return listNotes;
}

en::Note Evernote::dlNote(string guid)
{
    bool withContent = true;
    bool withResourcesData = false;
    bool withResourcesRecognition = false;
    bool withResourcesAlternateData = false;
    en::Note note;

    noteStore->getNote(note, getAuthToken(), guid, withContent, withResourcesData, withResourcesRecognition, withResourcesAlternateData);

    return note;
}

vector<en::Notebook> Evernote::dlNotebooks()
{
    vector<en::Notebook> notebooks;
    noteStore->listNotebooks(notebooks, getAuthToken());

    return notebooks;
}

en::Notebook Evernote::dlNotebook(string guid)
{
    en::Notebook notebook;
    noteStore->getNotebook(notebook, getAuthToken(), guid);

    return notebook;
}

vector<en::Tag> Evernote::dlTags()
{
    vector<en::Tag> tags;
    noteStore->listTags(tags, getAuthToken());
    return tags;
}

void Evernote::createNote(en::Note note)
{
    try{
        noteStore->createNote(note, getAuthToken(), note);
    }catch (en::EDAMUserException e){
        cerr << e.errorCode << " : " << e.parameter << endl;
    }

}

// Private Functions
string Evernote::getAuthToken()
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("config.ini", pt);

    return pt.get<string>("consumer.developerToken");
}
