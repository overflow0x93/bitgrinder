#include "../include/system/data.h"

std::vector<nlohmann::json> jsonToVector(nlohmann::json jsonInput) {
    std::vector<nlohmann::json> vToReturn;
    return vToReturn;
}

std::vector<nlohmann::json> appendJsonDataVector(std::vector<nlohmann::json> vectorToAppend, nlohmann::json jsonToAdd) {
    int amtToAppend = jsonToAdd["data"].size();
    int count = 0;
    while (count < amtToAppend) {
        vectorToAppend.push_back(jsonToAdd["data"][count]);
        ++amtToAppend;
    }
    return vectorToAppend;
}

nlohmann::json appendJsonData(nlohmann::json jsonToAppend, nlohmann::json jsonToAdd) {
    int amtToAppend = jsonToAdd["data"].size();
    int count = 0;
    while (count < amtToAppend) {
        jsonToAppend["data"].push_back(jsonToAdd["data"][count]);
        amtToAppend++;
    }
    return jsonToAppend;
}

std::vector<nlohmann::json> vecSortByKey(nlohmann::json jsonInput, std::string keyname, enum varType varTypeToSort) {
    // Agnostic sorting of json
    std::vector<nlohmann::json> vToReturn;

    switch (varTypeToSort) {
        case vFLOAT:
            break;
        case vINT:
            break;
        case vSTRING:
            break;
        default:
            return vToReturn;
    }
    return vToReturn;
}

nlohmann::json readJsonBinary(std::string targetFile) {
    std::ifstream input_file(targetFile, std::ios::binary);
    std::vector<uint8_t> input_vector(
            (std::istreambuf_iterator<char>(input_file)),
            std::istreambuf_iterator<char>());

    nlohmann::json outFile = nlohmann::json::from_cbor(input_vector);
    return outFile;
}

int writeJsonBinary(nlohmann::json targetJson, std::string targetFile) {
    std::ofstream output_file(targetFile, std::ios::out | std::ios::binary);
    std::cout << targetFile << "\r\n";
    std::vector<uint8_t> output_vector;
    nlohmann::json::to_cbor(targetJson, output_vector);
    output_file.write(reinterpret_cast<const char *>(output_vector.data()), output_vector.size());
    return 0;
}