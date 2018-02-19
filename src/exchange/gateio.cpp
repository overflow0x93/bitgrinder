#include <utility>

#include "../include/exchange/gateio.h"

std::string buffer;

GateIO::GateIO(std::string akey, std::string skey) : api_key{std::move(akey)}, api_secret{std::move(skey)} {
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
    struct athistory getAllTradeHistory;
    struct tjson jTradeHistory;
    struct withdraw doWithdraw;

    positionManager gatePositions;
//    gatePositions.initPosition();
    gatePositions.allPositions.push_back(gatePositions.tradePosition);
    std::vector<Ticker> gTickers;
}

float GateIO::getAPIlatency() {
    auto started = std::chrono::high_resolution_clock::now();
    // Setup output redirect
    sendRequest(this->getBalances.URL, this->getBalances.params);
    auto done = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count();
}

nlohmann::json GateIO::sendRequest(std::string url, std::string params) {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    std::string outBuffer;
    //nlohmann::json jsonResult;
    nlohmann::json jsonResult = {{"result", "fail"}};

    if (curl) {
        struct curl_slist *chunk = nullptr;
        std::string tURL = api_url;
        //tURL.append("");
        tURL.append(url);
        curl_easy_setopt(curl, CURLOPT_URL, tURL.c_str());
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        chunk = curl_slist_append(chunk, "Accept: application/x-www-form-urlencoded");
        chunk = curl_slist_append(chunk, "Content-type: application/x-www-form-urlencoded");
        chunk = curl_slist_append(chunk, "Charsets: utf-8");

        std::string parameters = params;

        // Attempt to write results to buffer for processing
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outBuffer);
        chunk = curl_slist_append(chunk, "Accept:");

        if (!params.empty()) { // if (params != "") {
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, parameters.length());
            parameters = jsonToSign(params);
            std::string keyHeader = "KEY: " + api_key;
            chunk = curl_slist_append(chunk, keyHeader.c_str());
/// HMAC ///////////////////////////////////////////////

// Parameters require post data::
            //curl_easy_setopt(curl, CURLOPT_POST, 0L);
            curl_easy_setopt(curl, CURLOPT_POST, 1L);

            //std::string sysCmd = "echo -n '";sysCmd.append(params);sysCmd.append("'");               //;sysCmd.append(api_key);sysCmd.append("&'");
            std::string sysCmd = "echo -n '";
            sysCmd.append(jsonToSign(params));
            sysCmd.append("'");               //;sysCmd.append(api_key);sysCmd.append("&'");
            ///////////////////////////////////////////////////////
            // THIS IS WORKING SIGN
            //echo -n "currencyPair=eos_eth&orderNumber=" | openssl dgst -sha512 -mac HMAC -macopt key:3ed0749c03cdbf8e21b6e49d6eb1e65d388e258c2556fc2c4ae4f437028669dc | cut -c 10
            ///////////////////////////////////////////////////////
            sysCmd.append(
                    " | openssl dgst -sha512 -mac HMAC -macopt key:3ed0749c03cdbf8e21b6e49d6eb1e65d388e258c2556fc2c4ae4f437028669dc | cut -c 10-");

            // Clean up output from system call
            std::array<char, 128> buffer{};
            std::string result;
            std::shared_ptr<FILE> pipe(popen(sysCmd.c_str(), "r"), pclose);
            if (!pipe) throw std::runtime_error("popen() failed!");
            while (!feof(pipe.get())) {
                if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
                    result += buffer.data();
            }
            // Create  header
            std::string signHeader;
            signHeader.append("SIGN: ");
            result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
            result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());

            signHeader.append(result);
            signHeader.append("");

////////////////////////////////////////////////////////
            // Finalize headers
            chunk = curl_slist_append(chunk, signHeader.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            jsonResult = {{"result", "fail"}};
            //json jsonResult = {{"result":"fail"}};
        } else {
            auto j3 = nlohmann::json::parse(outBuffer);
            jsonResult = j3;
        }
        // always cleanup
        curl_easy_cleanup(curl);

        // free the custom headers
        curl_slist_free_all(chunk);
    }
    return jsonResult;
}

nlohmann::json GateIO::joinTradeData(nlohmann::json currentTradeData, nlohmann::json addTradeData) {
    return currentTradeData;
}

nlohmann::json GateIO::getFullTradeData(int startTradeID, nlohmann::json addTradeData) {
    nlohmann::json currentTradeData;
    return currentTradeData;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string *) userp)->append((char *) contents, size * nmemb);
    return size * nmemb;
}

std::string jsonToSign(nlohmann::json params) {
    std::string signValue;

    //std::cout << params.dump() << "\r\n";
    signValue = params.dump();
    std::replace(signValue.begin(), signValue.end(), ':', '=');
    std::replace(signValue.begin(), signValue.end(), ',', '&');
    std::replace(signValue.begin(), signValue.end(), '{', ' ');
    std::replace(signValue.begin(), signValue.end(), '}', ' ');
    std::replace(signValue.begin(), signValue.end(), '"', ' ');
    std::replace(signValue.begin(), signValue.end(), '\\', ' ');
    //std::cout << signValue << "\r\n";
    signValue.erase(std::remove(signValue.begin(), signValue.end(), ' '), signValue.end());

    //std::cout << signValue << "\r\n";
    return signValue;
}
