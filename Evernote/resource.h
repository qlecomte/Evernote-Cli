/*
 * Auteur : Quentin LECOMTE
 * Date de création : 1/6/2016
 * Version : 0.0.1
 * Nom de la classe : Resource
 * Description : Une classe pour gérer, télécharger et téléverser des ressources associées à une note
 * Licence : Licence GNU GPL v3 - http://www.gnu.org/licenses/gpl-3.0.html
 */

#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

#include "evernote.h"
#include "sdk-evernote/Types_types.h"
namespace en = evernote::edam;


class Resource
{
public:
    Resource();
    Resource(std::string filename);
    Resource(en::Resource res);

    std::string getFilename();
    std::string getBinaryData();

    void download();

private:
    en::Resource resource;
};

#endif // RESOURCE_H
