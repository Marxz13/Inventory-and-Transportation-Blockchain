// FileOperations.cpp
#include <fstream> // Include for std::ofstream and std::ios
#include <iostream> // Include for std::cerr
#include <string> // Include for std::string
#include <sstream>
#include <cstring> // C strings and arrays utilities
#include "Blockchain.h"
#include "FileOperations.h"
#include <windows.h>

void searchForBlockByHashPattern(const std::string& hashPattern) {
    Blockchain blockchain;
    std::vector<std::string> txtFiles = listTxtFiles();

    for (const auto& file : txtFiles) {
        std::ifstream inFile(file);
        if (!inFile.is_open()) {
            std::cerr << "Error opening file: " << file << std::endl;
            continue;
        }

        std::string line;
        Block block;
        std::stringstream dataStream;
        bool isBlockInitialized = false;

        while (getline(inFile, line)) {
            if (line.rfind("Stage:", 0) == 0) { // Start of a new block
                if (isBlockInitialized) { // If a previous block was being processed
                    block.setInfo(dataStream.str()); // Assign the accumulated info to the block

                    // Check the hash pattern of the previous block
                    if (block.getCurrentHash().substr(0, 2) == hashPattern.substr(0, 2) &&
                        block.getCurrentHash().substr(block.getCurrentHash().size() - 4) == hashPattern.substr(hashPattern.size() - 4)) {

                        blockchain.printBlock(block);
                        std::cout << "Found in file: " << file << "\n";
                        inFile.close();
                        return; // Stop after finding the match
                    }

                    dataStream.str(""); // Clear stringstream for the next block
                    dataStream.clear();
                    block = Block(); // Reset block for the next one
                }

                isBlockInitialized = true; // Mark that we've started processing a block

                // Parse the line into block attributes
                std::istringstream headerStream(line);
                std::string token;
                while (getline(headerStream, token, ',')) {
                    size_t colonPos = token.find(':');
                    if (colonPos != std::string::npos) {
                        std::string key = token.substr(0, colonPos);
                        std::string value = token.substr(colonPos + 1);
                        if (key == "Stage") block.setId(stoi(value));
                        else if (key == "BlockID") block.setId(stoi(value));
                        else if (key == "CurrentHash") block.setCurrentHash(value);
                        else if (key == "PreviousHash") block.setPreviousHash(value);
                        else if (key == "Time") block.setTimestamp(value);
                    }
                }
            } else {
                // Accumulate block information content
                dataStream << line << "\n";
            }
        }

        // After finishing the file, check the last block
        if (isBlockInitialized) {
            block.setInfo(dataStream.str());
                if (block.getCurrentHash().substr(0, 2) == hashPattern.substr(0, 2) &&
                block.getCurrentHash().substr(block.getCurrentHash().size() - 4) == hashPattern.substr(hashPattern.size() - 4)) {
                blockchain.printBlock(block);
                std::cout << "Found in file: " << file << "\n";
                return; // Found the matching block
            }
        }
        inFile.close();
    }

    std::cout << "No block found with the specified hash pattern." << std::endl;
}
// Function to list all .txt files in the current directory
std::vector<std::string> listTxtFiles() {
    std::vector<std::string> files;
    WIN32_FIND_DATA fileData;
    HANDLE hFind = FindFirstFile("./*.txt", &fileData); // Search for .txt files

    // Loop through all found files and add their names to the vector
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            files.push_back(fileData.cFileName);
        } while (FindNextFile(hFind, &fileData) != 0);
        FindClose(hFind);
    }
    return files;
}

// Function to append a block's data to a file
void writeBlockToFile(const Block& block, const std::string& filename) {
    std::string filePath = filename + ".txt";

    // Open file in append mode
    std::ofstream outFile(filePath, std::ios::app);
    if (outFile.is_open()) {
        // Write formatted block data to file
        outFile << "Stage:" << block.getId() << ",";
        outFile << "BlockID:" << block.getId() << ",";
        outFile << "CurrentHash:" << block.getCurrentHash() << ",";
        outFile << "PreviousHash:" << block.getPreviousHash() << ",";
        outFile << "Time:" << block.getTimestamp() << ",";
        outFile << "Info:" << block.getInfo() << "\n";
        outFile.close();
    } else {
        // Error handling if file cannot be opened
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
}

// Function to display block information from a selected file
void displayBlockFromFile(const std::string& selectedFile) {
    Blockchain blockchain;
    std::ifstream inFile(selectedFile);
    if (!inFile.is_open()) {
        // Error handling if file cannot be opened
        std::cerr << "Error opening file: " << selectedFile << std::endl;
        return;
    }

    std::string line;
    Block block;
    std::stringstream dataStream;
    bool isFirstBlock = true;

    // Read file line by line
    while (getline(inFile, line)) {
        // Check if the line starts with "Stage:" indicating a new block
        if (line.rfind("Stage:", 0) == 0) {
            if (!isFirstBlock) {
                // Process and display the previous block before starting a new one
                block.setInfo(dataStream.str());
                blockchain.printBlock(block);

                // Clear stringstream for the next block
                dataStream.str("");
                dataStream.clear();
                block = Block();

                // Prompt user to press enter to view the next block
                std::cout << "\nPress enter to view next block...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getchar();
                system("cls"); // Clear console screen
                std::cout << "\n";
            }
            isFirstBlock = false;
            std::istringstream headerStream(line);
            std::string token;
            // Parse block header information
            while (getline(headerStream, token, ',')) {
                size_t colonPos = token.find(':');
                if (colonPos != std::string::npos) {
                    std::string key = token.substr(0, colonPos);
                    std::string value = token.substr(colonPos + 1);
                    // Assign values to the block based on the key
                    if (key == "Stage") block.setId(stoi(value));
                    else if (key == "BlockID") block.setId(stoi(value));
                    else if (key == "CurrentHash") block.setCurrentHash(value);
                    else if (key == "PreviousHash") block.setPreviousHash(value);
                    else if (key == "Time") block.setTimestamp(value);
                }
            }
        } else {
            // Collect block information content
            dataStream << line << "\n";
        }
    }

    // Display the last block if there is any data left
    if (!dataStream.str().empty()) {
        block.setInfo(dataStream.str());
        blockchain.printBlock(block);
    }

    inFile.close();
}
