//
// Created by overflow on 2/12/18.
//

#include "../include/system/conparse.hpp"

/*
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
*/