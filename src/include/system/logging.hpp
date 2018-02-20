#include "config.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>

#ifndef BITGRINDER_LOGGING_HPP
#define BITGRINDER_LOGGING_HPP

enum logType {
    INIT, SYSTEM, TRADE
};
enum logSeverity {
    INFO, WARNING, ERROR, CRITICAL
};

class Log {

private:
    int WriteToFile(std::string msg, std::string fileLocation);

public:
    Log();

    ~Log();

    static void BasicLog(logType lType = SYSTEM, std::string msg = "");
};

class Debug : public Log {

private:

public:
    Debug();

    ~Debug();

    static void dBasicLog(logType lType = SYSTEM, logSeverity lSev = CRITICAL, std::string msg = "");
};

#endif //BITGRINDER_LOGGING_HPP
