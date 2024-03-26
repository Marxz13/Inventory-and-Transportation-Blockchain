#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "Block.h"
#include <vector>
#include <random>
#include <chrono>
#include <ctime>
#include <string>
class Blockchain {
public:
    void addBlock(int stage);
    void addBlockFromFile(Stage stage, const std::string& data);
    void printBlock(const Block& block);
    std::string collectData(Stage stage, bool isfileInput, const std::string& data = "");
    std::string generateRandomHash();
    std::string getCurrentTime();
    const std::vector<Block>& getChain() const { return chain; }
    std::vector<std::string> splitString(const std::string& str, char delimiter);
private:
    std::vector<Block> chain;
};

#endif // BLOCKCHAIN_H
