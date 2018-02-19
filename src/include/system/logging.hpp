#include "./config.h"
#include <stdio>

#ifndef BITGRINDER_LOGGING_HPP
#define BITGRINDER_LOGGING_HPP

class Log {

private:
	int WriteToFile(std::string msg, std::string fileLocation);

public:
	Log();
	~Log();

}

class Debug : public Log {

private:

public:
	Debug();
	~Debug();
}

#endif //BITGRINDER_LOGGING_HPP
