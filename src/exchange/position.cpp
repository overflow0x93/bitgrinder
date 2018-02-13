//
// Created by overflow on 2/12/18.
//

#include "../include/exchange/position.h"

positionManager::positionManager(void) {
    // Basic Gate.io functions init
    struct basePosition tradePosition = {};

/*
 struct basePosition {
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
    positionManager();
*/
std::vector<basePosition> allPositions;
PushPosition();

}

positionManager::~positionManager(void) {


}

void positionManager::removePosition(int positionNum)
{

}

int positionManager::findPosition(std::string pairToFind)
{
    int returnIndex = -1;
    return returnIndex;
}

void positionManager::initPosition()
{
    //allPositions.push_back(tradePosition);
}

/*
positionManager:::Ticker(std::string pair, std::string exchange) : cPair{ pa$
{
    struct windowVitals vitals;
    struct tradeData tx;
    struct tradePeriod fullPeriod;
    struct currentPeriod partPeriod;
    //std::vector<tradePeriod> dWindow;
    //std::vector<tradeData> partPeriod.individualTX;
}

int Ticker::ReceiveTX()
{
    return 0;
}*/

//int positionManager::PushPosition(std::string pair = "ocn_eth", float rate = 0.00002466, float amount = 109666.7267, float fee = 0.002, float returns = 0, float reinvest = 1.0, bool buySig = false, bool sellSig = false)
void positionManager::PushPosition(std::string pair, float rate, float amount, float fee, float returns, float reinvest, bool buySig, bool sellSig)
{
        basePosition bPos;        
        bPos.pair = pair;
        bPos.rate = rate;
        bPos.amount = amount;
        bPos.fee = fee;
        bPos.returns = returns;
        bPos.reinvest = reinvest;
        bPos.buySig = buySig;
        bPos.sellSig = sellSig;
	allPositions.push_back(bPos);
}


