//
// Created by overflow on 2/11/18.
//
#include "logging.hpp"
#include <boost/utility/binary.hpp>
#include <cstdio>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <sstream>

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

    struct periodAVG {
	float basic;
	float byVol;
	float SMA5;
	float SMA10;
	float SMA30;
	float SMA50;
	float EMA10;
	float EMA30;
	float EMA50;
    } Avg;

    struct tradePeriod {
        unsigned short tPeriods{BOOST_BINARY(00000)};
	int initTimestamp;
        int initTXID;
        float openRate;
        int finalTimestamp;
        int finalTXID;
        float closeRate;
        float periodMin;
        float periodMax;
	int timeCat;
        std::vector <tradeData> individualTX{};
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
    virtual int PopCurrent();
/*
    virtual int PushHistorical(int index, int initTimestamp, int initTXID, float openRate,
        int finalTimestamp, int finalTXID, float closeRate, float periodMin, float periodMax,
        bool is10, bool is15, bool is20, bool is30, bool is60);
*/
    virtual void initThread();

    virtual void endThread();

    virtual void updateThread(Ticker *tickClass);
};


#endif //BITGRINDER_TRADEDATA_H
