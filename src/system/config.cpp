//
// Created by overflow on 2/12/18.
//
#include "../include/system/config.h"

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
