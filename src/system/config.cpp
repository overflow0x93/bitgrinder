//
// Created by overflow on 2/12/18.
//
#include "../include/system/config.h"

std::string config = "";
nlohmann::json cfgFile;

inline bool exists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

int setupConfig(std::string config) {
std::cout << config;
    nlohmann::json workingJson,tempJson;
//std::string conFile = config + ".test";
std::string conFile = "./bin/data/config";
    std::string input = "";
    {
	workingJson["Application"]["Config"]["TradeData"] = "./data/exchange/";
        std::cout << "Enter log location [./data/logs/] : ";
	std::string input;
        std::getline(std::cin, input);
	if(input.empty()){
	  workingJson["Application"]["Config"]["Logs"] = "./data/logs/";
	}
	else{
	  workingJson["Application"]["Config"]["Logs"] = input;
	}
        workingJson["Application"]["WebUI"]["Location"] = "/var/www/html/bitg/";
    }
    // Exchanges
    {
        

	std::cout << "Enter Gate.IO API Key: : ";
        std::getline(std::cin, input);
	if(input.empty()){
	  workingJson["Exchange"]["gateio"]["Account"]["API"] = "";
	}
	else{
	  workingJson["Exchange"]["gateio"]["Account"]["API"] = input;
	}

        std::cout << "Enter Gate.IO API Secret Key: : ";
        std::getline(std::cin, input);
        if(input.empty()){
	  workingJson["Exchange"]["gateio"]["Account"]["KEY"] = "";
	}

        else{
	  workingJson["Exchange"]["gateio"]["Account"]["KEY"] = input;
	}

        workingJson["Exchange"]["gateio"]["Config"]["UpdateFreq"] = 10;
        workingJson["Exchange"]["gateio"]["Trade"]["Exclude"]["jnt"] = true;
        workingJson["Exchange"]["gateio"]["Trade"]["Fees"] = 0.002;


        bool bMorePos = false;
        std::cout << "Do you have any current positions [Y]/N ? : ";
        std::getline(std::cin, input);
	int nPos = 0;
	if(input.empty() || input == "Y" || input == "y" || input == "Yes" || input == "YES" || input == "yes"){bMorePos = true;}
        else{bMorePos = false;}
	while(bMorePos){
	  std::cout << "Enter pair you traded < example: eos_eth > : ";
          std::getline(std::cin, input);
          if(input.empty()){
	    tempJson["Exchange"]["gateio"]["Position"]["eos_eth"] = "eos_eth";
	    tempJson["Exchange"]["gateio"]["Position"]["Currency"] = "eos_eth";
	    //root.put("Exchange.gateio.Position.Currency", 0.002);}
	  }
	  else{
	    workingJson["Exchange"]["gateio"]["Position"][input] = input;
	    workingJson["Exchange"]["gateio"]["Position"]["Currency"] = input;
	  }
//	  tempJson["Exchange"]["gateio"]["Position"]["Amount"] = 200.5;
//          tempJson["Exchange"]["gateio"]["Position"]["BuyRate"] = 0.00003125;
//          tempJson["Exchange"]["gateio"]["Position"]["Reinvest"] = 100.0;
//	  workingJson["Exchange"]["gateio"]["Position"].push_back(tempJson["Exchange"]["gateio"]["Position"]);
          std::cout << "Do you have any other current positions [Y]/N : ";
          std::getline(std::cin, input);
	  if(input.empty() || input == "Y" || input == "y" || input == "Yes" || input == "YES" || input == "yes"){bMorePos = true;}
          else{bMorePos = false;}
	  nPos++;
	  std::cout << "\r\n";
	}
	
    }
    /*
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
*/
    std::cout << workingJson.dump(4);
//    writeJsonBinary(workingJson, config);
    writeJsonBinary(workingJson, conFile);
    return 0;
}

int initConfig(std::string ipath) {

    std::string iconfig = ipath + "data/config.cb";
    //std::cout << iconfig << "\r\n";
    if(exists(iconfig))
    {
        //cfgFile = readJsonBinary(iconfig);
    }
    else
    {
        setupConfig(config);
        //cfgFile = readJsonBinary(iconfig);
    }

    return 0;
}

nlohmann::json readConfig(std::string cpath)
{
	std::cout<<cpath<<"\r\n";
	std::string configpath = cpath + "data/config.cb";
	initConfig(configpath);
        //cfgFile = readJsonBinary(configpath);
	//return cfgFile;
	//nlohmann::json returnJson = readJsonBinary(configpath);
	nlohmann::json returnJson;
	return returnJson;
}
