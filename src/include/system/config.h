//
// Created by overflow on 2/12/18.
//
#include "./json.hpp"
#include "./data.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>
#include <string>

#ifndef BITGRINDER_CONFIG_H
#define BITGRINDER_CONFIG_H


int setupConfig();
int initConfig(std::string ipath);
nlohmann::json readConfig(std::string cpath);
#endif //BITGRINDER_CONFIG_H
