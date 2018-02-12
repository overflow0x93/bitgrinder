#include "./include/bitgrinder.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>

std::string bitgver = "0.0.1.26";
std::string path = "";

nlohmann::json configFile;

inline bool exists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

int setupConfig() {
    nlohmann::json workingJson;
    {
        workingJson["Application"]["Config"]["TradeData"] = "./data/exchange/";
        workingJson["Application"]["Config"]["Logs"] = "./data/logs/";
        workingJson["Application"]["WebUI"]["Location"] = "/var/www/html/bitg/";
    }
    // Exchanges
    {
        workingJson["Exchange"]["gateio"]["Account"]["API"] = "";
        workingJson["Exchange"]["gateio"]["Account"]["KEY"] = "";
        workingJson["Exchange"]["gateio"]["Config"]["UpdateFreq"] = 10;
        workingJson["Exchange"]["gateio"]["Trade"]["Exclude"]["jnt"] = true;
        workingJson["Exchange"]["gateio"]["Trade"]["Fees"] = 0.002;
        workingJson["Exchange"]["gateio"]["Position"]["Currency"] = "ocn_eth";
        workingJson["Exchange"]["gateio"]["Position"]["Amount"] = 200.5;
        workingJson["Exchange"]["gateio"]["Position"]["BuyRate"] = 0.00003125;
        workingJson["Exchange"]["gateio"]["Position"]["Reinvest"] = 100.0;
    }
    {
        workingJson["Exchange"]["binance"]["Account"]["API"] = "";
        workingJson["Exchange"]["binance"]["Account"]["KEY"] = "";
        workingJson["Exchange"]["binance"]["Config"]["UpdateFreq"] = 10;
        workingJson["Exchange"]["binance"]["Trade"]["Exclude"]["jnt"] = true;
        workingJson["Exchange"]["binance"]["Position"]["Currency"] = "ocn_eth";
        workingJson["Exchange"]["binance"]["Position"]["Amount"] = 200.5;
        workingJson["Exchange"]["binance"]["Position"]["BuyRate"] = 0.00003125;
        workingJson["Exchange"]["binance"]["Position"]["Reinvest"] = 100.0;
    }
    {
        workingJson["Exchange"]["cryptopia"]["Account"]["API"] = "";
        workingJson["Exchange"]["cryptopia"]["Account"]["KEY"] = "";
        workingJson["Exchange"]["cryptopia"]["Config"]["UpdateFreq"] = 10;
        workingJson["Exchange"]["cryptopia"]["Trade"]["Exclude"]["jnt"] = true;
        workingJson["Exchange"]["cryptopia"]["Position"]["Currency"] = "ocn_eth";
        workingJson["Exchange"]["cryptopia"]["Position"]["Amount"] = 200.5;
        workingJson["Exchange"]["cryptopia"]["Position"]["BuyRate"] = 0.00003125;
        workingJson["Exchange"]["cryptopia"]["Position"]["Reinvest"] = 100.0;
    }
    {
        workingJson["Exchange"]["cryptobridge"]["Account"]["API"] = "";
        workingJson["Exchange"]["cryptobridge"]["Account"]["KEY"] = "";
        workingJson["Exchange"]["cryptobridge"]["Config"]["UpdateFreq"] = 10;
        workingJson["Exchange"]["cryptobridge"]["Trade"]["Exclude"]["jnt"] = true;
        workingJson["Exchange"]["cryptobridge"]["Position"]["Currency"] = "ocn_eth";
        workingJson["Exchange"]["cryptobridge"]["Position"]["Amount"] = 200.5;
        workingJson["Exchange"]["cryptobridge"]["Position"]["BuyRate"] = 0.00003125;
        workingJson["Exchange"]["cryptobridge"]["Position"]["Reinvest"] = 100.0;
    }
    return 0;
}

int applyConfig() {
    return 0;
}

int sortPeriods(std::string currency = "ven_eth", int iTimeInc = 30) {

    std::string tradeFile = path + "data/exchange/gate.io/" + currency + ".tx";
    std::string periodFile = path + "data/exchange/gate.io/" + currency + ".atx";
    periodFile.append(std::to_string(iTimeInc));
    std::cout << "\r\nSorting trades into " << periodFile << ".\r\n";

    // unix timestamp | number of seconds since 1 Jan 1970
    // Number of minutes * 60
    iTimeInc = iTimeInc * 60;

    nlohmann::json tradeData = readJsonBinary(tradeFile);
    nlohmann::json workingJson, pair5, pair10, pair15, pair30, pair45, pair60;
    bool nonce, sync = true;
    bool pushData, nextIndex = false;
//Epoch timestamp: 1451649600
//Timestamp in milliseconds: 1451649600000
//Human time (GMT): Friday, January 1, 2016 12:00:00 PM
    int floorTime, maxTime, openTime, closeTime = 1451649600; // init @ 1 Jan 2016
    maxTime += iTimeInc;
    int jsonIndex, iTime, iTrade = 0;
    int pGap = 0;
    int pCount = 1;
    double avgTMP, averageMove, tradeMax, tradeMin, periodVolume, periodVolume2, tradeVal, tradeVol, fRate, average, averageByVol;
    avgTMP, averageMove, tradeMax, periodVolume, periodVolume2, tradeVal, tradeVol, fRate, average, averageByVol = 0;
    tradeMin = 100000000;

    for (int index = 0; index < tradeData["data"].size(); index++) {
        std::stringstream timeStamp, lastTrade, ssVol, ssVol2, ssTMax, ssTMin, ssRate;

        ///////////////////////////////////////////////////////////////////////
        // get unix timestamp | number of seconds since 1 Jan 1970
        //
        {
            {
                timeStamp.clear();
                timeStamp.str(std::string());
                timeStamp.str(tradeData["data"][index]["timestamp"].dump());
                timeStamp >> iTime;
            }
            {
                lastTrade.clear();
                lastTrade.str(std::string());
                lastTrade.str(tradeData["data"][index]["tradeID"].dump());
                lastTrade >> iTrade;
            }
            {
                ssRate.clear();
                ssRate.str(std::string());
                ssRate.str(tradeData["data"][index]["rate"].dump());
                ssRate >> fRate;
            }
            {
                ssVol.clear();
                ssVol.str(std::string());
                ssVol.str(tradeData["data"][index]["total"].dump());
                ssVol >> periodVolume;
            }
            {
                ssVol2.clear();
                ssVol2.str(std::string());
                ssVol2.str(tradeData["data"][index]["amount"].dump());
                ssVol >> periodVolume2;
            }
        }
        ///////////////////////////////////////////////////////////////////////

        // To speed up initial processing time
        if (sync) {
            if (iTime >= maxTime) {
                while (iTime >= maxTime) {
                    floorTime = floorTime + iTimeInc;
                    maxTime = floorTime + iTimeInc;
                }
            } else if (iTime < floorTime) {
                while (iTime < floorTime) {
                    floorTime = floorTime - iTimeInc;
                    maxTime = floorTime - iTimeInc;
                }
            }
            sync = false;
        }

        if (iTime >= floorTime && iTime < maxTime) {
            if (nonce) {
                nextIndex = true;
                nonce = false;
                pCount = 0;
                tradeMin = 100000000;
                avgTMP, averageMove, tradeMax, periodVolume, periodVolume2, tradeVal, tradeVol, fRate, average, averageByVol = 0;
                averageMove = 0;

                workingJson["data"]["timeGap"] = pGap;
                workingJson["data"]["timeFloor"] = floorTime;
                workingJson["data"]["timeMax"] = maxTime;
                workingJson["data"]["openTime"] = iTime;
                workingJson["data"]["openDate"] = tradeData["data"][index]["date"];
                workingJson["data"]["openRate"] = fRate;

            }
            tradeVal = tradeVal + periodVolume;//  = periodVolume + ssVol;
            tradeVol = tradeVol + periodVolume2;//  = periodVolume + ssVol;
            ++pCount;
            if (fRate > tradeMax) { tradeMax = fRate; }
            if (fRate < tradeMin) { tradeMin = fRate; }
            avgTMP += fRate;
            averageMove = averageMove + fRate;
            pGap = 0;
        } else {
            while (iTime >= maxTime) {
                floorTime = floorTime + iTimeInc;
                maxTime = floorTime + iTimeInc;
            }

            pGap++;
            nonce = true;
            --index;

            if (nextIndex) {
                nextIndex = false;
                workingJson["data"]["closeTime"] = iTime;
                workingJson["data"]["closeDate"] = tradeData["data"][index]["date"];//.dump();
                workingJson["data"]["closeRate"] = fRate;
                workingJson["data"]["tradeHigh"] = tradeMax;
                workingJson["data"]["tradeLow"] = tradeMin;
                workingJson["data"]["txCount"] = pCount;
                workingJson["data"]["tradeValue"] = tradeVal;
                workingJson["data"]["tradeVolume"] = tradeVol;
                workingJson["data"]["avgTrade"] = (averageMove / pCount);
                pair30["data"].push_back(workingJson["data"]);
                pCount = 0;
                avgTMP, averageMove, tradeMax, periodVolume, periodVolume2, tradeVal, tradeVol, fRate, average, averageByVol = 0;
                averageMove = 0;
                tradeMin = 100000000;

                nonce = true;
            }
        }
    }
    writeJsonBinary(workingJson, periodFile);
    //std::cout << workingJson["data"].dump(4);
    pair30["data"].push_back(workingJson["data"]);

    std::cout << "Finished.\r\n";
    //std::cout << "\r\n" << pair30["data"].dump(4) << "\r\n";
    return 0;
}

int updatePair(GateIO activeExchange, std::string currency) {
    // Ensure formatting so entire pair list can be processed directly
    currency.erase(std::remove(currency.begin(), currency.end(), '"'), currency.end());
    currency.erase(std::remove(currency.begin(), currency.end(), '/'), currency.end());
// TODO: Check which exchange we're working on
    //if (dynamic_cast<GateIO*>(activeExchange) == nullptr)
    if (1 == 0) {
        std::cout << "Not GateIO" << std::endl;
    } else {
        int beginTradeID = 1;
        std::string tradeID = std::to_string(beginTradeID);
        std::string tradeURL = activeExchange.getAllTradeHistory.URL;
        std::string tradeFile =
                path + "data/exchange/gate.io/" + currency + ".tx"; // /data/exchange/gate.io/trx_eth.tx"
        tradeURL.append(currency);
        tradeURL.append("/");
        std::string txURL = "";
        // If tradefile exists, pick up where we left off instead of creating a new file
        if (exists(tradeFile)) {
            // update file
            std::cout << currency << " trade file exists.\r\n";
            nlohmann::json tradeOut = readJsonBinary(tradeFile);
            int lastTX = tradeOut["data"].size() - 1;
            std::stringstream lastTrade(tradeOut["data"][lastTX]["tradeID"].dump());
            lastTrade >> beginTradeID;
            beginTradeID += 1;
        } else { std::cout << currency << " trade file does not exist. Creating.\r\n"; }


        txURL = tradeURL;
        txURL.append(std::to_string(beginTradeID));
        nlohmann::json finalJson, jsonOutput;

        if (exists(tradeFile)) {
            finalJson = readJsonBinary(tradeFile);
            jsonOutput = finalJson;
        } else {
            jsonOutput = activeExchange.sendRequest(txURL.c_str(), activeExchange.getAllTradeHistory.params);
            if (jsonOutput["result"].dump() == "fail") {
                while (jsonOutput["result"].dump() == "fail") {
                    sleep(5000);
                    jsonOutput = activeExchange.sendRequest(txURL.c_str(),
                                                            activeExchange.getAllTradeHistory.params);
                    if (jsonOutput["result"].dump() != "fail")break;

                }
            }
            finalJson = jsonOutput;
        }

        int records = 1000;
        int count = 0;

        while (jsonOutput["data"].size() > 0 && jsonOutput["data"] != NULL) {
            count = 0;
            int index = jsonOutput["data"].size() - 1;
            beginTradeID = int(jsonOutput["data"][index]["tradeID"]) + 1;
            txURL = tradeURL;
            txURL.append(std::to_string(beginTradeID));
            jsonOutput = activeExchange.sendRequest(txURL.c_str(),
                                                    activeExchange.getAllTradeHistory.params);
            if (jsonOutput["result"].dump() == "fail") {
                while (jsonOutput["result"].dump() == "fail") {
                    sleep(5000);
                    jsonOutput = activeExchange.sendRequest(txURL.c_str(),
                                                            activeExchange.getAllTradeHistory.params);
                    if (jsonOutput["result"].dump() != "fail")break;
                }
            }
            while (count < jsonOutput["data"].size()) {
                finalJson["data"].push_back(jsonOutput["data"][count]);
                records++;
                count++;
            }
        }

        std::cout << "Write process complete.\r\n";

        writeJsonBinary(finalJson, tradeFile);
    } // end gateio processing

    return 0;
}

int fetchTradeData(GateIO activeExchange, std::string baseCurrency) {
    nlohmann::json activePairs = activeExchange.sendRequest(activeExchange.getPairs.URL,
                                                            activeExchange.getPairs.params);
    std::string currency, exchange = "";
    for (int index = 0; index < activePairs.size(); index++) {
        currency = activePairs[index].dump();
        std::cout << "Index: " << std::to_string(index) << "   Pair: " << currency << "\r\n";
        currency.erase(std::remove(currency.begin(), currency.end(), '"'), currency.end());
        currency.erase(std::remove(currency.begin(), currency.end(), '/'), currency.end());
        if (currency == "eth_usdt")
            continue; //||currency=="cofi_eth" || currency=="zpt_eth" )continue;  // output causes segfault
        if (currency.find(baseCurrency) != std::string::npos) {
            // TODO: Check which exchange we're working on
            //if (dynamic_cast<GateIO*>(activeExchange) == nullptr)
            if (1 == 0) {
                std::cout << "Not GateIO" << std::endl;
            } else {
                int beginTradeID = 1;
                std::string tradeID = std::to_string(beginTradeID);
                std::string tradeURL = activeExchange.getAllTradeHistory.URL;
                std::string tradeFile =
                        path + "data/exchange/gate.io/" + currency + ".tx"; // /data/exchange/gate.io/trx_eth.tx"
                tradeURL.append(currency);
                tradeURL.append("/");
                std::string txURL = "";
                // If tradefile exists, pick up where we left off instead of creating a new file
                ///////////////////////////////////////////////////////
                if (exists(tradeFile)) {
                    // update file
                    std::cout << currency << " trade file exists.\r\n";
                    nlohmann::json tradeOut = readJsonBinary(tradeFile);
                    int lastTX = tradeOut["data"].size() - 1;
                    std::cout << "Last tx: " << tradeOut["data"][lastTX]["tradeID"].dump() << "\r\n";
                    std::stringstream lastTrade(tradeOut["data"][lastTX]["tradeID"].dump());
                    lastTrade >> beginTradeID;
                    beginTradeID += 1;
                    std::cout << "Next tx: " << beginTradeID << "\r\n";
                } else { std::cout << currency << " trade file does not exist. Creating.\r\n"; }
                ///////////////////////////////////////////////////////



                txURL = tradeURL;
                txURL.append(std::to_string(beginTradeID));

                nlohmann::json finalJson, jsonOutput;

                ///////////////////////////////////////////////////////
                if (exists(tradeFile)) {
                    finalJson = readJsonBinary(tradeFile);
                    jsonOutput = finalJson;
                }
                    ///////////////////////////////////////////////////////
                else {
                    jsonOutput = activeExchange.sendRequest(txURL.c_str(), activeExchange.getAllTradeHistory.params);
                    if (jsonOutput["result"].dump() == "fail") {
                        while (jsonOutput["result"].dump() == "fail") {
                            sleep(5000);
                            jsonOutput = activeExchange.sendRequest(txURL.c_str(),
                                                                    activeExchange.getAllTradeHistory.params);
                            if (jsonOutput["result"].dump() != "fail")break;

                        }
                    }
                    finalJson = jsonOutput;
                }  // end if-else
                ///////////////////////////////////////////////////////


                ///////////////////////////////////////////////////////
                int records = 1000;
                //std::cout << "Fetching " << currency << "\r\n";
                //std::cout << "Loading: " << records << "\r\n";
                int count = 0;
                ///////////////////////////////////////////////////////
                while (jsonOutput["data"].size() > 0 && jsonOutput["data"] != NULL) {
                    count = 0;
                    int index = jsonOutput["data"].size() - 1;
                    beginTradeID = int(jsonOutput["data"][index]["tradeID"]) + 1;
                    txURL = tradeURL;
                    txURL.append(std::to_string(beginTradeID));
                    jsonOutput = activeExchange.sendRequest(txURL.c_str(),
                                                            activeExchange.getAllTradeHistory.params);
                    if (jsonOutput["result"].dump() == "fail") {
                        while (jsonOutput["result"].dump() == "fail") {
                            sleep(5000);
                            jsonOutput = activeExchange.sendRequest(txURL.c_str(),
                                                                    activeExchange.getAllTradeHistory.params);
                            if (jsonOutput["result"].dump() != "fail")break;
                        }
                    }// end null json check
                    while (count < jsonOutput["data"].size()) {
                        finalJson["data"].push_back(jsonOutput["data"][count]);
                        records++;
                        //system("clear");
                        //std::cout << "\r\n\r\n";
                        //std::cout << "Bitgrinder " << bitgver << "\r\n";
                        //std::cout << "Gate.io Historical: \r\n";
                        //std::cout << "Fetching " << currency << "\r\n";
                        //std::cout << "Loading:  " << records;// << "\r\n";
                        //std::cout << "  TID: " << jsonOutput["data"][count]["tradeID"] << "  \r\n";
                        //std::cout << jsonOutput["data"][count]["date"] << "\r\n";
                        count++;
                    }  // end push records to binary
                } // end read records to push
                ///////////////////////////////////////////////////////
                std::cout << "Write process complete.\r\n";

                writeJsonBinary(finalJson, tradeFile);
                std::cout << finalJson["data"].size() << " records written to " << tradeFile << ".\r\n";
                nlohmann::json testOut = readJsonBinary(tradeFile);
                int lastTX = testOut["data"].size() - 1;
                std::cout << "Last tx: " << testOut["data"][lastTX].dump();
                std::cout << std::to_string(activePairs.size() - index) << " pairs remaining.\r\n";
            } // end gateio processing

        } // end base currency check
        else { std::cout << "Index " << std::to_string(index) << " not in base currency selection.\r\n"; }

    } // end for
    std::cout << "Pair processing complete.\r\n";
    return 0;
}

int init(std::string binaryDir, GateIO gateRef) {
    //system("clear");
    std::cout << "\r\n\r\n";
    std::cout << "Bitgrinder " << bitgver << "\r\n";
    std::string sysCmd = "mkdir -p ";
    sysCmd.append(binaryDir);
    sysCmd.append("data/exchange/gate.io");
    system(sysCmd.c_str());
    //fetchTradeData(gateRef, "eth");
    updatePair(gateRef, "ven_eth");
    sortPeriods("ven_eth", 30);
    sortPeriods("ven_eth", 05);
    //std::thread(update).detach();
    return 0;
}

void update() {
    for (;;) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

int console(GateIO cliExchange) {
    // Basic CLI input management
    std::string clicmd;
    nlohmann::json jsonOutput;
    std::string latency = "";

    for (;;) {
        std::cout << " >  ";

        // Todo: Set delimiter " " and enable commands on per exchange basis
        getline(std::cin, clicmd);
        if (clicmd == "exit" || clicmd == "quit" || clicmd == "^c" || clicmd == "logout") { break; }
        else if (clicmd == "ping gate" || clicmd == "ping gate.io") {
            system("clear");
            std::cout << "\r\n\r\n";
            std::cout << "Bitgrinder " << bitgver << "\r\n";
            std::cout << "Gate.io API latency: " << cliExchange.getAPIlatency() << "ms\r\n";
        } else if (clicmd == "bal gate" || clicmd == "balance gate") {
            system("clear");
            std::cout << "\r\n\r\n";
            std::cout << "Bitgrinder " << bitgver << "\r\n";
            std::cout << "Exchange latency: " << cliExchange.getAPIlatency() << "ms\r\n";
            std::cout << "Gate.io balances: \r\n";
            jsonOutput = cliExchange.sendRequest(cliExchange.getBalances.URL, cliExchange.getBalances.params);
            std::cout << jsonOutput.dump(4);
            std::cout << "\r\n";
        } else if (clicmd == "hist gate" || clicmd == "history gate") {
            system("clear");
            std::cout << "\r\n\r\n";
            std::cout << "Bitgrinder " << bitgver << "\r\n";
            std::cout << "Exchange latency: " << cliExchange.getAPIlatency() << "ms\r\n";
            std::cout << "Gate.io Trade History: \r\n";
            jsonOutput = cliExchange.sendRequest(cliExchange.getTradeHistory.URL,
                                                 cliExchange.getTradeHistory.params.dump());
            std::cout << "\r\n";
        } else if (clicmd == "historical gate") {
            system("clear");
            std::cout << "\r\n\r\n";
            std::cout << "Bitgrinder " << bitgver << "\r\n";
            //std::cout << "Exchange latency: " << cliExchange.getAPIlatency() << "ms\r\n";
            std::cout << "Gate.io Historical: \r\n";

            // init base json
            int beginTradeID = 1;
            std::string tradeID = std::to_string(beginTradeID);
            std::string tradeURL = cliExchange.getAllTradeHistory.URL;
            tradeURL.append("trx_eth/");
            tradeURL.append(tradeID);
            jsonOutput = cliExchange.sendRequest(tradeURL.c_str(), cliExchange.getAllTradeHistory.params);
            nlohmann::json finalJson = jsonOutput;
            int records = 1000;
            std::cout << "Loading: " << records << "\r\n";
            int count = 0;
            while (jsonOutput["data"].size() > 0 && jsonOutput["data"] != NULL) {
                count = 0;
                int index = jsonOutput["data"].size() - 1;
                beginTradeID = int(jsonOutput["data"][index]["tradeID"]) + 1;
                tradeID = std::to_string(beginTradeID);
                tradeURL = cliExchange.getAllTradeHistory.URL;
                tradeURL.append("trx_eth/");
                tradeURL.append(tradeID);
                jsonOutput = cliExchange.sendRequest(tradeURL.c_str(), cliExchange.getAllTradeHistory.params);
                while (count < jsonOutput["data"].size()) {
                    finalJson["data"].push_back(jsonOutput["data"][count]);
                    records++;
                    system("clear");
                    std::cout << "\r\n\r\n";
                    std::cout << "Bitgrinder " << bitgver << "\r\n";
                    std::cout << "Gate.io Historical: \r\n";
                    std::cout << "Loading:  " << records;// << "\r\n";
                    std::cout << "  TID: " << jsonOutput["data"][count]["tradeID"] << "  \r\n";
                    std::cout << jsonOutput["data"][count]["date"] << "\r\n";
                    count++;
                }
            }

            std::string saveFile = path;
            saveFile.append("data/exchange/gate.io/trx_eth.tx");
            writeJsonBinary(finalJson, saveFile);
            std::cout << finalJson.size() << " records written to file.\r\n";
            nlohmann::json testOut = readJsonBinary(saveFile);
            int lastTX = testOut["data"].size() - 1;
            std::cout << "Last tx: " << testOut["data"][lastTX].dump(4);

        } else if (clicmd == "orders gate" || clicmd == "openorders gate") {
            system("clear");
            std::cout << "\r\n\r\n";
            std::cout << "Bitgrinder " << bitgver << "\r\n";
            std::cout << "Exchange latency: " << cliExchange.getAPIlatency() << "ms\r\n";
            std::cout << "Gate.io open orders: \r\n";
            jsonOutput = cliExchange.sendRequest(cliExchange.getOpenOrders.URL, cliExchange.getOpenOrders.params);
            std::cout << "\r\n";
        } else if (clicmd == "getpair gate") {
            system("clear");
            std::cout << "\r\n\r\n";
            std::cout << "Bitgrinder " << bitgver << "\r\n";
            std::cout << "Exchange latency: " << cliExchange.getAPIlatency() << "ms\r\n";
            jsonOutput = cliExchange.sendRequest(cliExchange.getPairs.URL, "");
            std::cout << "\r\n";
        }
    }
    return 0; //
}

int main(int argc, char *argv[]) {
    GateIO gate("B5738462-1EB0-449E-AEEC-3F6C1D7DA0DA",
                "3ed0749c03cdbf8e21b6e49d6eb1e65d388e258c2556fc2c4ae4f437028669dc");

    std::string aux(argv[0]);
    int pos = aux.rfind('/');
    path = aux.substr(0, pos + 1);
    std::cout << "Path: " << path << "\r\n";
    std::string name = aux.substr(pos + 1);

    if (init(path, gate) == 0) {
        std::cout << "Initialized. \r\n";

    } else {
        std::cout << "Error initializing.";
        exit(EXIT_FAILURE);
    }

    // Temp redirect straight to console
    //console(gate);
    return 0;
}
