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
#ifdef DEBUG
    std::string logLoc,logMsg, cTime, cDate;
    std::ofstream logFile;

std::cout << "[Debug] IN: dBasicLog\r\n";
std::cout << "[Debug] configFile = readConfig('./bin/');\r\n";

    nlohmann::json configFile = readConfig("./bin/");
    configFile["Application"]["Config"]["Logs"].dump();

//// Get time and date
boost::gregorian::date tdate(boost::gregorian::day_clock::local_day());
  boost::posix_time::ptime midnight(tdate);
  boost::posix_time::ptime 
     now(boost::posix_time::microsec_clock::local_time());
  boost::posix_time::time_duration td = now - midnight;
std::stringstream dstream, tstream;

  //std::cout << tdate << std::endl;

dstream << tdate.year() << "." << tdate.month().as_number() << "." << tdate.day();
tstream << td.hours() << ":" << td.minutes() << ":" << td.seconds() << "." << td.fractional_seconds();
cDate = dstream.str();
cTime = tstream.str();

    logLoc = "/opt/bitgrinder/system/logs/";logLoc.append(cDate);logLoc.append("-debug.");
    switch (lType) {
        case INIT:
            logLoc.append("init");
            break;
        case SYSTEM:
            logLoc.append("system");
            break;
        case TRADE:
            logLoc.append("trade");
            break;
        default:
            break;
    }
    switch (lSev) {
        case INFO:
            logMsg = "[--INFO--]  ";
            logMsg.append(cTime);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            break;
        case WARNING:
            logMsg = "[--WARN--]  ";
            logMsg.append(cTime);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            break;
        case ERROR:
            logMsg = "[!!ERROR!!]  ";
            logMsg.append(cTime);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            break;
        case CRITICAL:
            logMsg = "[!!CRITICAL!!]  ";
            logMsg.append(cTime);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
        default:
            logMsg = "[!!ERRORS 2!!]  ";
            logMsg.append(cTime);logMsg.append("  |  ");logMsg.append(msg);logMsg.append("\r\n");
            logMsg.append("Debug log severity not passed for above message.");logMsg.append("\r\n");
            break;
    }

    logFile.open (logLoc, std::ios::out | std::ios::ate | std::ios::app);
    logFile.write(logMsg.c_str(),logMsg.size());
    logFile.close();
#endif

}

