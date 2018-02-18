//
// Created by overflow on 2/12/18.
//
#include "./json.hpp"
#include "./data.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <openssl/evp.h>

#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#ifndef BITGRINDER_CONFIG_H
#define BITGRINDER_CONFIG_H


class Config {
private:

    std::string decrypt(std::string encrypted);

    std::string encrypt(std::string unencrypted);

public:
    Config();

    ~Config();

    virtual std::string getAPI(std::string exchange);

    virtual std::string getSecret(std::string exchange);

    virtual void genConfig();

    virtual std::vector<std::string> getPositions(std::string exchange);
};

int setupConfig(std::string cfgLoc);

int initConfig(std::string ipath);

nlohmann::json readConfig(std::string cpath);


#endif //BITGRINDER_CONFIG_H
