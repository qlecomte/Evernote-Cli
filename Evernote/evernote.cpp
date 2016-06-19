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

Evernote::~Evernote()
{
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
        cout << getErrorString(e.errorCode) << " : " << e.parameter << endl;
    }catch(en::EDAMSystemException e){
        cout << getErrorString(e.errorCode) << " : " << e.message << endl;
    }catch(en::EDAMNotFoundException e){
        cout << e.identifier << " : " << e.key << endl;
    }

    return listNotes;
}

en::Note Evernote::dlNote(string guid)
{
    bool withContent = true;
    bool withResourcesData = true;
    bool withResourcesRecognition = true;
    bool withResourcesAlternateData = true;
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
        cout << "La note " << note.title << " a été créée." << endl;
    }catch (en::EDAMUserException e){
        cerr << getErrorString(e.errorCode) << " : " << e.parameter << endl;
    }

}

void Evernote::createNotebook(en::Notebook nb)
{
    try{
        noteStore->createNotebook(nb, getAuthToken(), nb);
        cout << "Le répertoire " << nb.name << " a été créé." << endl;
    }catch(en::EDAMUserException e){
        if (e.errorCode == en::EDAMErrorCode::DATA_CONFLICT){
            cerr << "Le répertoire " << nb.name << " existe déjà, veuillez utiliser un autre nom." << endl;
        }else{
            cerr << getErrorString(e.errorCode) << " : " << e.parameter << endl;
        }
    }
}

// Private Functions
string Evernote::getAuthToken() const
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("config.ini", pt);

    return pt.get<string>("consumer.developerToken");
}

string Evernote::getErrorString(en::EDAMErrorCode::type e) const
{
    switch(e){
    case en::EDAMErrorCode::UNKNOWN:
        return "UNKNOWN";
    case en::EDAMErrorCode::BAD_DATA_FORMAT:
        return "BAD_DATA_FORMAT";
    case en::EDAMErrorCode::PERMISSION_DENIED:
        return "PERMISSION_DENIED";
    case en::EDAMErrorCode::INTERNAL_ERROR:
        return "INTERNAL_ERROR";
    case en::EDAMErrorCode::DATA_REQUIRED:
        return "DATA_REQUIRED";
    case en::EDAMErrorCode::LIMIT_REACHED:
        return "LIMIT_REACHED";
    case en::EDAMErrorCode::QUOTA_REACHED:
        return "QUOTA_REACHED";
    case en::EDAMErrorCode::INVALID_AUTH:
        return "INVALID_AUTH";
    case en::EDAMErrorCode::AUTH_EXPIRED:
        return "AUTH_EXPIRED";
    case en::EDAMErrorCode::DATA_CONFLICT:
        return "DATA_CONFLICT";
    case en::EDAMErrorCode::ENML_VALIDATION:
        return "ENML_VALIDATION";
    case en::EDAMErrorCode::SHARD_UNAVAILABLE:
        return "SHARD_UNAVAILABLE";
    case en::EDAMErrorCode::LEN_TOO_SHORT:
        return "LEN_TOO_SHORT";
    case en::EDAMErrorCode::LEN_TOO_LONG:
        return "LEN_TOO_LONG";
    case en::EDAMErrorCode::TOO_FEW:
        return "TOO_FEW";
    case en::EDAMErrorCode::TOO_MANY:
        return "TOO_MANY";
    case en::EDAMErrorCode::UNSUPPORTED_OPERATION:
        return "UNSUPPORTED_OPERATION";
    case en::EDAMErrorCode::TAKEN_DOWN:
        return "TAKEN_DOWN";
    case en::EDAMErrorCode::RATE_LIMIT_REACHED:
        return "RATE_LIMIT_REACHED";
    default:
        return "ERROR_NOT_FOUND";
    }
}
