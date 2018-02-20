#include "exchange/gateio.hpp"
#include "system/logging.hpp"
//#include "./system/tradedata.h"
#include "./system/json.hpp"
#include "system/config.hpp"
//#include "./system/data.h"
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <thread>
#include <chrono>
//#include <fstream>

int init();

void update();

int console(GateIO masterExchange);
