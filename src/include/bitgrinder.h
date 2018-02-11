#include "./exchange/gateio.h"
#include "./system/data.h"
#include "./system/json.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <curl/curl.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <fstream>
// Output test
#include <sstream>

int init();
void update();
int console(GateIO masterExchange);
