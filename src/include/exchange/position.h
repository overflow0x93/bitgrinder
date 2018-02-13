//
// Created by overflow on 2/12/18.
//
#include "../system/json.hpp"
#include <string>
#include <vector>

#ifndef BITGRINDER_POSITION_H
#define BITGRINDER_POSITION_H

#endif //BITGRINDER_POSITION_H

class positionManager {
public:
    struct basePosition {
        //std::string exchange{""};
//        std::string pair{"ocn_eth"};
//        float rate{0.00002466};
//        float amount{109666.7267};
//        float fee{0.002};
//        float returns{0};
//        float reinvest{1.0};
//        nlohmann::json book{};
//        bool buySig{false};
//        bool sellSig{false};

        std::string pair = "ocn_eth";
        float rate = 0.00002466;
        float amount = 109666.7267;
        float fee = 0.002;
        float returns = 0;
        float reinvest = 1.0;
//        nlohmann::json book;
        bool buySig = false;
        bool sellSig = false;
    } tradePosition;

    std::vector<basePosition> allPositions;

    positionManager();
    ~positionManager();
    virtual void removePosition(int positionNum);
    virtual void initPosition();
    virtual int findPosition(std::string pairToFind);
    virtual void PushPosition(std::string pair = "ocn_eth", float rate = 0.00002466, float amount = 109666.7267, float fee = 0.002, float returns = 0, float reinvest = 1.0, bool buySig = false, bool sellSig = false);
};
