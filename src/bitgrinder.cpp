#include "./include/bitgrinder.h"


bool updater = false;
std::string bitgver = "0.0.1.26";
std::string path = "";
std::string config = "";
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
An erroneous arithmetic operation, such as a divide by zero or an operation resulting in overflow.
3 SIGILL
Detection of an illegal instruction.
4 SIGINT
Receipt of an interactive attention signal.
5 SIGSEGV
An invalid access to storage.
6 SIGTERM
A termination request sent to the program.
*/
   std::cout << "\r\n\r\nInterrupt signal (" << signum << ") received.\n";
   std::cout << "Shutting down...\r\n";
   // cleanup and close up stuff here  
   

// terminate program  

   exit(signum);  
}

int init() {
    config = path + "data/config";
    std::cout << config << "\r\n";
    if(exists(config))configFile = readJsonBinary(config); 
    GateIO gate("B5738462-1EB0-449E-AEEC-3F6C1D7DA0DA",
                "3ed0749c03cdbf8e21b6e49d6eb1e65d388e258c2556fc2c4ae4f437028669dc");

    std::cout << "Positions: " << gate.gatePositions.allPositions.size() << " : ";
for (auto pos: gate.gatePositions.allPositions) // element will be a copy of the current array element
{
	std::cout << pos.pair << " ";
	gate.gTickers.push_back(Ticker(pos.pair, "gateio"));
        //Ticker gVenEth("ven_eth", "gateio");
	//add ticker to gateio ticker vector
}
std::cout << "\r\n";
    std::cout << "Tickers: " << gate.gTickers.size() << " : ";
for (auto ticks: gate.gTickers) // element will be a$
{
        std::cout << ticks.vitals.currencyPair << " ";
}
std::cout << "\r\n";

/*
    if(gVenEth.PushCurrent(1234567890123, 124038532, "buy", 0.000323, 230.3, 0.8)==0)
    {
        std::cout << gVenEth.partPeriod.individualTX[0].txID << " " << gVenEth.partPeriod.individualTX[0].txTimestamp << " " << gVenEth.partPeriod.individualTX[0].buySell << "\r\n";
    }
    gVenEth.initThread();
*/

    //update();
    return 0;
}

void update() {
    updater = true;
    while(updater)
    {
        // add update for book, refresh faster than periods
    //for (;;) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(5)); //300000
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); //300000
        std::cout << "5 minutes.";

    }
}

int main(int argc, char *argv[])
{
	std::string aux(argv[0]);
    int pos = aux.rfind('/');
    path = aux.substr(0, pos + 1);
    std::string name = aux.substr(pos + 1);

    if (init() == 0) {
        std::cout << "Initialized. \r\n";

    } else {
        std::cout << "Error initializing.";
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, signalHandler); 
    while(1){sleep(1);}
    //std::thread tUpdate(update);
    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    //tUpdate.join();



    return 0;
}
