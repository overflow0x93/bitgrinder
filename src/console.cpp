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

int main(int argc, char *argv[]) {
    std::string aux(argv[0]);
    int pos = aux.rfind('/');
    path = aux.substr(0, pos + 1);
    //std::std::cout << "Path: " << path << "\r\n";
    std::string name = aux.substr(pos + 1);
    try {
        int opt;
        int portnum;
        boost::program_options::options_description desc("Allowed options");
        desc.add_options()
                ("help,?", "produce help message")
                ("optimization", boost::program_options::value<int>(&opt)->default_value(10),
                 "optimization level")
                ("verbose,v", boost::program_options::value<int>()->implicit_value(1),
                 "enable verbosity (optionally specify level)")
                ("listen,l", boost::program_options::value<int>(&portnum)->implicit_value(1001)
                         ->default_value(0,"no"),
                 "listen on a port.")
                ("include-path,I", boost::program_options::value< std::vector<std::string> >(),
                 "include path")
                ("input-file", boost::program_options::value< std::vector<std::string> >(), "input file")
                ;

        boost::program_options::positional_options_description p;
        p.add("input-file", -1);

        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::command_line_parser(argc, argv).
                options(desc).positional(p).run(), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) {
            std::cout << "Usage: options_description [options]\n";
            std::cout << desc;
            return 0;
        }

        if (vm.count("include-path"))
        {
            //std::cout << "Include paths are: "
              //   << vm["include-path"].as< std::vector<std::string> >() << "\n";
        }

        if (vm.count("input-file"))
        {
            //std::cout << "Input files are: "
              //   << vm["input-file"].as< std::vector<std::string> >() << "\n";
        }

        if (vm.count("verbose")) {
            std::cout << "Verbosity enabled.  Level is " << vm["verbose"].as<int>()
                 << "\n";
        }

        std::cout << "Optimization level is " << opt << "\n";

        std::cout << "Listen port is " << portnum << "\n";
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << "\n";
        return 1;
    }
    return 0;
}