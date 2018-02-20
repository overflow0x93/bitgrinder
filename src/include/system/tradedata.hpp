//
// Created by overflow on 2/11/18.
//
#include "logging.hpp"
#include <cstdio>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

#ifndef BITGRINDER_TRADEDATA_H
#define BITGRINDER_TRADEDATA_H

class Ticker {
public:
    struct windowVitals {
        int initialTimestamp{};
        int finalTimestap{};
        std::string currencyPair{""};
        std::string exchangeName{""};
    } vitals;

    struct tradeData {
        int txID;
        int txTimestamp;
        std::string buySell;
        float rate;
        float amount;
        float total;
    } tx;

    struct tradePeriod {
        int initTimestamp;
        int initTXID;
        float openRate;
        int finalTimestamp;
        int finalTXID;
        float closeRate;
        float periodMin;
        float periodMax;
        std::vector <tradeData> individualTX;
    } fullPeriod;

    struct currentPeriod {
        int initTimestamp{};
        int initTXID{};
        float openRate{};
        int finalTimestamp{};
        int finalTXID{};
        float closeRate{};
        float periodMin{};
        float periodMax{};
        std::vector <tradeData> individualTX{};
    } partPeriod;

private:
    std::string cPair;
    std::string eName;
    bool updActive = false;
public:
    std::vector <tradePeriod> PeriodTX;

    Ticker(std::string, std::string);

    ~Ticker();

    virtual int ReceiveTX();

    virtual int PushCurrent(int time, int txid, std::string type, float rate, float amount, float total);

    virtual void initThread();

    virtual void endThread();

    virtual void updateThread(Ticker *tickClass);
};


#endif //BITGRINDER_TRADEDATA_H
