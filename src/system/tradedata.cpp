//
// Created by overflow on 2/11/18.
//
#include <utility>

#include "../include/system/tradedata.hpp"

Ticker::Ticker(std::string pair, std::string exchange) : cPair{std::move(pair)}, eName{std::move(exchange)} {
    struct windowVitals vitals;
    struct tradeData tx;
    struct tradePeriod fullPeriod;
    struct currentPeriod partPeriod;
    initThread();
    //std::vector<tradePeriod> dWindow;
    //std::vector<tradeData> partPeriod.individualTX;
}

Ticker::~Ticker() {

}

int Ticker::ReceiveTX() {
    return 0;
}

int Ticker::PushCurrent(int time, int txid, std::string type, float rate, float amount, float total) {
    tradeData ctx;
    ctx.txID = txid;
    ctx.txTimestamp = time;
    ctx.buySell = type;
    ctx.rate = rate;
    ctx.amount = amount;
    ctx.total = total;
//std::cout << gVenEth.tx.txID << " " << gVenEth.tx.txTim$
    partPeriod.individualTX.push_back(ctx);

    return 0;
}
int Ticker::PopCurrent() {
    return 0;
}

/*
int Ticker::PushHistorical(int index, int initTimestamp, int initTXID, float openRate, 
	int finalTimestamp, int finalTXID, float closeRate, float periodMin, float periodMax,
        bool is10, bool is15, bool is20, bool is30, bool is60) {
    tradeData ctx;
    ctx.txID = txid;
    ctx.txTimestamp = time;
    ctx.buySell = type;
    ctx.rate = rate;
    ctx.amount = amount;
    ctx.total = total;
//std::cout << gVenEth.tx.txID << " " << gVenEth.tx.txTim$
    fullPeriod.individualTX.push_back(ctx);

    return 0;

}
*/ 

void Ticker::initThread() {
    updActive = true;
    std::thread updThread(&Ticker::updateThread, *this, this);
    updThread.detach();
}

void Ticker::endThread() {
    updActive = false;
}

void Ticker::updateThread(Ticker *tickClass) {
    int count,cTXsize;
    std::cout << tickClass->vitals.currencyPair;
    std::string cTXpair = tickClass->vitals.currencyPair;
    transform(cTXpair.begin(), cTXpair.end(), cTXpair.begin(), toupper);
    std::cout << "[T-" << cTXpair << "] Thread started.\r\n";
#ifdef DEBUG
    std::string outMsg = "[T][";outMsg.append(cTXpair);outMsg.append("] Thread created.");
    Debug::dBasicLog(INIT,INFO,outMsg);
#endif
    //printf("[T] Thread Started\n");
    while (updActive) {
        //assert(tickClass->partPeriod.individualTX.size() > cTXsize);
        // Above fails
        //std::stringstream sizest;
        //sizest << cTXsize;
        // Check if current time > previous period + 5m
        // Move current period into period list
        std::this_thread::sleep_for(std::chrono::seconds(30));
#ifdef DEBUG
        //outMsg = "[T][";outMsg.append(cTXpair);outMsg.append("] Update process:\r\n                             ");
        //outMsg.append(sizest.str());outMsg.append(" TX records waiting to process.");
        //Debug::dBasicLog(INIT,INFO,outMsg);
#endif
        //while (count < cTXsize) {
            //std::cout << partPeriod.individualTX[count].rate;
            // likely null
        //}
    }
#ifdef DEBUG
    outMsg = "[T][";outMsg.append(cTXpair);outMsg.append("] Thread killed.");
    Debug::dBasicLog(INIT,INFO,outMsg);
#endif
}

/*
Multiplier: (2 / (Time periods + 1) ) = (2 / (10 + 1) ) = 0.1818 (18.18%)
EMA: {Close - EMA(previous day)} x multiplier + EMA(previous day)
*/
