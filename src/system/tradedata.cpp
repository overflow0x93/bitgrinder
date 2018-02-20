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

void Ticker::initThread() {
    updActive = true;
    std::thread updThread(&Ticker::updateThread, *this, this);
    updThread.detach();
}

void Ticker::endThread() {
    updActive = false;
}

void Ticker::updateThread(Ticker *tickClass) {
    // Check if current time > previous period + 5m
// Move current period into period list
    #ifdef DEBUG
    std::string outMsg = "[T] Thread created.";
    Debug::dBasicLog(INIT,INFO,outMsg);
    #endif
    //printf("[T] Thread Started\n");
    while (updActive) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    printf("[T] Thread Ended\n");
}

