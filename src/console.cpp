//
// Created by overflow on 2/11/18.
//
#include "./include/console.h"

std::string bitgver = "0.0.1.26";
std::string binpath = "";
nlohmann::json configFile;

inline bool exists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void signalHandler( int signum ) {
/*
1 SIGABRT
Abnormal termination of the program, such as a call to abort.
2 SIGFPE
An erroneous arithmetic operation, such as a divide by zero or an op$
3 SIGILL
Detection of an illegal instruction.
4 SIGINT
Receipt of an interactive attention signal.
5 SIGSEGV
An invalid access to storage.
6 SIGTERM
A termination request sent to the program.
*/
   std::cout << "\r\n\r\nInterrupt signal (" << signum << ") received.\r\n";
   std::cout << "Shutting down...\r\n";
   // cleanup and close up stuff here


// terminate program

   exit(signum);
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

int conInit()
{
    int returnCode = 0;
    // Init status
    {
        statusmsg("Bitgrinder Console", "Pass", 2);
        if (isRunning("bitgrinder")) { statusmsg("Bitgrinder", "Pass", 2); }
        else {
            statusmsg("Bitgrinder", "Down", 3);
            returnCode += 10;
        }
        if (isRunning("monitor")) { statusmsg("Bitgrinder Monitor", "Pass", 2); }
        else {
            statusmsg("Bitgrinder Monitor", "Down", 3);
            returnCode += 1;
        }
    }
    return returnCode;
}

int main(int argc, char *argv[]) {
    std::string aux(argv[0]);
    int pos = aux.rfind('/');
    binpath = aux.substr(0, pos + 1);
    //std::std::cout << "Path: " << path << "\r\n";
    std::string name = aux.substr(pos + 1);
    std::cout << "\r\n\r\n";
    std::cout << "Bitgrinder " << bitgver << "\r\n\r\n";

    int currentStatus=conInit();

//    configFile = readConfig(binpath);
    if(currentStatus!=0)
    {
        std::string sysCmd = "";
        sysCmd.append(binpath);
        if(currentStatus==11){
            std::cout << "Starting Bitgrinder...\r\n";
            sysCmd.append("bitgrinder &");
            //system(sysCmd.c_str());
            if (isRunning("bitgrinder")) { statusmsg("Start Bitgrinder", "Pass", 2); }
            else {
                statusmsg("Start Bitgrinder", "FAIL", 3);
            //    std::exit;
            }
            std::cout << "Starting Monitor...\r\n";
            sysCmd = "";
            sysCmd.append(binpath);
            sysCmd.append("monitor &");
            //system(sysCmd.c_str());
            if (isRunning("monitor")) { statusmsg("Start Bitgrinder Monitor", "Pass", 2); }
            else {
                statusmsg("Start Bitgrinder Monitor", "FAIL", 3);
            //    std::exit;
            }
        }
        else if(currentStatus==10){
            std::cout << "Starting Bitgrinder...\r\n";
            sysCmd.append("bitgrinder &");
            //system(sysCmd.c_str());
            if (isRunning("bitgrinder")) { statusmsg("Start Bitgrinder", "Pass", 2); }
            else {
                statusmsg("Start Bitgrinder", "FAIL", 3);
            //    std::exit;
            }
        }
        else if(currentStatus==1){
            std::cout << "Starting Monitor...\r\n";
            sysCmd.append("monitor &");
            //system(sysCmd.c_str());
            if (isRunning("monitor")) { statusmsg("Start Bitgrinder Monitor", "Pass", 2); }
            else {
                statusmsg("Start Bitgrinder Monitor", "FAIL", 3);
            //    std::exit;
            }
        }
        else {
            std::cout << "Unexpected running status. Terminating.\r\n";
            std::terminate;  // Abnormal exit - if we're lucky dump core
            //std::exit;
        }
    }

    try {
        int opt;
        int port;
        boost::program_options::options_description desc("Allowed options");
        desc.add_options()
                ("help,?", "display console options")
                ("config,cfg", "configure bitgrinder options")
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

        if (vm.count("config")) {
            std::cout << "\r\n";
            //std::cout << "Initializing configuration \r\n";
		/*
		if(initConfig(binpath)==0)
		{
            		statusmsg("Configuration", "PASS", 2);
		}
		else
		{
            		statusmsg("Configuration", "INIT", 4);
		}*/
		//configFile = readConfig(binpath);
		initConfig(binpath); // read has end of input error
		nlohmann::json ctest = readJsonBinary("./bin/data/config");
		std::cout << ctest.dump(4);
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

    signal(SIGINT, signalHandler);
    while(1){sleep(1);}

    return 0;
}
