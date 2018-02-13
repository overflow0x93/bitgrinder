//
// Created by overflow on 2/12/18.
//
#include "../include/exchange/apiscrape.h"

/*
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
 */

/*if(gVenEth.PushCurrent(1234567890123, 124038532, "buy", 0.000323, 230.3, 0.8)==0)
{
std::cout << gVenEth.partPeriod.individualTX[0].txID << " " << gVenEth.partPeriod.individualTX[0].txTimestamp << " " << gVenEth.partPeriod.individualTX[0].buySell << "\r\n";
}
gVenEth.initThread();*/