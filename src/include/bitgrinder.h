#include "./exchange/gateio.h"
//#include "./system/tradedata.h"
#include "./system/json.hpp"
#include "./system/config.h"
//#include "./system/data.h"
#include <csignal>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <thread>
//#include <fstream>

int init();
void update();
int console(GateIO masterExchange);
