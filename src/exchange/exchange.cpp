#include "../include/exchange/exchange.h"

std::string buffer;

//Exchange::Exchange(void) : api_key(""), api_secret("")
Exchange::Exchange(std::string akey, std::string skey) : api_key{ akey }, api_secret{ skey }
{
    // Basic Gate.io functions init
    struct pairs getPairs;
    struct marketinfo getMarketInfo;
    struct marketlist getMarketList;
    struct tickers getTickers;
    struct ticker getTicker;
    struct orderbooks getOrderBooks;
    struct orderbook getOrderBook;
    struct balances getBalances;
    struct depositaddr getDepositAddr;
    struct depositswithdraws getDepositsWithdraws;
    struct buycmd doBuy;
    struct sellcmd doSell;
    struct cancelorder doCancelOrder;
    struct cancelallorders doCancelAllOrders;
    struct getorder getOrder;
    struct openorders getOpenOrders;
    struct thistory getTradeHistory;
    struct tjson jTradeHistory;
    struct withdraw doWithdraw;

}

float Exchange::getAPIlatency()
{
    auto started = std::chrono::high_resolution_clock::now();
    // Setup output redirect
    sendRequest(this->getBalances.URL, this->getBalances.params);
    auto done = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count();
}

nlohmann::json Exchange::sendRequest(std::string url, std::string params)
{
    nlohmann::json jsonResult;
    return jsonResult;
}

