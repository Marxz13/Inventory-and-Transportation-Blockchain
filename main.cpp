#include <iostream> // Standard input-output stream
#include <sstream> // String stream
#include <fstream> // File stream
#include <windows.h> // Sleep
#include<unistd.h>

#include "Block.h"
#include "Blockchain.h"
#include "Authentication.h"
#include "FileOperations.h"
using namespace std;

// Converts the Stage enumeration to a human-readable string
string stageToString(Stage stage) {
    switch (stage) {
        case Manufacturing: return "Manufacturing";
        case QualityAssurance: return "Quality Assurance";
        case Packaging: return "Packaging";
        case Warehousing: return "Warehousing";
        case Transportation: return "Transportation";
        case RetailShelving: return "Retail Shelving";
        default: return "Unknown";
    }
}

int main() {
    login(); // User : admin - Pass : admin
    Blockchain blockchainFunction;
    Block block;

    Stage currentStage = Manufacturing; // Sets the initial stage of the blockchain
    int lastId = 0;
    string lastHash;

    bool startSystem = true;
    while (startSystem) {
        system("cls");
        if (cin.fail()) {
            cin.clear();
            // Clears cin state and ignores the rest of the line if an input error occurs
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // Displays the main menu options to the user
        cout << "*-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*" << endl;
        cout << "*           Please enter a command:                *" << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
        cout << "*      ( 1 ) Enter New Block                       *" << " *   * " << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
        cout << "*      ( 2 ) View BlockChain Product               *" << "   M   " << endl;
        cout << "*--------------------------------------------------*" << " A   R " << endl;
        cout << "*      ( 3 ) Save Current Blockchain               *" << "   Z   " << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
        cout << "*      ( 4 ) Search Blockchain                     *" << " *   * " << endl;
        cout << "*--------------------------------------------------*" << "   *   " << endl;
        cout << "*      ( 5 ) Exit                                  *" << endl;
        cout << "*-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*" << endl;
        cout << "\n> ";
        int command;
        cin >> command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (command) {
        case 1: {
            // Handles the logic for adding a new block to the blockchain
            system("cls");
            cout << "Choose method to add block:" << endl;
            cout << "1. Manually" << endl;
            cout << "2. Generate from file" << endl;
            int methodChoice;
            cin >> methodChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (methodChoice == 1) {
                blockchainFunction.addBlock(currentStage);
            } else if (methodChoice == 2) {
                system("cls");
                vector<string> files = listTxtFiles();

                if (files.empty()) {
                    cout << "No .txt files found in the directory." << endl;
                } else {
                    cout << "Select a file to create a block:" << endl;
                    for (size_t i = 0; i < files.size(); ++i) {
                        cout << i + 1 << ": " << files[i] << endl;
                    }
                    cout << "Enter the number of your choice: ";
                    int choice;
                    cin >> choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (choice > 0 && choice <= files.size()) {
                        string filename = files[choice - 1];

                        ifstream inFile(filename);
                        if (!inFile.is_open()) {
                            cout << "Error opening file." << endl;
                            break;
                        }
                        string fileContents;
                        getline(inFile, fileContents);
                        inFile.close();

                        stringstream ss(fileContents);
                        int stageIndicator;
                        char delimiter;
                        ss >> stageIndicator >> delimiter;

                        Stage stage = static_cast<Stage>(stageIndicator);
                        string remainingData = fileContents.substr(ss.tellg());
                        string data = blockchainFunction.collectData(stage, true, remainingData);
                        // Accessing the chain using the getter method
                        const std::vector<Block>& chain = blockchainFunction.getChain();
                        blockchainFunction.addBlockFromFile(stage, data);

                        cout << "Block generated from " << filename << " for " << stageToString(stage) << " stage." << endl;
                    } else {
                        cout << "Invalid selection." << endl;
                    }
                }
            }
            else {
                cout << "Invalid choice." << endl;
                break;
            }
            const std::vector<Block>& chain = blockchainFunction.getChain();
            cout << "Block added for stage: " << stageToString(currentStage) << endl;
            currentStage = static_cast<Stage>((currentStage + 1) % 7);

            const Block& latestBlock = chain.back();
            cout << "\n";
            blockchainFunction.printBlock(latestBlock);
            cout << "\n\nPress any button to return to main menu";
            getchar();
            cout << "\n\nReturning to main menu...";
            sleep(3);
            break;
        }
        // Displays options for viewing the blockchain, either in memory or from saved files
        case 2: {
            system("cls");
            bool inViewMenu = true;
            while (inViewMenu) {
                // View menu options presented to the user
                // Handles user input to select the view option
                cout << "*-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*" << endl;
                cout << "*            View BlockChain Options:              *" << endl;
                cout << "*--------------------------------------------------*" << endl;
                cout << "*      ( 1 ) View Current Blockchain in Memory     *" << endl;
                cout << "*--------------------------------------------------*" << endl;
                cout << "*      ( 2 ) View Saved Blockchains from Files     *" << endl;
                cout << "*--------------------------------------------------*" << endl;
                cout << "*      ( 3 ) Return to Main Menu                   *" << endl;
                cout << "*-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*-*-**-*" << endl;

                int viewChoice;
                cout << "> ";
                cin >> viewChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (viewChoice) {
                    case 1:
                        {
                        // Logic for viewing the current blockchain in memory
                        system("cls");
                        const std::vector<Block>& chain = blockchainFunction.getChain();
                        for (const Block& block : chain) {
                            blockchainFunction.printBlock(block);
                            cout << "Press enter to view next block...";
                            getchar();
                            system("cls");
                        }
                        break;

                        }
                 case 2: {
                     // Logic for viewing saved blockchains from files
                    vector<string> fileList = listTxtFiles();
                    int fileIndex = 1;
                    for (const auto& fileName : fileList) {
                        cout << fileIndex++ << ". " << fileName << endl;
                    }

                    cout << "Enter the number of the file you want to view: ";
                    int choice;
                    cin >> choice;

                    if (choice > 0 && choice <= fileList.size()) {
                        system("cls");
                        string selectedFile = fileList[choice - 1];
                        displayBlockFromFile(selectedFile);
                    } else {
                        cout << "Invalid selection." << endl;
                    }
                    break;
                }
                    case 3:
                     // Returns to the main menu
                        inViewMenu = false;
                        system("cls");
                        break;

                    default:
                        cout << "Invalid choice. Please try again." << endl;
                        break;
                }

                if (inViewMenu) {
                    cout << "Press enter to return to the View Menu...";
                    getchar();
                    system("cls");
                }
            }
            break;
        }
        case 3: {
            // Handles saving the current state of the blockchain to a file
            string filename;
            cout << "Enter File Name: ";
            cin >> filename;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            const std::vector<Block>& chain = blockchainFunction.getChain();
            for (const auto& block : chain) {
                writeBlockToFile(block, filename);
            }
            cout << "Saving Program." << endl;
            break;
        }
        case 4: {
            string hashPattern;
            cout << "Enter the first 2 and last 4 characters of the CurrentHash to search: ";
            cin >> hashPattern;

            searchForBlockByHashPattern(hashPattern);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Press Enter to return to the main menu...";
            getchar();
            break;
        }
        case 5:
        // Exits the program
            cout << "Exiting program." << endl;
            startSystem = false;
        default:
        // Handles invalid input from the user in the main menu
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
    return 0;
}
