//
// Created by overflow on 2/11/18.
//
#include "./include/console.h"

std::string bitgver = "0.0.1.26";
std::string path = "";

inline bool exists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

bool isRunning(std::string name)
{
    char command[32];
    sprintf(command, "pgrep %s > /dev/null", name.c_str());
    //sprintf(command, "pgrep %s > /dev/null", "bitgrinder");
    return 0 == system(command);
    //if(system(command)>0){return true;}else{return false;}
    //return system(command);
}

int main(int argc, char *argv[]) {
    std::string aux(argv[0]);
    int pos = aux.rfind('/');
    path = aux.substr(0, pos + 1);
    //std::std::cout << "Path: " << path << "\r\n";
    std::string name = aux.substr(pos + 1);
    if(isRunning("bitgrinder")){statusmsg("Bitgrinder","Pass", 2);}
    else{statusmsg("Bitgrinder","Down", 3);}
    if(isRunning("monitor")){statusmsg("Bitgrinder Monitor","Pass", 2);}
    else{statusmsg("Bitgrinder Monitor","Down", 3);}
    try {
        int opt;
        int port;
        boost::program_options::options_description desc("Allowed options");
        desc.add_options()
                ("help,?", "display console options")
                ("verbose,v", boost::program_options::value<int>()->implicit_value(1),
                 "enable verbosity (optionally specify level)")
                ("port,p", boost::program_options::value<int>(&port)->implicit_value(1001)
                         ->default_value(0,"no"),
                 "bitgrinder listen port")
                ("cli", "enter command line interface")
                ;

        boost::program_options::positional_options_description p;
        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::command_line_parser(argc, argv).
                options(desc).positional(p).run(), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) {
            std::cout << "Usage: options_description [options]\n";
            std::cout << desc;
            return 0;
        }

        if (vm.count("verbose")) {
            std::cout << "Verbosity enabled.  Level is " << vm["verbose"].as<int>()
                 << "\n";
        }


    }
    catch(std::exception& e)
    {
        std::cout << e.what() << "\n";
        return 1;
    }
    return 0;
}