#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
namespace po = boost::program_options;

#include "note.h"
#include "notes.h"
#include "notebook.h"

string getFileContent(string filename){
    ifstream in(filename, ios::in);

    if (in){
        ostringstream content;
        string line;
        bool first = true;
        while(getline(in, line)){
            if (first){
                first = false;
            }else{
                content << "</div><div>";
            }
            content << line ;
        }

        return content.str();
    } else{
        cerr << "Fichier non trouvé." << endl;
        return NULL;
    }
}

int main(int argc, char* argv[])
{
    try {
        po::options_description primary("Primary options");
        primary.add_options()
            ("help,h", "produce help message")
            ("example", "Show some examples how you should use it")
            ("licence", "Show the licence (GNU GPL v3")
            ("get", po::value<string>(), "Obtenir")
            ("create", po::value<string>(), "Créer")
            ("update", po::value<string>(), "Mettre à jour")
        ;

        po::options_description moreOptions("More options");
        moreOptions.add_options()
            ("notebook,n", po::value<string>(), "Specify an notebook to use")
            ("title,t", po::value<string>(), "Specify the title of the note")
            ("content,c", po::value<string>(), "Specify the content of the note")
            ("file-content", po::value<string>(), "Specify a file to use as content")
            ("tag", po::value<vector<string>>()->multitoken(), "Specify the tag of the note")
            ("download-media", "Download the media files included in the note");
        ;

        po::options_description cmdline_options;
        cmdline_options.add(primary).add(moreOptions);

        po::options_description visible;
        visible.add(primary).add(moreOptions);

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, cmdline_options), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << visible << endl;

            return 0;
        }
        if (vm.count("example")){
            cout << "Examples to Write" << endl;

            return 0;
        }
        if (vm.count("get")){
            if (boost::iequals(vm["get"].as<string>(), "note")){
                Note note;
                if (vm.count("title")){
                    if (vm.count("notebook")){
                        note = Notebook(vm["notebook"].as<string>()).getNotes().getNote(vm["title"].as<string>());
                    }else{
                        note = Notes().getNote(vm["title"].as<string>());
                    }

                    cout << note << endl;

                    if (vm.count("download-media")){
                        note.downloadMedias();
                    }
                }else{
                    cout << "-t (or --title) is mandatory. Please use --example to see some examples if you need to." << endl;
                }
            }
            else if (boost::iequals(vm["get"].as<string>(), "notebook")){
                Notebook notebook;
                if (vm.count("notebook")){
                    notebook = Notebook(vm["notebook"].as<string>());
                    cout << notebook << endl;
                }else{
                    cout << "-n (or --notebook) is mandatory. Please use --example to see some examples if you need to." << endl;
                }
            }
            else if (boost::iequals(vm["get"].as<string>(), "tag")){}

            return 0;
        }
        if (vm.count("create")){
            if (boost::iequals(vm["create"].as<string>(), "note")){
                if (vm.count("title")) {
                    Note note;
                    note.setTitle(vm["title"].as<string>());
                    if (vm.count("content")){
                        note.setContent(vm["content"].as<string>());
                    }
                    if (vm.count("file-content")){
                        string str = getFileContent(vm["file-content"].as<string>());
                        cout << str << endl;
                        note.setContent(str);
                    }
                    if (vm.count("notebook")){
                        note.setNotebook(Notebook(vm["notebook"].as<string>()));
                    }

                    note.create();
                }else{
                    cout << "-t (or title) is mandatory. Please use --example to see some examples if you need to." << endl;
                }
            }
            else if (boost::iequals(vm["create"].as<string>(), "notebook")){
                if (vm.count("notebook")){
                    Notebook notebook;
                    notebook.setName(vm["notebook"].as<string>());
                    notebook.create();
                }else{
                    cout << "-n (or --notebook) is mandatory. Please use --example to see some examples if you need to." << endl;
                }
            }
            return 0;
        }
        if (vm.count("delete")){
            if (boost::iequals(vm["update"].as<string>(), "note")){}
            if (boost::iequals(vm["update"].as<string>(), "notebook")){
                if (vm.count("notebook")){
                    Notebook notebook;
                    notebook.setName(vm["notebook"].as<string>());
                    notebook.create();
                }else{
                    cout << "-n (or --notebook) is mandatory. Please use --example to see some examples if you need to." << endl;
                }
            }
            return 0;
        }


        cout << "Use -h (or --help) to display help" << endl;

    }catch(exception& e) {
        cerr << "error: " << e.what() << endl;

        return 1;
    }catch(...) {
        cerr << "Exception of unknown type!" << endl;

        return 1;
    }

    return 0;
}




