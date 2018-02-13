#include "../system/json.hpp"
#include "./position.h"

#include <chrono>
#include <curl/curl.h>
#include <iostream>
#include <string>

class GateIO
{
public:
    struct baseRequest{
        std::string URL{""};
        std::string params{""};
    };
    struct pairs : baseRequest{
        std::string URL{"/api2/1/pairs"};
        std::string params{""};
    } getPairs;
    struct marketinfo : baseRequest{
        std::string URL{"/api2/1/marketinfo"};
        std::string params{""};
    } getMarketInfo;
    struct marketlist : baseRequest{
        std::string URL{"/api2/1/marketlist"};
        std::string params{""};
    } getMarketList;
    struct tickers : baseRequest{
        std::string URL{"/api2/1/tickers"};
        std::string params{""};
    } getTickers;
    struct ticker : baseRequest{
        std::string URL{"/api2/1/ticker"};
        std::string params{""};
    } getTicker;
    struct athistory : baseRequest{
        std::string URL{"/api2/1/tradeHistory/"};
        std::string PAIR{"ven_eth"};
        std::string TID{"130000000"}; // Trade ID #30000000 Dec 2017
        std::string params{""};
    } getAllTradeHistory;

    struct orderbooks : baseRequest{
        std::string URL{"/api2/1/orderBooks"};
        std::string params{""};
    } getOrderBooks;
    struct orderbook : baseRequest{
        std::string URL{"/api2/1/orderBook"};
        std::string params{""};
    } getOrderBook;
    struct balances : baseRequest{
        std::string URL{"/api2/1/private/balances"};
        std::string params{"{}"};
    } getBalances;
    struct depositaddr : baseRequest{
        std::string URL{"/api2/1/private/depositAddress"};
        nlohmann::json params{"currency="}; // {'currency':param}
    } getDepositAddr;
    struct depositswithdraws : baseRequest{
        std::string URL{"/api2/1/private/depositsWithdrawals"};
        nlohmann::json params{"start=&end="}; //
    } getDepositsWithdraws;
    struct buycmd : baseRequest{
        std::string URL{"/api2/1/private/buy"};
        nlohmann::json params{"currencyPair=&rate=&amount="}; // {'currencyPair': currencyPair,'rate':rate,'amount':amount}
    } doBuy;
    struct sellcmd : baseRequest{
        std::string URL{"/api2/1/private/sell"};
        nlohmann::json params{"currencyPair=&rate=&amount="}; // {'currencyPair': $
    } doSell;
    struct cancelorder : baseRequest{
        std::string URL{"/api2/1/private/cancelOrder"};
        nlohmann::json params{"orderNumber=&currencyPair="}; // {'currencyPair': $
    } doCancelOrder;
    struct cancelallorders : baseRequest{
        std::string URL{"/api2/1/private/cancelAllOrders"};
        nlohmann::json params{"type=&currencyPair="}; // {'currencyPair': $
    } doCancelAllOrders;
    struct getorder : baseRequest{
        std::string URL{"/api2/1/private/getOrder"};
        nlohmann::json params{""}; // {'currencyPair': $
    } getOrder;
    struct openorders : baseRequest{
        std::string URL{"/api2/1/private/openOrders"};
        std::string params{""};
    } getOpenOrders;
    struct thistory : baseRequest{
        std::string URL{"/api2/1/private/tradeHistory"};
        nlohmann::json params{{"currencyPair","ven_eth"},{"orderNumber",""}};
    } getTradeHistory;
    struct tjson : baseRequest{
        std::string URL{"/api2/1/private/tradeHistory"};
        nlohmann::json params{{"currencyPair","ven_eth"},{"orderNumber",""}};
    } jTradeHistory;

    struct withdraw : baseRequest{
        std::string URL{"/api2/1/private/withdraw"};
        nlohmann::json params{"currency=&amount=&address="};
    } doWithdraw;

private:
    std::string api_key;
    std::string api_secret; //key;
    std::string api_url{"http://data.gate.io"};

public:
    GateIO(std::string, std::string);
    positionManager gatePositions;
    float getAPIlatency();
    //void sendRequest(std::string url, std::string params);
    nlohmann::json sendRequest(std::string url, std::string params);
    nlohmann::json joinTradeData(nlohmann::json currentTradeData, nlohmann::json addTradeData);
    nlohmann::json getFullTradeData(int startTradeID, nlohmann::json addTradeData);
};

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
std::string string_to_hex(const std::string& input);
std::string jsonToSign(nlohmann::json params);
void removeSpaces(char *str);
