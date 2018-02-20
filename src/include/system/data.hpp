#include "json.hpp"

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sys/stat.h>
#include <unistd.h>

//std::vector jsonToVector(nlohmann::json jobj, std::string str, auto value);
std::vector<nlohmann::json> jsonToVector(nlohmann::json jsonInput);
std::vector<nlohmann::json> appendJsonDataVector(std::vector<nlohmann::json> vectorToAppend, nlohmann::json jsonToAdd);
nlohmann::json appendJsonData(nlohmann::json jsonToAppend, nlohmann::json jsonToAdd);

nlohmann::json readJsonBinary(std::string targetFile);
int writeJsonBinary(nlohmann::json targetJson, std::string targetFile);
//inline bool exists(const std::string &name);
