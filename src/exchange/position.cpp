//
// Created by overflow on 2/12/18.
//

#include "../include/exchange/position.h"

positionManager::positionManager(void) {
    // Basic Gate.io functions init
    struct basePosition tradePosition;
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
allPositions.push_back(tradePosition);


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
