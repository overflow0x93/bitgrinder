#include "./include/bitgrinder.h"


bool updater = false;
std::string bitgver = "0.0.1.26";
std::string path = "";

nlohmann::json configFile;

int applyConfig() {
    return 0;
}

int init() {
    GateIO gate("B5738462-1EB0-449E-AEEC-3F6C1D7DA0DA",
                "3ed0749c03cdbf8e21b6e49d6eb1e65d388e258c2556fc2c4ae4f437028669dc");
    /*struct basePosition {
        //std::string exchange{""};
        std::string pair{""};
        float rate{0};
        float amount{0};
        float fee{0.002};
        float returns{0};
        float reinvest{1.0};
        nlohmann::json book{};
        bool buySig{false};
        bool sellSig{false};
    } tradePosition;

    std::vector<positionManager> allPositions;
    positionManager();*/
    //gate.gatePositions().allPositions.push_back();
    Ticker gVenEth("ven_eth", "gateio");
/*
    if(gVenEth.PushCurrent(1234567890123, 124038532, "buy", 0.000323, 230.3, 0.8)==0)
    {
        std::cout << gVenEth.partPeriod.individualTX[0].txID << " " << gVenEth.partPeriod.individualTX[0].txTimestamp << " " << gVenEth.partPeriod.individualTX[0].buySell << "\r\n";
    }
    gVenEth.initThread();
*/

    update();
    return 0;
}

void update() {
    updater = true;
    while(updater)
    {
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

    std::thread tUpdate(update);
    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    tUpdate.join();



    return 0;
}
