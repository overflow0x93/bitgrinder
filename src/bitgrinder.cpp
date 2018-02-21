#include "./include/bitgrinder.hpp"
// ⇋⇌🢔🢕🢖🢗⮐⮑⮒⮓⮔⯐
bool updater = false;
std::string bitgver = "0.0.1.26";
nlohmann::json configFile;

inline bool exists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void signalHandler(int signum) {
    std::cout << "\r\n\r\nInterrupt signal (" << signum << ") received.\n";
    std::cout << "Shutting down...\r\n";
    // cleanup and close up stuff here
#ifdef DEBUG
    std::string outMsg = "↯↯↯↯ TERM SIGNAL_______________________________\r\n___________________________TERMINATING BITGRINDER________________________\r\n\r\n\r\n";
    Debug::dBasicLog(INIT,INFO,outMsg);
#endif
    updater = false;
    // Ticker termination failing - object deleted already
    std::cout << "\r\n";

    // terminate program

    exit(signum);
}


int init(std::string path) {
    configFile = readConfig(path);
    std::string outMsg;
    Debug::dBasicLog(INIT, INFO,
                     "\r\n_________________________BITGRINDER INITIALIZATION__________________________");
//    GateIO gate("B5738462-1EB0-449E-AEEC-3F6C1D7DA0DA",
//                "3ed0749c03cdbf8e21b6e49d6eb1e65d388e258c2556fc2c4ae4f437028669dc");
    GateIO gate(configFile["Exchange"]["gateio"]["Account"]["API"].dump(),
                configFile["Exchange"]["gateio"]["Account"]["KEY"].dump());
    //gateIOp = &gate;
    std::cout << "API: " << configFile["Exchange"]["gateio"]["Account"]["API"].dump() << "\r\n";
    std::cout << "Positions in config: " << configFile["Exchange"]["gateio"]["Position"].size() << " : ";
    std::cout << "Starting tx ID: " << configFile["Exchange"]["gateio"]["Config"]["iTXID"].dump() << "\r\n";

// Format starting TXID    
    std::string sInitTX = configFile["Exchange"]["gateio"]["Config"]["iTXID"].dump();
    std::replace(sInitTX.begin(), sInitTX.end(), '"', ' ');
    sInitTX.erase(std::remove(sInitTX.begin(), sInitTX.end(), ' '), sInitTX.end());
    int initTX = std::stoi(sInitTX);


    for (auto cpos: configFile["Exchange"]["gateio"]["Position"]) {
        std::cout << cpos["Pair"].dump() << " ";
        std::string pairNameToAdd = cpos["Pair"].dump();
        std::replace(pairNameToAdd.begin(), pairNameToAdd.end(), '"', ' ');
        pairNameToAdd.erase(std::remove(pairNameToAdd.begin(), pairNameToAdd.end(), ' '), pairNameToAdd.end());
#ifdef DEBUG
        outMsg = "Located and pushing ";
        outMsg.append(pairNameToAdd);outMsg.append(" position.");
        Debug::dBasicLog(INIT,INFO,outMsg);
#endif
        gate.gatePositions.PushPosition(pairNameToAdd, 0.00004266, 0.98, 0.002, 0.0, 1.0, false, false);
    }
    std::cout << "\r\n";
    std::cout << "Positions: " << gate.gatePositions.allPositions.size() << " : ";


    for (auto pos: gate.gatePositions.allPositions) // element will be a copy of the current array element
    {
        std::cout << pos.pair << " ";
        Ticker newTicker = Ticker(pos.pair, "gateio");
        // Add other details here
        newTicker.vitals.currencyPair = pos.pair;
#ifdef DEBUG
        outMsg = "Created and pushing ";
        outMsg.append(pos.pair);outMsg.append(" ticker.");
        Debug::dBasicLog(INIT,INFO,outMsg);
#endif

        gate.gTickers.push_back(newTicker);
    }
    std::cout << "\r\n";

    std::cout << "Tickers: " << gate.gTickers.size() << " : ";
#ifdef DEBUG
        outMsg = "Starting parallel tick init ";
        Debug::dBasicLog(INIT,INFO,outMsg);
#endif

/////////////////////////////////////////////////
    #pragma omp parallel for    
    for (int tcount = 0; tcount <gate.gTickers.size(); tcount++) {
    std::string sTS, sTX, sRATE, sAMT, sTOT, tradeURL, poutMsg;
    int cTS, cTX;
    float cRATE, cAMT, cTOT;
    int lastTS;

    //for (auto ticks: gate.gTickers) {
	Ticker ticks = gate.gTickers[tcount]; 
	ticks.initThread();
	/*
	try { // 
	  if(ticks == NULL)throw 1;
	}
	catch (int e) {
	  switch(e){
	    case 1:
		outMsg = "[CRITICAL] Ticker is NULL!";
		break;
	    default:
		outMsg = "[CRITICAL] Error in Ticker assignment!";
		break;
	  }
#ifdef DEBUG
        Debug::dBasicLog(INIT,CRITICAL,outMsg);
#endif

	std::cout << outMsg << "\r\n";
	}*/
#ifdef DEBUG
        poutMsg = ticks.vitals.currencyPair;
        poutMsg.append(" initialization started.");
        Debug::dBasicLog(INIT,INFO,outMsg);
#endif
        //Find out length of tickers; fill with initial data.
        tradeURL = gate.getAllTradeHistory.URL;
        tradeURL.append(ticks.vitals.currencyPair);
        tradeURL.append("/");
        std::string txURL = tradeURL;
        txURL.append(sInitTX); // Roughly halfway through jan
        int cTXID = initTX;
        nlohmann::json jsonOutput;
        jsonOutput = gate.sendRequest(txURL.c_str(), gate.getAllTradeHistory.params);
        if (jsonOutput.empty())std::cout << "Empty JSON.\r\n";
        else if (jsonOutput["data"].empty())std::cout << "JSON ERROR.\r\n";
        int count;
        auto now = std::chrono::high_resolution_clock::now();
        long int ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        sTS = jsonOutput["data"][0]["timestamp"].dump();
        std::replace(sTS.begin(), sTS.end(), '"', ' ');
        sTS.erase(std::remove(sTS.begin(), sTS.end(), ' '), sTS.end());
        cTS = std::stoi(sTS);
        lastTS = cTS;
        int txp = 0;
        while ((ms / 1000) >= cTS + (5 * 60) && txp <= 2) { // As long as entry is at least 5 minutes ago
            count = 0;
            tradeURL = gate.getAllTradeHistory.URL;
            tradeURL.append(ticks.vitals.currencyPair);
            tradeURL.append("/");
            std::string txURL = tradeURL;
            txURL.append(std::to_string(cTXID)); // Roughly halfway through jan
            nlohmann::json jsonOutput;
            jsonOutput = gate.sendRequest(txURL.c_str(), gate.getAllTradeHistory.params);
            if (jsonOutput.empty())std::cout << "Empty JSON.\r\n";

            while (count < jsonOutput["data"].size()) {
                txp = 0;
                sTS = jsonOutput["data"][count]["timestamp"].dump();
                std::replace(sTS.begin(), sTS.end(), '"', ' ');
                sTS.erase(std::remove(sTS.begin(), sTS.end(), ' '), sTS.end());
                cTS = std::stoi(sTS);
                lastTS = cTS;
                sTX = jsonOutput["data"][count]["tradeID"].dump();
                std::replace(sTX.begin(), sTX.end(), '"', ' ');
                sTX.erase(std::remove(sTX.begin(), sTX.end(), ' '), sTX.end());
                cTX = std::stoi(sTX);
                cTXID = cTX;
                sRATE = jsonOutput["data"][count]["rate"].dump();
                std::replace(sRATE.begin(), sRATE.end(), '"', ' ');
                sRATE.erase(std::remove(sRATE.begin(), sRATE.end(), ' '), sRATE.end());
                cRATE = std::stof(sRATE);
                sAMT = jsonOutput["data"][count]["amount"].dump();
                std::replace(sAMT.begin(), sAMT.end(), '"', ' ');
                sAMT.erase(std::remove(sAMT.begin(), sAMT.end(), ' '), sAMT.end());
                cAMT = std::stof(sAMT);
                sTOT = jsonOutput["data"][count]["total"].dump();
                std::replace(sTOT.begin(), sTOT.end(), '"', ' ');
                sTX.erase(std::remove(sTOT.begin(), sTOT.end(), ' '), sTOT.end());
                cTOT = std::stof(sTOT);
                //std::cout << cTOT << " ";
                // Must be numbers, but are read as strings
                //if(cTOT >= minValue)
                ticks.PushCurrent(cTS, cTX, jsonOutput["data"][count]["type"], cRATE, cAMT, cTOT);
#ifdef DEBUG
                //std::cout << "[Debug] Target time : " << std::to_string(ms/1000) << "   Time Index : " << std::to_string(cTS) << " \r\n";
#endif
                ++count;
            }  // end push records to binary
            ++txp;
#ifdef DEBUG
            std::cout << "[Debug] Next " << ticks.vitals.currencyPair << " batch...\r\n";
#endif
            cTXID += 1;
        }
// End parallel

#ifdef DEBUG
        std::cout << "[Debug] Next currency pair...\r\n";
outMsg = ticks.vitals.currencyPair;
outMsg.append(" initialization completed with ");	
outMsg.append(std::to_string(ticks.partPeriod.individualTX.size()));
outMsg.append(" records added to ticker.");
Debug::dBasicLog(INIT,INFO,outMsg);
#endif
// Init complete
    }
#ifdef DEBUG
    outMsg = "-----TICKER INIT COMPLETE-----";
    //outMsg.append(std::to_string(ticks.partPeriod.individualTX.size()));
    //outMsg.append(" records added to ticker.");
    Debug::dBasicLog(INIT,INFO,outMsg);
#endif

    update();


    return 0;
}

void update() {
#ifdef DEBUG
    std::string outMsg = "Update thread started.";
    Debug::dBasicLog(INIT,INFO,outMsg);
#endif
    updater = true;
    while (updater) {
#ifdef DEBUG
        outMsg = "Update pass";
        Debug::dBasicLog(INIT,INFO,outMsg);
        std::cout << "[Debug] Running update process...\r\n";
#endif
        // add update for book, refresh faster than periods
        //for (;;) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(5)); //300000
        std::this_thread::sleep_for(std::chrono::seconds(30)); //300000
        //std::cout << "2.5 minutes";

    }
#ifdef DEBUG
    outMsg = "Stopping update thread.";
    Debug::dBasicLog(INIT,INFO,outMsg);
    std::cout << "[Debug] Stopping update process...\r\n";
#endif

}

int main(int argc, char *argv[]) {
    std::string aux(argv[0]);
    int pos = aux.rfind('/');
    std::string path = aux.substr(0, pos + 1);
    std::string name = aux.substr(pos + 1);
    signal(SIGINT, signalHandler);

#ifdef DEBUG
    std::cout << "[Debug] path = " << path << "\r\n";
#endif
    if (init(path) == 0) {
        std::cout << "Initialized. \r\n";

    }
    else {
        std::cout << "Error initializing.";
        exit(EXIT_FAILURE);
    }

    //while (1) { sleep(1); }
    //std::thread tUpdate(update);
    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    //tUpdate.join();



    return 0;
}
