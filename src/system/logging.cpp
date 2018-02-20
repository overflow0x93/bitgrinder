#include "../include/system/logging.hpp"

Log::Log()
{

}

Log::~Log()
{

}

void Log::BasicLog(logType lType, std::string msg)
{
    std::string logLoc;
    std::ofstream logFile;
    logFile.open (logLoc, std::ios::out | std::ios::ate | std::ios::app);
}

Debug::Debug() {

}

Debug::~Debug() {

}

void Debug::dBasicLog(logType lType, logSeverity lSev, std::string msg)
{
    std::string logLoc,logMsg, timeDate;
    std::ofstream logFile;
    nlohmann::json configFile = readConfig("./bin/data/config");
    configFile["Application"]["Config"]["Logs"].dump();
    switch (lType) {
        case INIT:
            logLoc = "./bin/data/log/init.log";
            break;
        case SYSTEM:
            logLoc = "./bin/data/log/system.log";
            break;
        case TRADE:
            logLoc = "./bin/data/log/trade.log";
            break;
        default:
            break;
    }
    switch (lSev) {
        case INFO:
            logMsg = "[      INFO      ]  |  ";
            logMsg.append(timeDate);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            break;
        case WARNING:
            logMsg = "[   ---WARN----  ]  |  ";
            logMsg.append(timeDate);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            break;
        case ERROR:
            logMsg = "[-----ERROR!-----]  |  ";
            logMsg.append(timeDate);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            break;
        case CRITICAL:
            logMsg = "[  !!CRITICAL!!  ]  |  ";
            logMsg.append(timeDate);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
        default:
            logMsg = "[---ERRORS (2)---]  |  ";
            logMsg.append(timeDate);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            logMsg.append("Debug log severity not passed for above message.");logMsg.append("\r\n");
            break;
    }

    logFile.open (logLoc, std::ios::out | std::ios::ate | std::ios::app);
    logFile.write(logMsg.c_str(),logMsg.size());
    logFile.close();
}

