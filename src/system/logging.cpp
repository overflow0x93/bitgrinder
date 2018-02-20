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
    std::string logLoc,logMsg, cTime, cDate;
    std::ofstream logFile;

namespace pt = boost::posix_time;
pt::ptime now = pt::second_clock::local_time();
std::stringstream ss;
ss << static_cast<int>(now.date().day() <<  now.date().month()) << now.date().year();
cDate = ss.str().c_str();
#ifdef DEBUG
std::cout << "[Debug] IN: dBasicLog\r\n";
std::cout << "[Debug] configFile = readConfig('./bin/');\r\n";
#endif
    nlohmann::json configFile = readConfig("./bin/");
    configFile["Application"]["Config"]["Logs"].dump();
    switch (lType) {
        case INIT:
            logLoc = "/opt/bitgrinder/system/logs/debug.init-";
            break;
        case SYSTEM:
            logLoc = "/opt/bitgrinder/system/logs/debug.system-";
            break;
        case TRADE:
            logLoc = "/opt/bitgrinder/system/logs/debug.trade-";
            break;
        default:
            break;
    }
	logLoc.append(cDate);
    switch (lSev) {
        case INFO:
            logMsg = "[      INFO      ]   ";
            logMsg.append(cTime);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            break;
        case WARNING:
            logMsg = "[   ---WARN----  ]   ";
            logMsg.append(cTime);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            break;
        case ERROR:
            logMsg = "[-----ERROR!-----]   ";
            logMsg.append(cTime);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            break;
        case CRITICAL:
            logMsg = "[  !!CRITICAL!!  ]   ";
            logMsg.append(cTime);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
        default:
            logMsg = "[---ERRORS (2)---]   ";
            logMsg.append(cTime);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            logMsg.append("Debug log severity not passed for above message.");logMsg.append("\r\n");
            break;
    }

    logFile.open (logLoc, std::ios::out | std::ios::ate | std::ios::app);
    logFile.write(logMsg.c_str(),logMsg.size());
    logFile.close();
}

