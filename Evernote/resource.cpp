/*
 * Auteur : Quentin LECOMTE
 * Date de création : 01/06/2016
 * Version : 0.2.0
 * Nom de la classe : Resource
 * Description : Une classe pour récupérer la durée d'une vidéo.
 * Licence : Licence Apache 2.0 - http://www.apache.org/licenses/LICENSE-2.0
 */


#include "resource.h"
#include "fstream"
using namespace std;

Resource::Resource()
{}

Resource::Resource(string filename)
{}

Resource::Resource(en::Resource res) : resource(res)
{}

string Resource::getFilename()
{
    return resource.attributes.fileName;
}

string Resource::getBinaryData()
{
    return resource.data.body;
}

void Resource::download()
{
    ofstream of(resource.attributes.fileName, ios::out | ios::trunc);
    if (of){
        of << getBinaryData();
        of.close();
    }
}
