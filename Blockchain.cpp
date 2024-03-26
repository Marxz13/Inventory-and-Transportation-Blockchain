#include "Blockchain.h"
#include "Block.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
// Keep these static variables in the implementation file to avoid redefinition errors
static int hashCounter = 0; // Counter for hashes to ensure uniqueness
static std::random_device rd; // Non-deterministic random number generator
static std::mt19937 generator(rd()); // Mersenne Twister pseudo-random generator

void Blockchain::addBlock(int stage) {
    Block newBlock;
    newBlock.setId(chain.empty() ? 1 : chain.back().getId() + 1);
    newBlock.setInfo(collectData(static_cast<Stage>(stage), false));
    newBlock.setPreviousHash(chain.empty() ? "genesis_hash" : chain.back().getCurrentHash());
    newBlock.setCurrentHash(generateRandomHash());
    newBlock.setTimestamp(getCurrentTime());
    chain.push_back(newBlock);
}
void Blockchain::addBlockFromFile(Stage stage, const std::string& data) {
    Block newBlock;
    newBlock.setId(this->chain.empty() ? 1 : this->chain.back().getId() + 1);
    newBlock.setPreviousHash(this->chain.empty() ? "0" : this->chain.back().getCurrentHash());
    newBlock.setCurrentHash(this->generateRandomHash());
    newBlock.setTimestamp(this->getCurrentTime());
    newBlock.setInfo(data);
    this->chain.push_back(newBlock);
}

void Blockchain::printBlock(const Block& block) {
    // Function to print block information in a formatted manner
    std::cout << "--------------------- " << "Stage " << block.getId() << " ---------------------" << std::endl;
    std::cout << "\n";
    std::cout << "Block ID      : " << block.getId() << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << "Timestamp     : " << block.getTimestamp() << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << "Previous Hash : " << block.getPreviousHash() << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << "Current Hash  : " << block.getCurrentHash() << std::endl;
    std::cout << "--------------" << std::endl;
    std::cout << block.getInfo() << std::endl;
    std::cout << "\n---------------------------------------------------" << std::endl;
}

std::string Blockchain::generateRandomHash() {
    // Function to generate a random hash
    const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string randHash;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 localGenerator(seed);

    std::uniform_int_distribution<> distribution(0, chars.size() - 1);

    for (int i = 0; i < 20; i++) {
        randHash += chars[distribution(localGenerator)];
    }
    auto t = std::time(nullptr);
    randHash += std::to_string(t) + std::to_string(hashCounter++); // Append time and counter to ensure uniqueness

    return randHash;
}

std::string Blockchain::getCurrentTime() {
    // Function to get current time formatted as YYYY-MM-DD HH:MM:SS
    std::time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}
std::vector<std::string> Blockchain::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    // Extract each token by delimiter and add to the vector
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}
std::string Blockchain::collectData(Stage stage, bool isFileInput, const std::string& data) {
    std::stringstream dataStream;
    std::vector<std::string> tokens;
    if (isFileInput) {
        tokens = splitString(data, ';');
    }
    switch (stage) {
        case Manufacturing:
            {
                std::string farmID, farmLocation, quantity, harvestDate, practiceDetails, plantationCertificate, batchNumber;
                if (isFileInput && tokens.size() >= 7) {
                    farmID = tokens[0];
                    farmLocation = tokens[1];
                    quantity = tokens[2];
                    harvestDate = tokens[3];
                    practiceDetails = tokens[4];
                    plantationCertificate = tokens[5];
                    batchNumber =  tokens[6];
                } else {
                    std::cout << "Enter Farm ID                : ";
                    getline(std::cin, farmID);
                    std::cout << "Enter Farm Location          : ";
                    getline(std::cin, farmLocation);
                    std::cout << "Enter Quantity               : ";
                    getline(std::cin, quantity);
                    std::cout << "Enter Harvest Date           : ";
                    getline(std::cin, harvestDate);
                    std::cout << "Enter Process Details        : ";
                    getline(std::cin, practiceDetails);
                    std::cout << "Enter Plantation Certificate : ";
                    getline(std::cin, plantationCertificate);
                    std::cout << "Enter Batch Number           : ";
                    getline(std::cin, batchNumber);
                }
                dataStream
                    << "\nFarm ID                 : " << farmID
                    << "\nFarm Location           : " << farmLocation
                    << "\nQuantity                : " << quantity
                    << "\n"
                    << "\nHarvest Date            : " << harvestDate
                    << "\nProcess Details         : " << practiceDetails
                    << "\n"
                    << "\nBatch Number            : " << batchNumber
                    << "\nPlantation Certificate  : " << plantationCertificate;
            }
            break;
        case QualityAssurance:
            {
                std::string inspectionDate, inspectorName, QAReportID, QAResultTest, nonConformanceReports, approvalStatus;
                if (isFileInput && tokens.size() >= 6) {
                    inspectionDate = tokens[0];
                    inspectorName = tokens[1];
                    QAReportID = tokens[2];
                    QAResultTest = tokens[3];
                    nonConformanceReports = tokens[4];
                    approvalStatus = tokens[5];
                }
                else{
                    std::cout << "Enter Inspection Date               : ";
                    getline(std::cin, inspectionDate);
                    std::cout << "Enter Inspector Name                : ";
                    getline(std::cin, inspectorName);
                    std::cout << "Enter Report ID                     : ";
                    getline(std::cin, QAReportID);
                    std::cout << "Enter Quality Test Result           : ";
                    getline(std::cin, QAResultTest);
                    std::cout << "Enter Non-Conformance Reports       : ";
                    getline(std::cin, nonConformanceReports);
                    std::cout << "Enter Approval Status               : ";
                    getline(std::cin, approvalStatus);
                }
                dataStream
                << "\nInspection Date         : " << inspectionDate
                << "\nInspector Name          : " << inspectorName
                << "\n"
                << "\nQA Report ID            : " << QAReportID
                << "\nQA Test Result          : " << QAResultTest
                << "\nNon-Conformance Reports : " << nonConformanceReports
                << "\nApproval Status         : " << approvalStatus;
            }
            break;
        case Packaging:
            {
                std::string packageDate, packageType, quantityPackaged, packageLine, labelInfo;
                if (isFileInput && tokens.size() >= 5) {
                    packageDate= tokens[0];
                    packageType = tokens[1];
                    quantityPackaged = tokens[2];
                    packageLine = tokens[3];
                    labelInfo = tokens[4];
                }
                else{
                    std::cout << "Enter Packaging Date       : ";
                    getline(std::cin, packageDate);
                    std::cout << "Enter Packaging Type       : ";
                    getline(std::cin, packageType);
                    std::cout << "Enter Quantity Packaged    : ";
                    getline(std::cin, quantityPackaged);
                    std::cout << "Enter Package Line         : ";
                    getline(std::cin, packageLine);
                    std::cout << "Enter Label Information    : ";
                    getline(std::cin, labelInfo);
                }
                dataStream
                << "\nPackaging Date       : " << packageDate
                << "\nPackaging Type       : " << packageType
                << "\n"
                << "\nQuantity Packaged    : " << quantityPackaged
                << "\nPackage Line         : " << packageLine
                << "\n"
                << "\nLabel Information    : " << labelInfo;
            }
            break;
        case Warehousing:
            {
                std::string warehouseID, warehouseName, storageLocation, storageCondition, securityMeasures, inventoryLevel;
                if (isFileInput && tokens.size() >= 6) {
                    warehouseID = tokens[0];
                    warehouseName = tokens[1];
                    storageLocation = tokens[2];
                    storageCondition = tokens[3];
                    securityMeasures = tokens[4];
                    inventoryLevel = tokens[5];
                }
                else{
                    std::cout << "Enter Warehouse ID         : ";
                    getline(std::cin, warehouseID);
                    std::cout << "Enter Warehouse Name       : ";
                    getline(std::cin, warehouseName);
                    std::cout << "Enter Warehouse Location   : ";
                    getline(std::cin, storageLocation);
                    std::cout << "Enter Security Measures    : ";
                    getline(std::cin, securityMeasures);
                    std::cout << "Enter Storage Condition    : ";
                    getline(std::cin, storageCondition);
                    std::cout << "Enter Inventory Level      :  ";
                    getline(std::cin, inventoryLevel);
                }
                dataStream
                << "\nWarehouse ID       : " << warehouseID
                << "\nWarehouse Name     : " << warehouseName
                << "\n"
                << "\nStorage Location   : " << storageLocation
                << "\nStorage Condition  : " << storageCondition
                << "\n"
                << "\nSecurity Measures  : " << securityMeasures
                << "\nInventory Level    : " << inventoryLevel;
            }
            break;
        case Transportation:
            {
                std::string transport, departDate, estArrivalDate, temperatureControl, routeInformation, carrierInformation;
                if (isFileInput && tokens.size() >= 6) {
                    transport = tokens[0];
                    departDate = tokens[1];
                    estArrivalDate = tokens[2];
                    temperatureControl = tokens[3];
                    routeInformation = tokens[4];
                    carrierInformation = tokens[5];
                }
                else{
                    std::cout << "Enter Transport Type                                                                  : ";
                    getline(std::cin, transport);
                    std::cout << "Enter Departure Date                                                                  : ";
                    getline(std::cin, departDate);
                    std::cout << "Enter Estimated Arrival Date                                                          : ";
                    getline(std::cin, estArrivalDate);
                    std::cout << "Enter temperature Control                                                             : ";
                    getline(std::cin, temperatureControl);
                    std::cout << "Enter Route Information (including transit points)                                    : ";
                    getline(std::cin, routeInformation);
                    std::cout << "Enter Carrier Information (including sustainability practices and compliance records) : ";
                    getline(std::cin, carrierInformation);
                }
                dataStream
                << "Transport Type           :  " << transport
                << "\n"
                << "\nDeparture Date         : " << departDate
                << "\nEstimated Arrival Date : " << estArrivalDate
                << "\n"
                << "\nTemperature Control    : " << temperatureControl
                << "\nRoute Information      : " << routeInformation
                << "\nCarrier Information    : " << carrierInformation;
            }
            break;
        case RetailShelving:
            {
                std::string shelvingDate, storeLocation, shelfLife, promotionalInfo, customerFeedback;
                if (isFileInput && tokens.size() >= 5) {
                    shelvingDate = tokens[0];
                    storeLocation = tokens[1];
                    shelfLife = tokens[2];
                    promotionalInfo = tokens[3];
                    customerFeedback = tokens[4];
                }
                else{
                    std::cout << "Enter Shelving date           : ";
                    getline(std::cin, shelvingDate);
                    std::cout << "Enter Store Location          : ";
                    getline(std::cin, storeLocation);
                    std::cout << "Enter Shelf Life              : ";
                    getline(std::cin, shelfLife);
                    std::cout << "Enter Promotional Information : ";
                    getline(std::cin, promotionalInfo);
                    std::cout << "Enter Customer Feedback       : ";
                    getline(std::cin, customerFeedback);
                }
                dataStream
                    << "\nShelving date           :  " << shelvingDate
                    << "\nStore Location          : " << storeLocation
                    << "\nShelf Life              : " << shelfLife
                    << "\n"
                    << "\nPromotional Information : " << promotionalInfo
                    << "\n"
                    << "\nCustomer Feedback       : " << customerFeedback;
            }
            break;
        default:
            std::cout << "Unknown stage";
            return "";
    }
    return dataStream.str();
}


