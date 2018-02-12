//
// Created by overflow on 2/11/18.
//
#include "../include/system/tradedata.h"

Ticker::Ticker(std::string pair, std::string exchange) : cPair{ pair }, eName{ exchange }
{
    struct windowVitals vitals;
    struct tradeData tx;
    struct tradePeriod fullPeriod;
    struct currentPeriod partPeriod;
    std::vector<tradePeriod> dWindow;
}

int Ticker::ReceiveTX()
{
    return 0;
}
