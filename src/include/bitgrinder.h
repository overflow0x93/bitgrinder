#include "./exchange/gateio.h"
//#include "./system/tradedata.h"
#include "./system/json.hpp"
#include "./system/config.h"
//#include "./system/data.h"
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <thread>
//#include <fstream>

int init();

void update();

int console(GateIO masterExchange);
